#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>                       
#include <MFRC522.h> 
int bakiye=100; 
int tutar=5;
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(10,9); 
byte kart[4] = {210, 103, 240, 115}; 

void setup() {
   lcd.begin();
   Serial.begin(9600);                   
   SPI.begin();                           
    rfid.PCD_Init();                    
    lcd.home();
    lcd.print("KARTLI GECIS");
    lcd.setCursor(4, 1);
    lcd.print("SISTEMI");
}

void loop() {
  if ( ! rfid.PICC_IsNewCardPresent())    //Yeni kartın okunmasını bekliyoruz.
    return;
  if ( ! rfid.PICC_ReadCardSerial())      //Kart okunmadığı zaman bekliyoruz.
    return;
  ekranaYazdir();
  if (rfid.uid.uidByte[0] == kart[0] &&   
      rfid.uid.uidByte[1] == kart[1] &&
      rfid.uid.uidByte[2] == kart[2] &&
      rfid.uid.uidByte[3] == kart[3] ) {
      if(tutar>5)
      {
         Serial.println("Dogru Kart");
       
        bakiye=bakiye-tutar
        lcd.home();
        lcd.setCursor(1, 0);
        lcd.print("Kesilen Tutar:"+tutar );
        lcd.setCursor(1, 1);
        lcd.print("Kalan Bakiye:"+bakiye);
        delay(3000);
        lcd.clear();
         lcd.home();
          lcd.setCursor(1, 0);
        lcd.print("KARTLI GECIS");
        lcd.setCursor(4, 1);
        lcd.print("SISTEMI");
      }
      else
      {
        lcd.clear();
         lcd.home();
          lcd.setCursor(1, 0);
        lcd.print("Yetersiz Bakiye");
        lcd.setCursor(4, 1);
        lcd.print("Karta yukleme yap");
        delay(3000);
          lcd.clear();
           lcd.home();
          lcd.setCursor(1, 0);
        lcd.print("KARTLI GECIS");
        lcd.setCursor(4, 1);
        lcd.print("SISTEMI");
      }
     
    }

}
void ekranaYazdir(){
  Serial.print("Kimlik Numarasi: ");
  for(int sayac = 0; sayac < 4; sayac++){
    Serial.print(rfid.uid.uidByte[sayac]);
   Serial.print(" ");
  }
  Serial.println("");
}
