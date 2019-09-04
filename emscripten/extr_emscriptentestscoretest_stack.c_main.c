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
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int test (int) ; 

int main(int argc, char **argv) {
  // We should get the same value for the first and last - stack has unwound
  int x1 = test(argc - 2);
  int x2 = test(100);
  int x3 = test((argc - 2) / 4);
  printf("*%d,%d*\n", x3 - x1, x2 != x1);
  return 0;
}