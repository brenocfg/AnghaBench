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
typedef  int /*<<< orphan*/  ieee754sp ;
struct TYPE_2__ {int rm; int mx; scalar_t__ nod; } ;

/* Variables and functions */
 int IEEE754_INEXACT ; 
 int IEEE754_OVERFLOW ; 
#define  IEEE754_RD 131 
#define  IEEE754_RN 130 
#define  IEEE754_RU 129 
#define  IEEE754_RZ 128 
 int IEEE754_UNDERFLOW ; 
 int /*<<< orphan*/  SETCX (int) ; 
 int /*<<< orphan*/  SPXSRSXn (int) ; 
 scalar_t__ SP_EBIAS ; 
 int SP_EMAX ; 
 int SP_EMIN ; 
 int SP_HIDDEN_BIT ; 
 int SP_MBIT (int) ; 
 int SP_MBITS ; 
 int /*<<< orphan*/  assert (unsigned int) ; 
 int /*<<< orphan*/  buildsp (int,scalar_t__,unsigned int) ; 
 int get_rounding (int,unsigned int) ; 
 TYPE_1__ ieee754_csr ; 
 int /*<<< orphan*/  ieee754sp_inf (int) ; 
 int /*<<< orphan*/  ieee754sp_max (int) ; 
 int /*<<< orphan*/  ieee754sp_min (int) ; 
 int /*<<< orphan*/  ieee754sp_zero (int) ; 

ieee754sp ieee754sp_format(int sn, int xe, unsigned xm)
{
	assert(xm);		/* we don't gen exact zeros (probably should) */

	assert((xm >> (SP_MBITS + 1 + 3)) == 0);	/* no execess */
	assert(xm & (SP_HIDDEN_BIT << 3));

	if (xe < SP_EMIN) {
		/* strip lower bits */
		int es = SP_EMIN - xe;

		if (ieee754_csr.nod) {
			SETCX(IEEE754_UNDERFLOW);
			SETCX(IEEE754_INEXACT);

			switch(ieee754_csr.rm) {
			case IEEE754_RN:
				return ieee754sp_zero(sn);
			case IEEE754_RZ:
				return ieee754sp_zero(sn);
			case IEEE754_RU:      /* toward +Infinity */
				if(sn == 0)
					return ieee754sp_min(0);
				else
					return ieee754sp_zero(1);
			case IEEE754_RD:      /* toward -Infinity */
				if(sn == 0)
					return ieee754sp_zero(0);
				else
					return ieee754sp_min(1);
			}
		}

		if (xe == SP_EMIN - 1
				&& get_rounding(sn, xm) >> (SP_MBITS + 1 + 3))
		{
			/* Not tiny after rounding */
			SETCX(IEEE754_INEXACT);
			xm = get_rounding(sn, xm);
			xm >>= 1;
			/* Clear grs bits */
			xm &= ~(SP_MBIT(3) - 1);
			xe++;
		}
		else {
			/* sticky right shift es bits
			 */
			SPXSRSXn(es);
			assert((xm & (SP_HIDDEN_BIT << 3)) == 0);
			assert(xe == SP_EMIN);
		}
	}
	if (xm & (SP_MBIT(3) - 1)) {
		SETCX(IEEE754_INEXACT);
		if ((xm & (SP_HIDDEN_BIT << 3)) == 0) {
			SETCX(IEEE754_UNDERFLOW);
		}

		/* inexact must round of 3 bits
		 */
		xm = get_rounding(sn, xm);
		/* adjust exponent for rounding add overflowing
		 */
		if (xm >> (SP_MBITS + 1 + 3)) {
			/* add causes mantissa overflow */
			xm >>= 1;
			xe++;
		}
	}
	/* strip grs bits */
	xm >>= 3;

	assert((xm >> (SP_MBITS + 1)) == 0);	/* no execess */
	assert(xe >= SP_EMIN);

	if (xe > SP_EMAX) {
		SETCX(IEEE754_OVERFLOW);
		SETCX(IEEE754_INEXACT);
		/* -O can be table indexed by (rm,sn) */
		switch (ieee754_csr.rm) {
		case IEEE754_RN:
			return ieee754sp_inf(sn);
		case IEEE754_RZ:
			return ieee754sp_max(sn);
		case IEEE754_RU:	/* toward +Infinity */
			if (sn == 0)
				return ieee754sp_inf(0);
			else
				return ieee754sp_max(1);
		case IEEE754_RD:	/* toward -Infinity */
			if (sn == 0)
				return ieee754sp_max(0);
			else
				return ieee754sp_inf(1);
		}
	}
	/* gen norm/denorm/zero */

	if ((xm & SP_HIDDEN_BIT) == 0) {
		/* we underflow (tiny/zero) */
		assert(xe == SP_EMIN);
		if (ieee754_csr.mx & IEEE754_UNDERFLOW)
			SETCX(IEEE754_UNDERFLOW);
		return buildsp(sn, SP_EMIN - 1 + SP_EBIAS, xm);
	} else {
		assert((xm >> (SP_MBITS + 1)) == 0);	/* no execess */
		assert(xm & SP_HIDDEN_BIT);

		return buildsp(sn, xe + SP_EBIAS, xm & ~SP_HIDDEN_BIT);
	}
}