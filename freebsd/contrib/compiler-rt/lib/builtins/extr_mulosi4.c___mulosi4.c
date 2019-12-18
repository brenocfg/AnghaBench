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
typedef  int const si_int ;

/* Variables and functions */
 int CHAR_BIT ; 

si_int __mulosi4(si_int a, si_int b, int *overflow) {
  const int N = (int)(sizeof(si_int) * CHAR_BIT);
  const si_int MIN = (si_int)1 << (N - 1);
  const si_int MAX = ~MIN;
  *overflow = 0;
  si_int result = a * b;
  if (a == MIN) {
    if (b != 0 && b != 1)
      *overflow = 1;
    return result;
  }
  if (b == MIN) {
    if (a != 0 && a != 1)
      *overflow = 1;
    return result;
  }
  si_int sa = a >> (N - 1);
  si_int abs_a = (a ^ sa) - sa;
  si_int sb = b >> (N - 1);
  si_int abs_b = (b ^ sb) - sb;
  if (abs_a < 2 || abs_b < 2)
    return result;
  if (sa == sb) {
    if (abs_a > MAX / abs_b)
      *overflow = 1;
  } else {
    if (abs_a > MIN / -abs_b)
      *overflow = 1;
  }
  return result;
}