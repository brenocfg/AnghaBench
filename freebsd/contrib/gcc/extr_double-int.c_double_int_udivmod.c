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
typedef  int /*<<< orphan*/  double_int ;

/* Variables and functions */
 int /*<<< orphan*/  double_int_divmod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ *) ; 

double_int
double_int_udivmod (double_int a, double_int b, unsigned code, double_int *mod)
{
  return double_int_divmod (a, b, true, code, mod);
}