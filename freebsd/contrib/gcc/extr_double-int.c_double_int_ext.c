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
 int /*<<< orphan*/  double_int_sext (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  double_int_zext (int /*<<< orphan*/ ,unsigned int) ; 

double_int
double_int_ext (double_int cst, unsigned prec, bool uns)
{
  if (uns)
    return double_int_zext (cst, prec);
  else
    return double_int_sext (cst, prec);
}