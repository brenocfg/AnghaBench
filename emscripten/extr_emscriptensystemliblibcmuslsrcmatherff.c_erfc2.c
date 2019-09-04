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
typedef  float float_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_FLOAT_WORD (int,float) ; 
 int /*<<< orphan*/  SET_FLOAT_WORD (float,int) ; 
 float erfc1 (float) ; 
 float expf (float) ; 
 float fabsf (float) ; 
 float ra0 ; 
 float ra1 ; 
 float ra2 ; 
 float ra3 ; 
 float ra4 ; 
 float ra5 ; 
 float ra6 ; 
 float ra7 ; 
 float rb0 ; 
 float rb1 ; 
 float rb2 ; 
 float rb3 ; 
 float rb4 ; 
 float rb5 ; 
 float rb6 ; 
 float sa1 ; 
 float sa2 ; 
 float sa3 ; 
 float sa4 ; 
 float sa5 ; 
 float sa6 ; 
 float sa7 ; 
 float sa8 ; 
 float sb1 ; 
 float sb2 ; 
 float sb3 ; 
 float sb4 ; 
 float sb5 ; 
 float sb6 ; 
 float sb7 ; 

__attribute__((used)) static float erfc2(uint32_t ix, float x)
{
	float_t s,R,S;
	float z;

	if (ix < 0x3fa00000)  /* |x| < 1.25 */
		return erfc1(x);

	x = fabsf(x);
	s = 1/(x*x);
	if (ix < 0x4036db6d) {   /* |x| < 1/0.35 */
		R = ra0+s*(ra1+s*(ra2+s*(ra3+s*(ra4+s*(
		     ra5+s*(ra6+s*ra7))))));
		S = 1.0f+s*(sa1+s*(sa2+s*(sa3+s*(sa4+s*(
		     sa5+s*(sa6+s*(sa7+s*sa8)))))));
	} else {                 /* |x| >= 1/0.35 */
		R = rb0+s*(rb1+s*(rb2+s*(rb3+s*(rb4+s*(
		     rb5+s*rb6)))));
		S = 1.0f+s*(sb1+s*(sb2+s*(sb3+s*(sb4+s*(
		     sb5+s*(sb6+s*sb7))))));
	}
	GET_FLOAT_WORD(ix, x);
	SET_FLOAT_WORD(z, ix&0xffffe000);
	return expf(-z*z - 0.5625f) * expf((z-x)*(z+x) + R/S)/x;
}