#include <Wire.h>
#include <RTClib.h>


RTC_DS3231 rtc;
const char *monthNames[] = {"", "Januari", "Februari", "Maret", "April", "Mei", "Juni", "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

// SCL = A5
// SDA = A4
void setup() {
  Serial.begin(9600);

  // Memulai komunikasi dengan modul RTC DS3231
  if (!rtc.begin()) {
    Serial.println("Tidak dapat menemukan RTC");
    while (1);
  }

  // Jika modul RTC kehilangan daya, set waktu dengan waktu kompilasi program
  if (rtc.lostPower()) {
    Serial.println("RTC kehilangan daya, atur ulang waktu!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();

  Serial.print("Tanggal Sekarang: ");
  Serial.print(now.day());
  Serial.print(" ");
  Serial.print(monthNames[now.month()]);
  Serial.print(" ");
  Serial.print(now.year());
  Serial.print(" Jam Sekarang: ");
  printDigits(now.hour());
  Serial.print(":");
  printDigits(now.minute());
  Serial.print(":");
  printDigits(now.second());
  Serial.println();

  delay(1000);
}

// Fungsi untuk menampilkan dua digit angka, menambahkan '0' di depan jika angkanya kurang dari 10
void printDigits(int digits) {
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
