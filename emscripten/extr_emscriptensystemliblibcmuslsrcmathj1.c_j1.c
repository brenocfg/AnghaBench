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
 double common (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fabs (double) ; 
 double r00 ; 
 double r01 ; 
 double r02 ; 
 double r03 ; 
 double s01 ; 
 double s02 ; 
 double s03 ; 
 double s04 ; 
 double s05 ; 

double j1(double x)
{
	double z,r,s;
	uint32_t ix;
	int sign;

	GET_HIGH_WORD(ix, x);
	sign = ix>>31;
	ix &= 0x7fffffff;
	if (ix >= 0x7ff00000)
		return 1/(x*x);
	if (ix >= 0x40000000)  /* |x| >= 2 */
		return common(ix, fabs(x), 0, sign);
	if (ix >= 0x38000000) {  /* |x| >= 2**-127 */
		z = x*x;
		r = z*(r00+z*(r01+z*(r02+z*r03)));
		s = 1+z*(s01+z*(s02+z*(s03+z*(s04+z*s05))));
		z = r/s;
	} else
		/* avoid underflow, raise inexact if x!=0 */
		z = x;
	return (0.5 + z)*x;
}