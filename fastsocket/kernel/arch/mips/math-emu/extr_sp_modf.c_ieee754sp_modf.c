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
 scalar_t__ SP_EBIAS ; 
 scalar_t__ SP_HIDDEN_BIT ; 
 scalar_t__ SP_MBITS ; 
 int /*<<< orphan*/  buildsp (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ieee754sp_zero (int /*<<< orphan*/ ) ; 
 int xc ; 
 scalar_t__ xe ; 
 scalar_t__ xm ; 
 int /*<<< orphan*/  xs ; 

ieee754sp ieee754sp_modf(ieee754sp x, ieee754sp * ip)
{
	COMPXSP;

	CLEARCX;

	EXPLODEXSP;

	switch (xc) {
	case IEEE754_CLASS_SNAN:
	case IEEE754_CLASS_QNAN:
	case IEEE754_CLASS_INF:
	case IEEE754_CLASS_ZERO:
		*ip = x;
		return x;
	case IEEE754_CLASS_DNORM:
		/* far to small */
		*ip = ieee754sp_zero(xs);
		return x;
	case IEEE754_CLASS_NORM:
		break;
	}
	if (xe < 0) {
		*ip = ieee754sp_zero(xs);
		return x;
	}
	if (xe >= SP_MBITS) {
		*ip = x;
		return ieee754sp_zero(xs);
	}
	/* generate ipart mantissa by clearing bottom bits
	 */
	*ip = buildsp(xs, xe + SP_EBIAS,
		      ((xm >> (SP_MBITS - xe)) << (SP_MBITS - xe)) &
		      ~SP_HIDDEN_BIT);

	/* generate fpart mantissa by clearing top bits
	 * and normalizing (must be able to normalize)
	 */
	xm = (xm << (32 - (SP_MBITS - xe))) >> (32 - (SP_MBITS - xe));
	if (xm == 0)
		return ieee754sp_zero(xs);

	while ((xm >> SP_MBITS) == 0) {
		xm <<= 1;
		xe--;
	}
	return buildsp(xs, xe + SP_EBIAS, xm & ~SP_HIDDEN_BIT);
}