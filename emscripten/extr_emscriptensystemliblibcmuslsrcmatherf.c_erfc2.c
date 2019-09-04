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
typedef  double double_t ;

/* Variables and functions */
 int /*<<< orphan*/  SET_LOW_WORD (double,int /*<<< orphan*/ ) ; 
 double erfc1 (double) ; 
 double exp (double) ; 
 double fabs (double) ; 
 double ra0 ; 
 double ra1 ; 
 double ra2 ; 
 double ra3 ; 
 double ra4 ; 
 double ra5 ; 
 double ra6 ; 
 double ra7 ; 
 double rb0 ; 
 double rb1 ; 
 double rb2 ; 
 double rb3 ; 
 double rb4 ; 
 double rb5 ; 
 double rb6 ; 
 double sa1 ; 
 double sa2 ; 
 double sa3 ; 
 double sa4 ; 
 double sa5 ; 
 double sa6 ; 
 double sa7 ; 
 double sa8 ; 
 double sb1 ; 
 double sb2 ; 
 double sb3 ; 
 double sb4 ; 
 double sb5 ; 
 double sb6 ; 
 double sb7 ; 

__attribute__((used)) static double erfc2(uint32_t ix, double x)
{
	double_t s,R,S;
	double z;

	if (ix < 0x3ff40000)  /* |x| < 1.25 */
		return erfc1(x);

	x = fabs(x);
	s = 1/(x*x);
	if (ix < 0x4006db6d) {  /* |x| < 1/.35 ~ 2.85714 */
		R = ra0+s*(ra1+s*(ra2+s*(ra3+s*(ra4+s*(
		     ra5+s*(ra6+s*ra7))))));
		S = 1.0+s*(sa1+s*(sa2+s*(sa3+s*(sa4+s*(
		     sa5+s*(sa6+s*(sa7+s*sa8)))))));
	} else {                /* |x| > 1/.35 */
		R = rb0+s*(rb1+s*(rb2+s*(rb3+s*(rb4+s*(
		     rb5+s*rb6)))));
		S = 1.0+s*(sb1+s*(sb2+s*(sb3+s*(sb4+s*(
		     sb5+s*(sb6+s*sb7))))));
	}
	z = x;
	SET_LOW_WORD(z,0);
	return exp(-z*z-0.5625)*exp((z-x)*(z+x)+R/S)/x;
}