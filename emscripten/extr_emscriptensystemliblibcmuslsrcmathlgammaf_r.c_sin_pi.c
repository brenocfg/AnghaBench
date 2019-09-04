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
 float __cosdf (double) ; 
 float __sindf (double) ; 
 float floorf (float) ; 

__attribute__((used)) static float sin_pi(float x)
{
	double_t y;
	int n;

	/* spurious inexact if odd int */
	x = 2*(x*0.5f - floorf(x*0.5f));  /* x mod 2.0 */

	n = (int)(x*4);
	n = (n+1)/2;
	y = x - n*0.5f;
	y *= 3.14159265358979323846;
	switch (n) {
	default: /* case 4: */
	case 0: return __sindf(y);
	case 1: return __cosdf(y);
	case 2: return __sindf(-y);
	case 3: return -__cosdf(y);
	}
}