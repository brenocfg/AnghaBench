#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  ieee754sp ;
struct TYPE_2__ {int rm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEARCX ; 
 int /*<<< orphan*/  COMPXSP ; 
 int /*<<< orphan*/  EXPLODEXSP ; 
 int /*<<< orphan*/  FLUSHXSP ; 
#define  IEEE754_CLASS_DNORM 137 
#define  IEEE754_CLASS_INF 136 
#define  IEEE754_CLASS_NORM 135 
#define  IEEE754_CLASS_QNAN 134 
#define  IEEE754_CLASS_SNAN 133 
#define  IEEE754_CLASS_ZERO 132 
 int /*<<< orphan*/  IEEE754_INEXACT ; 
 int /*<<< orphan*/  IEEE754_INVALID_OPERATION ; 
#define  IEEE754_RD 131 
#define  IEEE754_RN 130 
#define  IEEE754_RU 129 
#define  IEEE754_RZ 128 
 int /*<<< orphan*/  SETCX (int /*<<< orphan*/ ) ; 
 int SP_HIDDEN_BIT ; 
 int SP_MBITS ; 
 TYPE_1__ ieee754_csr ; 
 int /*<<< orphan*/  ieee754si_indef () ; 
 int ieee754si_xcpt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int xc ; 
 int xe ; 
 int xm ; 
 scalar_t__ xs ; 

int ieee754sp_tint(ieee754sp x)
{
	COMPXSP;

	CLEARCX;

	EXPLODEXSP;
	FLUSHXSP;

	switch (xc) {
	case IEEE754_CLASS_SNAN:
	case IEEE754_CLASS_QNAN:
	case IEEE754_CLASS_INF:
		SETCX(IEEE754_INVALID_OPERATION);
		return ieee754si_xcpt(ieee754si_indef(), "sp_tint", x);
	case IEEE754_CLASS_ZERO:
		return 0;
	case IEEE754_CLASS_DNORM:
	case IEEE754_CLASS_NORM:
		break;
	}
	if (xe >= 31) {
		/* look for valid corner case */
		if (xe == 31 && xs && xm == SP_HIDDEN_BIT)
			return -0x80000000;
		/* Set invalid. We will only use overflow for floating
		   point overflow */
		SETCX(IEEE754_INVALID_OPERATION);
		return ieee754si_xcpt(ieee754si_indef(), "sp_tint", x);
	}
	/* oh gawd */
	if (xe > SP_MBITS) {
		xm <<= xe - SP_MBITS;
	} else {
		u32 residue;
		int round;
		int sticky;
		int odd;

		if (xe < -1) {
			residue = xm;
			round = 0;
			sticky = residue != 0;
			xm = 0;
		}
		else {
			/* Shifting a u32 32 times does not work,
			* so we do it in two steps. Be aware that xe
			* may be -1 */
			residue = xm << (xe + 1);
			residue <<= 31 - SP_MBITS;
			round = (residue >> 31) != 0;
			sticky = (residue << 1) != 0;
			xm >>= SP_MBITS - xe;
		}
		odd = (xm & 0x1) != 0x0;
		switch (ieee754_csr.rm) {
		case IEEE754_RN:
			if (round && (sticky || odd))
				xm++;
			break;
		case IEEE754_RZ:
			break;
		case IEEE754_RU:	/* toward +Infinity */
			if ((round || sticky) && !xs)
				xm++;
			break;
		case IEEE754_RD:	/* toward -Infinity */
			if ((round || sticky) && xs)
				xm++;
			break;
		}
		if ((xm >> 31) != 0) {
			/* This can happen after rounding */
			SETCX(IEEE754_INVALID_OPERATION);
			return ieee754si_xcpt(ieee754si_indef(), "sp_tint", x);
		}
		if (round || sticky)
			SETCX(IEEE754_INEXACT);
	}
	if (xs)
		return -xm;
	else
		return xm;
}