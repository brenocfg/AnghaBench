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
typedef  int uint32_t ;

/* Variables and functions */
 double cos (int) ; 
 double invsqrtpi ; 
 double pzero (double) ; 
 double qzero (double) ; 
 double sin (double) ; 
 double sqrt (double) ; 

__attribute__((used)) static double common(uint32_t ix, double x, int y0)
{
	double s,c,ss,cc,z;

	/*
	 * j0(x) = sqrt(2/(pi*x))*(p0(x)*cos(x-pi/4)-q0(x)*sin(x-pi/4))
	 * y0(x) = sqrt(2/(pi*x))*(p0(x)*sin(x-pi/4)+q0(x)*cos(x-pi/4))
	 *
	 * sin(x-pi/4) = (sin(x) - cos(x))/sqrt(2)
	 * cos(x-pi/4) = (sin(x) + cos(x))/sqrt(2)
	 * sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
	 */
	s = sin(x);
	c = cos(x);
	if (y0)
		c = -c;
	cc = s+c;
	/* avoid overflow in 2*x, big ulp error when x>=0x1p1023 */
	if (ix < 0x7fe00000) {
		ss = s-c;
		z = -cos(2*x);
		if (s*c < 0)
			cc = z/ss;
		else
			ss = z/cc;
		if (ix < 0x48000000) {
			if (y0)
				ss = -ss;
			cc = pzero(x)*cc-qzero(x)*ss;
		}
	}
	return invsqrtpi*cc/sqrt(x);
}