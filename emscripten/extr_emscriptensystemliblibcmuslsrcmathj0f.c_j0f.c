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
 float R02 ; 
 float R03 ; 
 float R04 ; 
 float R05 ; 
 float S01 ; 
 float S02 ; 
 float S03 ; 
 float S04 ; 
 float common (int,float,int /*<<< orphan*/ ) ; 
 float fabsf (float) ; 

float j0f(float x)
{
	float z,r,s;
	uint32_t ix;

	GET_FLOAT_WORD(ix, x);
	ix &= 0x7fffffff;
	if (ix >= 0x7f800000)
		return 1/(x*x);
	x = fabsf(x);

	if (ix >= 0x40000000) {  /* |x| >= 2 */
		/* large ulp error near zeros */
		return common(ix, x, 0);
	}
	if (ix >= 0x3a000000) {  /* |x| >= 2**-11 */
		/* up to 4ulp error near 2 */
		z = x*x;
		r = z*(R02+z*(R03+z*(R04+z*R05)));
		s = 1+z*(S01+z*(S02+z*(S03+z*S04)));
		return (1+x/2)*(1-x/2) + z*(r/s);
	}
	if (ix >= 0x21800000)  /* |x| >= 2**-60 */
		x = 0.25f*x*x;
	return 1 - x;
}