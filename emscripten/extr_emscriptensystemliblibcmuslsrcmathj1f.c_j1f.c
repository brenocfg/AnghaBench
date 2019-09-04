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
 float common (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fabsf (float) ; 
 float r00 ; 
 float r01 ; 
 float r02 ; 
 float r03 ; 
 float s01 ; 
 float s02 ; 
 float s03 ; 
 float s04 ; 
 float s05 ; 

float j1f(float x)
{
	float z,r,s;
	uint32_t ix;
	int sign;

	GET_FLOAT_WORD(ix, x);
	sign = ix>>31;
	ix &= 0x7fffffff;
	if (ix >= 0x7f800000)
		return 1/(x*x);
	if (ix >= 0x40000000)  /* |x| >= 2 */
		return common(ix, fabsf(x), 0, sign);
	if (ix >= 0x32000000) {  /* |x| >= 2**-27 */
		z = x*x;
		r = z*(r00+z*(r01+z*(r02+z*r03)));
		s = 1+z*(s01+z*(s02+z*(s03+z*(s04+z*s05))));
		z = 0.5f + r/s;
	} else
		/* raise inexact if x!=0 */
		z = 0.5f + x;
	return z*x;
}