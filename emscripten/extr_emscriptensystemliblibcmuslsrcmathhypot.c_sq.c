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
typedef  double double_t ;

/* Variables and functions */
 double SPLIT ; 

__attribute__((used)) static void sq(double_t *hi, double_t *lo, double x)
{
	double_t xh, xl, xc;

	xc = (double_t)x*SPLIT;
	xh = x - xc + xc;
	xl = x - xh;
	*hi = (double_t)x*x;
	*lo = xh*xh - *hi + 2*xh*xl + xl*xl;
}