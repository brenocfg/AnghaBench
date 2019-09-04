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
 double func_int_double_1 (int /*<<< orphan*/ ,int,double) ; 
 double func_int_double_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,double) ; 
 int /*<<< orphan*/  printf (char*,double) ; 

int main() {
  double ret = func_int_double_1(0, 5, 10.0);
  printf("%f\n", ret); // Expects to print 15
  ret = func_int_double_2(0, 0, 5, 10.0);
  printf("%f\n", ret); // Expects to print 15
}