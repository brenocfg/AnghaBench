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

/* Variables and functions */

int64_t returner2(int test) {
  while (test > 10) test /= 2; // confuse the compiler so it doesn't eliminate this function
  return test > 5 ? 0x0000def123450123ULL : 0ULL;
}