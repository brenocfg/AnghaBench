#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bits; } ;
typedef  TYPE_1__ ieee754sp ;

/* Variables and functions */
 int /*<<< orphan*/  CLEARCX ; 
 int /*<<< orphan*/  COMPXSP ; 
 int /*<<< orphan*/  COMPYSP ; 
 int /*<<< orphan*/  EXPLODEXSP ; 
 int /*<<< orphan*/  EXPLODEYSP ; 
 int /*<<< orphan*/  FLUSHXSP ; 
 int /*<<< orphan*/  FLUSHYSP ; 
 int IEEE754_CEQ ; 
 int IEEE754_CGT ; 
 scalar_t__ IEEE754_CLASS_SNAN ; 
 int IEEE754_CLT ; 
 int IEEE754_CUN ; 
 int /*<<< orphan*/  IEEE754_INVALID_OPERATION ; 
 scalar_t__ SETANDTESTCX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETCX (int /*<<< orphan*/ ) ; 
 int SP_SIGN_BIT ; 
 int ieee754si_xcpt (int /*<<< orphan*/ ,char*,TYPE_1__) ; 
 scalar_t__ ieee754sp_isnan (TYPE_1__) ; 
 scalar_t__ xc ; 
 scalar_t__ yc ; 

int ieee754sp_cmp(ieee754sp x, ieee754sp y, int cmp, int sig)
{
	COMPXSP;
	COMPYSP;

	EXPLODEXSP;
	EXPLODEYSP;
	FLUSHXSP;
	FLUSHYSP;
	CLEARCX;	/* Even clear inexact flag here */

	if (ieee754sp_isnan(x) || ieee754sp_isnan(y)) {
		if (sig || xc == IEEE754_CLASS_SNAN || yc == IEEE754_CLASS_SNAN)
			SETCX(IEEE754_INVALID_OPERATION);
		if (cmp & IEEE754_CUN)
			return 1;
		if (cmp & (IEEE754_CLT | IEEE754_CGT)) {
			if (sig && SETANDTESTCX(IEEE754_INVALID_OPERATION))
				return ieee754si_xcpt(0, "fcmpf", x);
		}
		return 0;
	} else {
		int vx = x.bits;
		int vy = y.bits;

		if (vx < 0)
			vx = -vx ^ SP_SIGN_BIT;
		if (vy < 0)
			vy = -vy ^ SP_SIGN_BIT;

		if (vx < vy)
			return (cmp & IEEE754_CLT) != 0;
		else if (vx == vy)
			return (cmp & IEEE754_CEQ) != 0;
		else
			return (cmp & IEEE754_CGT) != 0;
	}
}