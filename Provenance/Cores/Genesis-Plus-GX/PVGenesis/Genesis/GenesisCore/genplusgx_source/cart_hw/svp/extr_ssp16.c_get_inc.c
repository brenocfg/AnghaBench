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

__attribute__((used)) static int get_inc(int mode)
{
  int inc = (mode >> 11) & 7;
  if (inc != 0) {
    if (inc != 7) inc--;
    /* inc = (1<<16) << inc; */
    inc = 1 << inc; /* 0 1 2 4 8 16 32 128 */
    if (mode & 0x8000) inc = -inc; /* decrement mode */
  }
  return inc;
}