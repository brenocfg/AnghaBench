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
 double pone (double) ; 
 double qone (double) ; 
 double sin (double) ; 
 double sqrt (double) ; 

__attribute__((used)) static double common(uint32_t ix, double x, int y1, int sign)
{
	double z,s,c,ss,cc;

	/*
	 * j1(x) = sqrt(2/(pi*x))*(p1(x)*cos(x-3pi/4)-q1(x)*sin(x-3pi/4))
	 * y1(x) = sqrt(2/(pi*x))*(p1(x)*sin(x-3pi/4)+q1(x)*cos(x-3pi/4))
	 *
	 * sin(x-3pi/4) = -(sin(x) + cos(x))/sqrt(2)
	 * cos(x-3pi/4) = (sin(x) - cos(x))/sqrt(2)
	 * sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
	 */
	s = sin(x);
	if (y1)
		s = -s;
	c = cos(x);
	cc = s-c;
	if (ix < 0x7fe00000) {
		/* avoid overflow in 2*x */
		ss = -s-c;
		z = cos(2*x);
		if (s*c > 0)
			cc = z/ss;
		else
			ss = z/cc;
		if (ix < 0x48000000) {
			if (y1)
				ss = -ss;
			cc = pone(x)*cc-qone(x)*ss;
		}
	}
	if (sign)
		cc = -cc;
	return invsqrtpi*cc/sqrt(x);
}