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
typedef  int uint64_t ;
typedef  int du_int ;

/* Variables and functions */
 int UINT64_C (int) ; 

double __floatundidf(du_int a) {
  static const double twop52 = 4503599627370496.0;           // 0x1.0p52
  static const double twop84 = 19342813113834066795298816.0; // 0x1.0p84
  static const double twop84_plus_twop52 =
      19342813118337666422669312.0; // 0x1.00000001p84

  union {
    uint64_t x;
    double d;
  } high = {.d = twop84};
  union {
    uint64_t x;
    double d;
  } low = {.d = twop52};

  high.x |= a >> 32;
  low.x |= a & UINT64_C(0x00000000ffffffff);

  const double result = (high.d - twop84_plus_twop52) + low.d;
  return result;
}