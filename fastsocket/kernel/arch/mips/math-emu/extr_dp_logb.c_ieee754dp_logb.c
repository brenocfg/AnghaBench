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
typedef  int /*<<< orphan*/  ieee754dp ;

/* Variables and functions */
 int /*<<< orphan*/  CLEARCX ; 
 int /*<<< orphan*/  COMPXDP ; 
 int /*<<< orphan*/  DPDNORMX ; 
 int /*<<< orphan*/  EXPLODEXDP ; 
#define  IEEE754_CLASS_DNORM 133 
#define  IEEE754_CLASS_INF 132 
#define  IEEE754_CLASS_NORM 131 
#define  IEEE754_CLASS_QNAN 130 
#define  IEEE754_CLASS_SNAN 129 
#define  IEEE754_CLASS_ZERO 128 
 int /*<<< orphan*/  ieee754dp_fint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee754dp_inf (int) ; 
 int /*<<< orphan*/  ieee754dp_nanxcpt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int xc ; 
 int /*<<< orphan*/  xe ; 

ieee754dp ieee754dp_logb(ieee754dp x)
{
	COMPXDP;

	CLEARCX;

	EXPLODEXDP;

	switch (xc) {
	case IEEE754_CLASS_SNAN:
		return ieee754dp_nanxcpt(x, "logb", x);
	case IEEE754_CLASS_QNAN:
		return x;
	case IEEE754_CLASS_INF:
		return ieee754dp_inf(0);
	case IEEE754_CLASS_ZERO:
		return ieee754dp_inf(1);
	case IEEE754_CLASS_DNORM:
		DPDNORMX;
		break;
	case IEEE754_CLASS_NORM:
		break;
	}
	return ieee754dp_fint(xe);
}