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
 int /*<<< orphan*/  printf (char*,...) ; 

int check_equal(int expected, int actual)
{
  if (expected == actual) {
    printf("ok\n");
    return 1;
  } else {
    printf("error: expected = %d, actual = %d\n", expected, actual);
    return 0;
  }
}