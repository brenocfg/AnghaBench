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
 int /*<<< orphan*/  test_value (int) ; 

int main() {
  test_value(0);
  test_value(100.1);
  test_value(-100.1);
  test_value(.5);
  test_value(-.5);
  test_value(1 - 1e-16);
  test_value(-(1 - 1e-16));

  return 0;
}