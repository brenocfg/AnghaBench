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
 int JSDOUBLE_HI32_SIGNBIT ; 

bool JSDOUBLE_IS_NEGZERO(double d) {
  union {
    struct {
      unsigned int lo, hi;
    } s;
    double d;
  } x;
  if (d != 0) return false;
  x.d = d;
  return (x.s.hi & JSDOUBLE_HI32_SIGNBIT) != 0;
}