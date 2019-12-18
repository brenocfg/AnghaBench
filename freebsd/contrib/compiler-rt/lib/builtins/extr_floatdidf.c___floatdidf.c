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
typedef  int int64_t ;
typedef  double const int32_t ;
typedef  int di_int ;

/* Variables and functions */
 int INT64_C (int) ; 

double __floatdidf(di_int a) {
  static const double twop52 = 4503599627370496.0; // 0x1.0p52
  static const double twop32 = 4294967296.0;       // 0x1.0p32

  union {
    int64_t x;
    double d;
  } low = {.d = twop52};

  const double high = (int32_t)(a >> 32) * twop32;
  low.x |= a & INT64_C(0x00000000ffffffff);

  const double result = (high - twop52) + low.d;
  return result;
}