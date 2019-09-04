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
 double __cos (double,double) ; 
 double __sin (double,double,int /*<<< orphan*/ ) ; 
 double floor (double) ; 
 double pi ; 

__attribute__((used)) static double sin_pi(double x)
{
	int n;

	/* spurious inexact if odd int */
	x = 2.0*(x*0.5 - floor(x*0.5));  /* x mod 2.0 */

	n = (int)(x*4.0);
	n = (n+1)/2;
	x -= n*0.5f;
	x *= pi;

	switch (n) {
	default: /* case 4: */
	case 0: return __sin(x, 0.0, 0);
	case 1: return __cos(x, 0.0);
	case 2: return __sin(-x, 0.0, 0);
	case 3: return -__cos(x, 0.0);
	}
}