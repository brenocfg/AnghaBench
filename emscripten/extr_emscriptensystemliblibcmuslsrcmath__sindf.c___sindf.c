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
 double S1 ; 
 double S2 ; 
 double S3 ; 
 double S4 ; 

float __sindf(double x)
{
	double_t r, s, w, z;

	/* Try to optimize for parallel evaluation as in __tandf.c. */
	z = x*x;
	w = z*z;
	r = S3 + z*S4;
	s = z*x;
	return (x + s*(S1 + z*S2)) + s*w*r;
}