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
 int /*<<< orphan*/  GET_HIGH_WORD (int,double) ; 
 double R02 ; 
 double R03 ; 
 double R04 ; 
 double R05 ; 
 double S01 ; 
 double S02 ; 
 double S03 ; 
 double S04 ; 
 double common (int,double,int /*<<< orphan*/ ) ; 
 double fabs (double) ; 

double j0(double x)
{
	double z,r,s;
	uint32_t ix;

	GET_HIGH_WORD(ix, x);
	ix &= 0x7fffffff;

	/* j0(+-inf)=0, j0(nan)=nan */
	if (ix >= 0x7ff00000)
		return 1/(x*x);
	x = fabs(x);

	if (ix >= 0x40000000) {  /* |x| >= 2 */
		/* large ulp error near zeros: 2.4, 5.52, 8.6537,.. */
		return common(ix,x,0);
	}

	/* 1 - x*x/4 + x*x*R(x^2)/S(x^2) */
	if (ix >= 0x3f200000) {  /* |x| >= 2**-13 */
		/* up to 4ulp error close to 2 */
		z = x*x;
		r = z*(R02+z*(R03+z*(R04+z*R05)));
		s = 1+z*(S01+z*(S02+z*(S03+z*S04)));
		return (1+x/2)*(1-x/2) + z*(r/s);
	}

	/* 1 - x*x/4 */
	/* prevent underflow */
	/* inexact should be raised when x!=0, this is not done correctly */
	if (ix >= 0x38000000)  /* |x| >= 2**-127 */
		x = 0.25*x*x;
	return 1 - x;
}