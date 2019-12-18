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
typedef  int /*<<< orphan*/  ieee754sp ;

/* Variables and functions */
 int /*<<< orphan*/  CLEARCX ; 
 int /*<<< orphan*/  COMPXSP ; 
 int /*<<< orphan*/  EXPLODEXSP ; 
#define  IEEE754_CLASS_DNORM 133 
#define  IEEE754_CLASS_INF 132 
#define  IEEE754_CLASS_NORM 131 
#define  IEEE754_CLASS_QNAN 130 
#define  IEEE754_CLASS_SNAN 129 
#define  IEEE754_CLASS_ZERO 128 
 int /*<<< orphan*/  SPDNORMX ; 
 scalar_t__ SP_EBIAS ; 
 int SP_HIDDEN_BIT ; 
 int /*<<< orphan*/  buildsp (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int xc ; 
 int xe ; 
 int xm ; 
 int /*<<< orphan*/  xs ; 

ieee754sp ieee754sp_frexp(ieee754sp x, int *eptr)
{
	COMPXSP;
	CLEARCX;
	EXPLODEXSP;

	switch (xc) {
	case IEEE754_CLASS_SNAN:
	case IEEE754_CLASS_QNAN:
	case IEEE754_CLASS_INF:
	case IEEE754_CLASS_ZERO:
		*eptr = 0;
		return x;
	case IEEE754_CLASS_DNORM:
		SPDNORMX;
		break;
	case IEEE754_CLASS_NORM:
		break;
	}
	*eptr = xe + 1;
	return buildsp(xs, -1 + SP_EBIAS, xm & ~SP_HIDDEN_BIT);
}