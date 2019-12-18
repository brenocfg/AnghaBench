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
typedef  int const di_int ;

/* Variables and functions */
 int CHAR_BIT ; 
 int /*<<< orphan*/  compilerrt_abort () ; 

di_int __mulvdi3(di_int a, di_int b) {
  const int N = (int)(sizeof(di_int) * CHAR_BIT);
  const di_int MIN = (di_int)1 << (N - 1);
  const di_int MAX = ~MIN;
  if (a == MIN) {
    if (b == 0 || b == 1)
      return a * b;
    compilerrt_abort();
  }
  if (b == MIN) {
    if (a == 0 || a == 1)
      return a * b;
    compilerrt_abort();
  }
  di_int sa = a >> (N - 1);
  di_int abs_a = (a ^ sa) - sa;
  di_int sb = b >> (N - 1);
  di_int abs_b = (b ^ sb) - sb;
  if (abs_a < 2 || abs_b < 2)
    return a * b;
  if (sa == sb) {
    if (abs_a > MAX / abs_b)
      compilerrt_abort();
  } else {
    if (abs_a > MIN / -abs_b)
      compilerrt_abort();
  }
  return a * b;
}