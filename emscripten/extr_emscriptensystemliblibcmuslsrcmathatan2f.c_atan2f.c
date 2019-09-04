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
 int /*<<< orphan*/  GET_FLOAT_WORD (int,float) ; 
 float atanf (float) ; 
 float fabsf (float) ; 
 scalar_t__ isnan (float) ; 
 float pi ; 
 int /*<<< orphan*/  pi_lo ; 

float atan2f(float y, float x)
{
	float z;
	uint32_t m,ix,iy;

	if (isnan(x) || isnan(y))
		return x+y;
	GET_FLOAT_WORD(ix, x);
	GET_FLOAT_WORD(iy, y);
	if (ix == 0x3f800000)  /* x=1.0 */
		return atanf(y);
	m = ((iy>>31)&1) | ((ix>>30)&2);  /* 2*sign(x)+sign(y) */
	ix &= 0x7fffffff;
	iy &= 0x7fffffff;

	/* when y = 0 */
	if (iy == 0) {
		switch (m) {
		case 0:
		case 1: return y;   /* atan(+-0,+anything)=+-0 */
		case 2: return  pi; /* atan(+0,-anything) = pi */
		case 3: return -pi; /* atan(-0,-anything) =-pi */
		}
	}
	/* when x = 0 */
	if (ix == 0)
		return m&1 ? -pi/2 : pi/2;
	/* when x is INF */
	if (ix == 0x7f800000) {
		if (iy == 0x7f800000) {
			switch (m) {
			case 0: return  pi/4; /* atan(+INF,+INF) */
			case 1: return -pi/4; /* atan(-INF,+INF) */
			case 2: return 3*pi/4;  /*atan(+INF,-INF)*/
			case 3: return -3*pi/4; /*atan(-INF,-INF)*/
			}
		} else {
			switch (m) {
			case 0: return  0.0f;    /* atan(+...,+INF) */
			case 1: return -0.0f;    /* atan(-...,+INF) */
			case 2: return  pi; /* atan(+...,-INF) */
			case 3: return -pi; /* atan(-...,-INF) */
			}
		}
	}
	/* |y/x| > 0x1p26 */
	if (ix+(26<<23) < iy || iy == 0x7f800000)
		return m&1 ? -pi/2 : pi/2;

	/* z = atan(|y/x|) with correct underflow */
	if ((m&2) && iy+(26<<23) < ix)  /*|y/x| < 0x1p-26, x < 0 */
		z = 0.0;
	else
		z = atanf(fabsf(y/x));
	switch (m) {
	case 0: return z;              /* atan(+,+) */
	case 1: return -z;             /* atan(-,+) */
	case 2: return pi - (z-pi_lo); /* atan(+,-) */
	default: /* case 3 */
		return (z-pi_lo) - pi; /* atan(-,-) */
	}
}