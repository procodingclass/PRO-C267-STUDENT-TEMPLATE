#include<RTClib.h>
#include<ezButton.h>
#include <LiquidCrystal_I2C.h>

RTC_DS1307 rtc;

//  lcd object : setting register address 0x27
LiquidCrystal_I2C lcd(0x27, 20, 4);



//  encoder variables
byte clk = 2;
byte dt = 3;
byte sw = 4;

ezButton button(sw);

//  counting rotations
int counter = 0;
int prev_counter = 0;
int flag = 0;

String rtc_date = "";
String rtc_time = "";

void setup() {

  Serial.begin(9600);

  //  initializing LCD
  lcd.init();  //  initialize the lcd.
  lcd.clear();  //  clears the screen and moves the cursor to the top left corner.
  lcd.backlight();  //  turn on the backlight.

  //  initial messages
  lcd.clear();
  lcd_print(0, 0, "RTC found");
  delay(1000);
  lcd_print(0, 0, "Hi i am Cuckoo!");
  delay(2000);
  // if (!rtc.begin()) {
  //   Serial.println("RTC not initialised");
  //   while (true);
  // }
  // Serial.println("RTC found");

  attachInterrupt(digitalPinToInterrupt(clk), encoder, FALLING);

  button.setDebounceTime(25);
}

void encoder() {
  prev_counter = counter;
  if (digitalRead(dt)  ==  HIGH)counter++;
  else counter--;
  counter = constrain(counter, 0, 3);
  flag = 1;
}

void mode_selector() {

  if (prev_counter != counter  &&  flag  ==  1) {
    if (counter  ==  0) {
      lcd.clear();
      lcd_print(0, 0, "Date and Time");
    }
    else if (counter  ==  1) {
      lcd.clear();
      lcd_print(0, 0, "Set Alarm");
    }
    else if (counter  ==  2) {
      lcd.clear();
      lcd_print(0, 0, "Stopwatch");
    }
    else if (counter  ==  3) {
      lcd.clear();
      lcd_print(0, 0, "Countdown Timer");
    }
    flag = 0;
  }
}



void loop() {

  button.loop();
  if (button.isPressed())select_mode();

  //  RTC date and time
  // DateTime dt = rtc.now();
  // rtc_date = get_date(dt);
  // // Serial.println(rtc_date);
  // rtc_time = get_time(dt);
  // Serial.println(rtc_time);
  mode_selector();

  //  for better working of simulator
  delay(10);
}

String get_time(DateTime current) {

  int hour = current.hour();
  int minute = current.minute();
  int second = current.second();

  String current_time = "Time : " + String(hour) + ":" + String(minute) +
                        ":" + String(second);

  return current_time;
}

String get_date(DateTime current) {

  int year = current.year();
  int month = current.month();
  int day = current.day();

  String current_date = "Date : " + String(day) + "/" + String(month) +
                        "/" + String(year);

  return current_date;
}

void select_mode(){
 if (counter  ==  0)get_time();
 else if (counter  ==  1)set_alarm();
 else if (counter  ==  2)stopwatch();
 else countdown();
}
void get_time(){
 
}
 
void set_alarm(){
 
}

void stopwatch(){
 
}
 
void countdown(){
 
}


void lcd_print(int x, int y, String message) {
  lcd.setCursor(x, y);
  lcd.print(message);
}
