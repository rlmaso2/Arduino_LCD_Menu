#include <LiquidCrystal.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// Main menu array
String mainMenu[5]; 
// Main menu default choice
int mainSwitch = 0;
#define mainMenuItems 2
//run menu array
String runMenu[2];
int runSwitch = 0;
#define runMenuItems 2
//settings menu array
String settingsMenu[4];
int settingsSwitch = 0;
int freqq = 50;
//flush menu array
String flushMenu[10];
int flushSwitch = 0;
#define flushMenuItems 1
int settings[4] = {15,50,50,50}; // frequency Hz, Dutycycle1 %, Dutycycle2 %, delay % of period
String units[4] = {"Hz", "%", "%", "%"};
void setup() {
  lcd.begin(16, 2);              // start the lcd
  lcd.setCursor(0,0);
  lcd.print("Main menu: "); 
  
  // Filling our main menu items
  mainMenu[0] = "Flush            ";
  mainMenu[1] = "Settings          ";
  mainMenu[2] = "Run            ";
  
  // Filling our settings menu items
  settingsMenu[0] = "Set Freq = ";
  settingsMenu[1] = "Set Duty1 = ";
  settingsMenu[2] = "Set Duty2 = ";
  settingsMenu[3] = "Set Delay = ";
  // Filling our run menu items
  runMenu[0] = "ON";
  runMenu[1] = "OFF";
  // Filling our flush menu items
  flushMenu[0] = "OFF ";
  flushMenu[1] = "ON ";
  
  lcd.setCursor(0,1);
  lcd.print(mainMenu[0]);
  Serial.begin(9600);

}

int read_LCD_buttons()
{
 adc_key_in = analogRead(0);
 if (adc_key_in < 620)  return btnSELECT; 
 if (adc_key_in < 820)  return btnRIGHT;
 if (adc_key_in < 860)  return btnLEFT;
 if (adc_key_in < 908)  return btnDOWN;    
 if (adc_key_in < 936)  return btnUP; 
 return btnNONE;  // when all others fail, return this...
}

void clearScreen()
{
  lcd.setCursor(0,0);
  lcd.print("                  "); 
  lcd.setCursor(0,1);
  lcd.print("                  ");
}

void clearLine(int lineNum)
{
  lcd.setCursor(0,lineNum);
  lcd.print("                  "); 
  lcd.setCursor(0,lineNum);
}

void flushAll(bool flu){
} 

void startSol(){
} 

void stopSol(){

}

void flushSol(){
  lcd.setCursor(0,0);
  lcd.print(mainMenu[0]); // print a simple message
  lcd.setCursor(0,1);
  lcd.print("Select to Flush");
  // Loop for reading buttons
  while(true)
  {
    lcd_key = read_LCD_buttons();
    Serial.println("Flush?");
    
    switch (lcd_key)
    {
       case btnRIGHT:
       {
         break;
       }
       // back to main menu on the left button press
       case btnLEFT:
       {
         delay(200);
         goto exit;
         break;
       }
       case btnSELECT:
       {
          if(flushSwitch == 0){
              Serial.println("Flush ON");
              flushSwitch = 1;
              flushAll(true);
              clearLine(1);
              lcd.print(flushMenu[flushSwitch]);
           }
           else if(flushSwitch == 1){
              Serial.println("Flush OFF");
              flushSwitch = 0;
              flushAll(false);
              clearLine(1);
              lcd.print(flushMenu[flushSwitch]);
           }
           delay(200);
           break;
       }
     }
    }
  
  exit:
  flushSwitch = 0;
  flushAll(false);
  Serial.println("Flush OFF");
  lcd.setCursor(0,0);
  lcd.print("Main menu:     ");
  clearLine(1);
  lcd.print(mainMenu[0]);
  return;
}

