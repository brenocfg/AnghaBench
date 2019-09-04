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

double get() {
  double ret = 0;
  __asm __volatile__("Math.abs(-12/3.3)" : "=r"(ret));  // write to a variable
  asm("#comment1");
  asm volatile("#comment2");
  asm volatile(
      "#comment3\n"
      "#comment4\n");
  return ret;
}