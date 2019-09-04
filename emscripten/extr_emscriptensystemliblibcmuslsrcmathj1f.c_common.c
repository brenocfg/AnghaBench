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
 double cosf (int) ; 
 double invsqrtpi ; 
 double ponef (float) ; 
 double qonef (float) ; 
 double sinf (float) ; 
 double sqrtf (float) ; 

__attribute__((used)) static float common(uint32_t ix, float x, int y1, int sign)
{
	double z,s,c,ss,cc;

	s = sinf(x);
	if (y1)
		s = -s;
	c = cosf(x);
	cc = s-c;
	if (ix < 0x7f000000) {
		ss = -s-c;
		z = cosf(2*x);
		if (s*c > 0)
			cc = z/ss;
		else
			ss = z/cc;
		if (ix < 0x58800000) {
			if (y1)
				ss = -ss;
			cc = ponef(x)*cc-qonef(x)*ss;
		}
	}
	if (sign)
		cc = -cc;
	return invsqrtpi*cc/sqrtf(x);
}