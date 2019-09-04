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
 int time (int /*<<< orphan*/ ) ; 

int truthy() {
  int x = time(0);
  while (x > 10) {
    x |= 7;
    x /= 2;
  }
  return x < 3;
}