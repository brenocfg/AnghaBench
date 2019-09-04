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
 float common (int,float,int) ; 
 float j0f (float) ; 
 float logf (float) ; 
 float tpi ; 
 float u00 ; 
 float u01 ; 
 float u02 ; 
 float u03 ; 
 float u04 ; 
 float u05 ; 
 float u06 ; 
 float v01 ; 
 float v02 ; 
 float v03 ; 
 float v04 ; 

float y0f(float x)
{
	float z,u,v;
	uint32_t ix;

	GET_FLOAT_WORD(ix, x);
	if ((ix & 0x7fffffff) == 0)
		return -1/0.0f;
	if (ix>>31)
		return 0/0.0f;
	if (ix >= 0x7f800000)
		return 1/x;
	if (ix >= 0x40000000) {  /* |x| >= 2.0 */
		/* large ulp error near zeros */
		return common(ix,x,1);
	}
	if (ix >= 0x39000000) {  /* x >= 2**-13 */
		/* large ulp error at x ~= 0.89 */
		z = x*x;
		u = u00+z*(u01+z*(u02+z*(u03+z*(u04+z*(u05+z*u06)))));
		v = 1+z*(v01+z*(v02+z*(v03+z*v04)));
		return u/v + tpi*(j0f(x)*logf(x));
	}
	return u00 + tpi*logf(x);
}