
/*Arduino ADC ve voltaj bölücü devre ile
*Basit Voltmetre ve P10 Gösterge Örneği
*Dr.TRonik YouTube MAYIS 2023 İzmir/Türkiye
*https://youtu.be/WweKJArr4YI
*/

/********************************************************************
  GLOBALS___GLOBALS___GLOBALS___GLOBALS___GLOBALS___GLOBALS___
 ********************************************************************/
//SPI for P10 comminication
#include "SPI.h"

//DMD2 setup for P10
#include "DMD2.h"
#include <fonts/SystemFont5x7.h>
#include <fonts/ArialBlack16.h>
SoftDMD dmd(1, 1);

#define ANALOG_IN_PIN A3  // Analog sinyal girişimiz A3

float VCC = 0.0;  //Ölçülecek Voltaj
float VDD = 0.0;  //A3 pin Voltajı
float R1 = 150000.0;  //R1 direnci 150 K.ohm
float R2 = 39000.0;   //R2 direnci 39 K.ohm
int adc_value = 0;  //ADC değeri
float refVoltage = 5.00;  //Referans / besleme voltajı (farklı ise refVoltage ona göre değişmeli)

/********************************************************************
  SETUP___SETUP___SETUP___SETUP___SETUP___SETUP___SETUP___SETUP___
 ********************************************************************/
void setup() {

  Serial.begin(9600);     //Serial Monitor
  dmd.begin();            //DMD2
  dmd.clearScreen();      //Panel temizleme
  dmd.setBrightness(10);  //Panel parlaklık ayarı
  Serial.println("DC Voltaj Testi Başladı");
}

/********************************************************************
  LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__LOOP__
 ********************************************************************/
void loop() {

  adc_value = analogRead(ANALOG_IN_PIN);    //A3 Analog giriş okuma
  VDD = adc_value * (refVoltage / 1024.0);  //Okunan girişin referans değerine oranlanması
  VCC = VDD / (R2 / (R1 + R2));             //Ölülecek voltaj değerinin hesaplanması
  Serial.print("Input Voltage = ");
  Serial.println(VCC, 2);  //Ondalık 2 hane serial yazdırma

  //Ondalık tek hane p10 panele yazdırma
  dmd.selectFont(ArialBlack16);  //Font seçimi
  char buffer[10];
  dmd.drawString(0, 0, (dtostrf(VCC, 2, 1, buffer)));  //float değişkenini ondalıktan sonra 1 hane yazdırma
  delay(5000); //5 saniye de bir...
  dmd.clearScreen(); // Panelde önceki ölçümden karekter kalmasın...
}

/*
//___:
e-posta: bilgi@ronaer.com
https://www.instagram.com/dr.tronik2023/   
YouTube: Dr.TRonik: www.youtube.com/c/DrTRonik
PCBWay: https://www.pcbway.com/project/member/shareproject/?bmbno=A0E12018-0BBC-4C
*/
