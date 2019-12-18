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
typedef  int /*<<< orphan*/  ieee754dp ;
struct TYPE_2__ {int rm; int mx; scalar_t__ nod; } ;

/* Variables and functions */
 scalar_t__ DP_EBIAS ; 
 int DP_EMAX ; 
 int DP_EMIN ; 
 int DP_HIDDEN_BIT ; 
 int DP_MBIT (int) ; 
 int DP_MBITS ; 
 int IEEE754_INEXACT ; 
 int IEEE754_OVERFLOW ; 
#define  IEEE754_RD 131 
#define  IEEE754_RN 130 
#define  IEEE754_RU 129 
#define  IEEE754_RZ 128 
 int IEEE754_UNDERFLOW ; 
 int /*<<< orphan*/  SETCX (int) ; 
 int XDPSRS (int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  builddp (int,scalar_t__,int) ; 
 int get_rounding (int,int) ; 
 TYPE_1__ ieee754_csr ; 
 int /*<<< orphan*/  ieee754dp_inf (int) ; 
 int /*<<< orphan*/  ieee754dp_max (int) ; 
 int /*<<< orphan*/  ieee754dp_min (int) ; 
 int /*<<< orphan*/  ieee754dp_zero (int) ; 

ieee754dp ieee754dp_format(int sn, int xe, u64 xm)
{
	assert(xm);		/* we don't gen exact zeros (probably should) */

	assert((xm >> (DP_MBITS + 1 + 3)) == 0);	/* no execess */
	assert(xm & (DP_HIDDEN_BIT << 3));

	if (xe < DP_EMIN) {
		/* strip lower bits */
		int es = DP_EMIN - xe;

		if (ieee754_csr.nod) {
			SETCX(IEEE754_UNDERFLOW);
			SETCX(IEEE754_INEXACT);

			switch(ieee754_csr.rm) {
			case IEEE754_RN:
				return ieee754dp_zero(sn);
			case IEEE754_RZ:
				return ieee754dp_zero(sn);
			case IEEE754_RU:    /* toward +Infinity */
				if(sn == 0)
					return ieee754dp_min(0);
				else
					return ieee754dp_zero(1);
			case IEEE754_RD:    /* toward -Infinity */
				if(sn == 0)
					return ieee754dp_zero(0);
				else
					return ieee754dp_min(1);
			}
		}

		if (xe == DP_EMIN - 1
				&& get_rounding(sn, xm) >> (DP_MBITS + 1 + 3))
		{
			/* Not tiny after rounding */
			SETCX(IEEE754_INEXACT);
			xm = get_rounding(sn, xm);
			xm >>= 1;
			/* Clear grs bits */
			xm &= ~(DP_MBIT(3) - 1);
			xe++;
		}
		else {
			/* sticky right shift es bits
			 */
			xm = XDPSRS(xm, es);
			xe += es;
			assert((xm & (DP_HIDDEN_BIT << 3)) == 0);
			assert(xe == DP_EMIN);
		}
	}
	if (xm & (DP_MBIT(3) - 1)) {
		SETCX(IEEE754_INEXACT);
		if ((xm & (DP_HIDDEN_BIT << 3)) == 0) {
			SETCX(IEEE754_UNDERFLOW);
		}

		/* inexact must round of 3 bits
		 */
		xm = get_rounding(sn, xm);
		/* adjust exponent for rounding add overflowing
		 */
		if (xm >> (DP_MBITS + 3 + 1)) {
			/* add causes mantissa overflow */
			xm >>= 1;
			xe++;
		}
	}
	/* strip grs bits */
	xm >>= 3;

	assert((xm >> (DP_MBITS + 1)) == 0);	/* no execess */
	assert(xe >= DP_EMIN);

	if (xe > DP_EMAX) {
		SETCX(IEEE754_OVERFLOW);
		SETCX(IEEE754_INEXACT);
		/* -O can be table indexed by (rm,sn) */
		switch (ieee754_csr.rm) {
		case IEEE754_RN:
			return ieee754dp_inf(sn);
		case IEEE754_RZ:
			return ieee754dp_max(sn);
		case IEEE754_RU:	/* toward +Infinity */
			if (sn == 0)
				return ieee754dp_inf(0);
			else
				return ieee754dp_max(1);
		case IEEE754_RD:	/* toward -Infinity */
			if (sn == 0)
				return ieee754dp_max(0);
			else
				return ieee754dp_inf(1);
		}
	}
	/* gen norm/denorm/zero */

	if ((xm & DP_HIDDEN_BIT) == 0) {
		/* we underflow (tiny/zero) */
		assert(xe == DP_EMIN);
		if (ieee754_csr.mx & IEEE754_UNDERFLOW)
			SETCX(IEEE754_UNDERFLOW);
		return builddp(sn, DP_EMIN - 1 + DP_EBIAS, xm);
	} else {
		assert((xm >> (DP_MBITS + 1)) == 0);	/* no execess */
		assert(xm & DP_HIDDEN_BIT);

		return builddp(sn, xe + DP_EBIAS, xm & ~DP_HIDDEN_BIT);
	}
}