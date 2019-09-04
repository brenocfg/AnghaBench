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
 float cosf (int) ; 
 float invsqrtpi ; 
 float pzerof (float) ; 
 float qzerof (float) ; 
 float sinf (float) ; 
 float sqrtf (float) ; 

__attribute__((used)) static float common(uint32_t ix, float x, int y0)
{
	float z,s,c,ss,cc;
	/*
	 * j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
	 * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x)
	 */
	s = sinf(x);
	c = cosf(x);
	if (y0)
		c = -c;
	cc = s+c;
	if (ix < 0x7f000000) {
		ss = s-c;
		z = -cosf(2*x);
		if (s*c < 0)
			cc = z/ss;
		else
			ss = z/cc;
		if (ix < 0x58800000) {
			if (y0)
				ss = -ss;
			cc = pzerof(x)*cc-qzerof(x)*ss;
		}
	}
	return invsqrtpi*cc/sqrtf(x);
}