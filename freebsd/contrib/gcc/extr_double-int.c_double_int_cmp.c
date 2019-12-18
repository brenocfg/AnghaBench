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
 int double_int_scmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int double_int_ucmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
double_int_cmp (double_int a, double_int b, bool uns)
{
  if (uns)
    return double_int_ucmp (a, b);
  else
    return double_int_scmp (a, b);
}