void settingsSol(){
  lcd.setCursor(0,0);
  lcd.print(mainMenu[1]); // print a simple message
  lcd.setCursor(0,1);
  lcd.print(settingsMenu[settingsSwitch]);
  lcd.print(settings[settingsSwitch]);
  lcd.print(units[settingsSwitch]);
//  lcd.print("Modify Settings?");
  // Loop for reading buttons
  while(true)
  {
    Serial.print(settingsMenu[settingsSwitch]);
          Serial.print(settings[settingsSwitch]);
          Serial.println(units[settingsSwitch]);
          Serial.print("SettingsSwitch:");
          Serial.print(settingsSwitch);
    lcd_key = read_LCD_buttons();
    
    switch (lcd_key)
    {
       case btnRIGHT:
       {
         delay(200);
         break;
       }
       // back to main menu on the left button press
       case btnLEFT:
       {
         delay(200);
         goto exit;
         break;
       }
       case btnUP:
       {
        if(settings[settingsSwitch] <= 100)
           increaseSetting();
         clearLine(1);
         lcd.print(settingsMenu[settingsSwitch]);
         lcd.print(settings[settingsSwitch]);
         lcd.print(units[settingsSwitch]);
         delay(200);
         break;
       }
       case btnDOWN:
       {
        if(settings[settingsSwitch] >= 0)
           decreaseSetting();
         clearLine(1);
         lcd.print(settingsMenu[settingsSwitch]);
         lcd.print(settings[settingsSwitch]);
         lcd.print(units[settingsSwitch]);
         delay(200);
         break;
       }
       case btnSELECT:
       {
        Serial.print("LCD Key: ");
        Serial.println(lcd_key);
         if(settingsSwitch == 0){
            increaseSettingSwitch();
//            delay(100);
            clearLine(1);
            lcd.print(settingsMenu[settingsSwitch]);
            lcd.print(settings[settingsSwitch]);
            lcd.print(units[settingsSwitch]);
            delay(200);
            break;
         }
         else if(settingsSwitch == 1){
            increaseSettingSwitch();
//            delay(100);
            clearLine(1);
            lcd.print(settingsMenu[settingsSwitch]);
            lcd.print(settings[settingsSwitch]);
            lcd.print(units[settingsSwitch]);
            delay(200);
            break;
         }
         else if(settingsSwitch == 2){
            increaseSettingSwitch();
//            delay(100);
            clearLine(1);
            lcd.print(settingsMenu[settingsSwitch]);
            lcd.print(settings[settingsSwitch]);
            lcd.print(units[settingsSwitch]);
            delay(200);
            break;
         }
         else if(settingsSwitch == 3){
            increaseSettingSwitch();
            clearLine(1);
            lcd.print(settingsMenu[settingsSwitch]);
            lcd.print(settings[settingsSwitch]);
            lcd.print(units[settingsSwitch]);
      //                goto run;
            delay(200);
            break;
         }
      }
    }
  }
  
  exit:
  lcd.setCursor(0,0);
  lcd.print("Main menu:     ");
  lcd.setCursor(0,1);
  lcd.print(mainMenu[0]);
  return;

  run:
  mainSwitch = 2;
  return;
}
void increaseSetting(){
  settings[settingsSwitch]++;
}
void decreaseSetting(){
  settings[settingsSwitch]--;
}
void increaseSettingSwitch(){
  if(settingsSwitch == 3)
    settingsSwitch = 0;
  else
    settingsSwitch++;
}

void runSol(){
  lcd.setCursor(0,0);
  lcd.print(mainMenu[2]); // print a simple message
  lcd.setCursor(0,1);
  lcd.print("Select to start");
  // Loop for reading buttons
  while(true)
  {
    lcd_key = read_LCD_buttons();
    
    switch (lcd_key)
    {
       case btnRIGHT:
       {
         delay(200);
         break;
       }
       // back to main menu on the left button press
       case btnLEFT:
       {
         stopSol();
         runSwitch = 0;
         delay(200);
         goto exit;
         break;
       }
       case btnSELECT:
       {
        if(runSwitch == 0){
                runSwitch = 1;
                clearScreen();
                lcd.setCursor(0,0);
                lcd.print("Fq: ");
                lcd.print(settings[0]);
                lcd.print(units[0]);
                lcd.print(" ");
                lcd.print("Del:");
                lcd.print(settings[3]);
                lcd.print(units[3]);
                lcd.setCursor(0,1);
                lcd.print("DC1: ");
                lcd.print(settings[1]);
                lcd.print(units[1]);
                lcd.print(" ");
                lcd.print("DC2:");
                lcd.print(settings[2]);
                lcd.print(units[2]);
                startSol();
              }
              else{
                stopSol();
                runSwitch = 0;
                clearScreen();
                lcd.setCursor(0,0);
                lcd.print(mainMenu[2]);
                lcd.setCursor(0,1);
                lcd.print("Select to start");
              }
              delay(200);
            }
          }
        } 
  exit:
  lcd.setCursor(0,0);
  lcd.print("Main menu:     ");
  lcd.setCursor(0,1);
  lcd.print(mainMenu[0]);
  return;
}

void loop()
{  
  // move to the begining of the second line
  lcd.setCursor(0,1); 
  lcd_key = read_LCD_buttons();  // read the buttons
  
 // depending on which button was pushed, 
 // we perform an action
 switch (lcd_key)
 {
   // Enter a sub menu on Right button press
   case btnSELECT:
     {
       clearScreen();
       
       if(mainSwitch == 0)
       {
         delay(200);
         flushSol();
       }
       else if(mainSwitch == 1)
       {
         delay(200);
         settingsSol();
       }
       else if(mainSwitch == 2)
       {
         delay(200);
         runSol();
       }
       break;
     }

   // Move to the next sub menu (UP)
   case btnUP:
     {
       if(mainSwitch == 0)
       {
         mainSwitch = mainMenuItems; 
       }
       else
       {
         mainSwitch = mainSwitch - 1;
       }
       
       lcd.print(mainMenu[mainSwitch]);
       delay(200);
       break;
     }

   // Move to the next sub menu (DOWN)
   case btnDOWN:
     {
       if(mainSwitch > mainMenuItems - 1)
       {
         mainSwitch = 0; 
       }
       else
       {
         mainSwitch = mainSwitch + 1;
       }
       
       lcd.print(mainMenu[mainSwitch]);
       delay(200);
       break;
     }
 }

}


