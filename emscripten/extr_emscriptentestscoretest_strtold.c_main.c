#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int strtold (char*,char**) ; 

int main() {
  char* endptr;
  printf("\n");
  printf("%Lg\n", strtold("0", &endptr));
  printf("%Lg\n", strtold("0.", &endptr));
  printf("%Lg\n", strtold("0.0", &endptr));
  printf("%Lg\n", strtold("-0.0", &endptr));
  printf("%Lg\n", strtold("1", &endptr));
  printf("%Lg\n", strtold("1.", &endptr));
  printf("%Lg\n", strtold("1.0", &endptr));
  printf("%Lg\n", strtold("z1.0", &endptr));
  printf("%Lg\n", strtold("0.5", &endptr));
  printf("%Lg\n", strtold(".5", &endptr));
  printf("%Lg\n", strtold(".a5", &endptr));
  printf("%Lg\n", strtold("123", &endptr));
  printf("%Lg\n", strtold("123.456", &endptr));
  printf("%Lg\n", strtold("-123.456", &endptr));
  printf("%Lg\n", strtold("1234567891234567890", &endptr));
  printf("%Lg\n", strtold("1234567891234567890e+50", &endptr));
  printf("%Lg\n", strtold("84e+220", &endptr));
  printf("%Lg\n", strtold("123e-50", &endptr));
  printf("%Lg\n", strtold("123e-250", &endptr));
  printf("%Lg\n", strtold("123e-450", &endptr));
  printf("%Lg\n", strtold("0x6", &endptr));
  printf("%Lg\n", strtold("-0x0p+0", &endptr));
  char str[] = "  12.34e56end";
  printf("%Lg\n", strtold(str, &endptr));
  printf("%d\n", endptr - str);
  printf("%Lg\n", strtold("84e+420", &endptr));
  printf("%.12Lf\n", strtold("1.2345678900000000e+08", NULL));
  return 0;
}