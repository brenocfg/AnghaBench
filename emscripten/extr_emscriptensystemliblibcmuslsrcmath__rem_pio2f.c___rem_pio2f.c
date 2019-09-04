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
typedef  int int32_t ;
typedef  float double_t ;

/* Variables and functions */
 int __rem_pio2_large (double*,double*,int,int,int /*<<< orphan*/ ) ; 
 float invpio2 ; 
 float pio2_1 ; 
 float pio2_1t ; 
 float toint ; 

int __rem_pio2f(float x, double *y)
{
	union {float f; uint32_t i;} u = {x};
	double tx[1],ty[1];
	double_t fn;
	uint32_t ix;
	int n, sign, e0;

	ix = u.i & 0x7fffffff;
	/* 25+53 bit pi is good enough for medium size */
	if (ix < 0x4dc90fdb) {  /* |x| ~< 2^28*(pi/2), medium size */
		/* Use a specialized rint() to get fn.  Assume round-to-nearest. */
		fn = (double_t)x*invpio2 + toint - toint;
		n  = (int32_t)fn;
		*y = x - fn*pio2_1 - fn*pio2_1t;
		return n;
	}
	if(ix>=0x7f800000) {  /* x is inf or NaN */
		*y = x-x;
		return 0;
	}
	/* scale x into [2^23, 2^24-1] */
	sign = u.i>>31;
	e0 = (ix>>23) - (0x7f+23);  /* e0 = ilogb(|x|)-23, positive */
	u.i = ix - (e0<<23);
	tx[0] = u.f;
	n  =  __rem_pio2_large(tx,ty,e0,1,0);
	if (sign) {
		*y = -ty[0];
		return -n;
	}
	*y = ty[0];
	return n;
}