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
 double C0 ; 
 double C1 ; 
 double C2 ; 
 double C3 ; 

float __cosdf(double x)
{
	double_t r, w, z;

	/* Try to optimize for parallel evaluation as in __tandf.c. */
	z = x*x;
	w = z*z;
	r = C2+z*C3;
	return ((1.0+z*C0) + w*C1) + (w*z)*r;
}