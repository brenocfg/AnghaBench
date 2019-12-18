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
typedef  int u64 ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  ieee754dp ;
struct TYPE_2__ {int rm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEARCX ; 
 int /*<<< orphan*/  COMPXDP ; 
 int DP_HIDDEN_BIT ; 
 int DP_MBITS ; 
 int /*<<< orphan*/  EXPLODEXDP ; 
 int /*<<< orphan*/  FLUSHXDP ; 
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
 TYPE_1__ ieee754_csr ; 
 int /*<<< orphan*/  ieee754di_indef () ; 
 int ieee754di_xcpt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int xc ; 
 int xe ; 
 int xm ; 
 scalar_t__ xs ; 

s64 ieee754dp_tlong(ieee754dp x)
{
	COMPXDP;

	CLEARCX;

	EXPLODEXDP;
	FLUSHXDP;

	switch (xc) {
	case IEEE754_CLASS_SNAN:
	case IEEE754_CLASS_QNAN:
	case IEEE754_CLASS_INF:
		SETCX(IEEE754_INVALID_OPERATION);
		return ieee754di_xcpt(ieee754di_indef(), "dp_tlong", x);
	case IEEE754_CLASS_ZERO:
		return 0;
	case IEEE754_CLASS_DNORM:
	case IEEE754_CLASS_NORM:
		break;
	}
	if (xe >= 63) {
		/* look for valid corner case */
		if (xe == 63 && xs && xm == DP_HIDDEN_BIT)
			return -0x8000000000000000LL;
		/* Set invalid. We will only use overflow for floating
		   point overflow */
		SETCX(IEEE754_INVALID_OPERATION);
		return ieee754di_xcpt(ieee754di_indef(), "dp_tlong", x);
	}
	/* oh gawd */
	if (xe > DP_MBITS) {
		xm <<= xe - DP_MBITS;
	} else if (xe < DP_MBITS) {
		u64 residue;
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
			/* Shifting a u64 64 times does not work,
			* so we do it in two steps. Be aware that xe
			* may be -1 */
			residue = xm << (xe + 1);
			residue <<= 63 - DP_MBITS;
			round = (residue >> 63) != 0;
			sticky = (residue << 1) != 0;
			xm >>= DP_MBITS - xe;
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
		if ((xm >> 63) != 0) {
			/* This can happen after rounding */
			SETCX(IEEE754_INVALID_OPERATION);
			return ieee754di_xcpt(ieee754di_indef(), "dp_tlong", x);
		}
		if (round || sticky)
			SETCX(IEEE754_INEXACT);
	}
	if (xs)
		return -xm;
	else
		return xm;
}