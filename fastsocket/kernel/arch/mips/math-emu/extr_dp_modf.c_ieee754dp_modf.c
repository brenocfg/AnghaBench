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
 scalar_t__ DP_EBIAS ; 
 scalar_t__ DP_HIDDEN_BIT ; 
 scalar_t__ DP_MBITS ; 
 int /*<<< orphan*/  EXPLODEXDP ; 
#define  IEEE754_CLASS_DNORM 133 
#define  IEEE754_CLASS_INF 132 
#define  IEEE754_CLASS_NORM 131 
#define  IEEE754_CLASS_QNAN 130 
#define  IEEE754_CLASS_SNAN 129 
#define  IEEE754_CLASS_ZERO 128 
 int /*<<< orphan*/  builddp (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ieee754dp_zero (int /*<<< orphan*/ ) ; 
 int xc ; 
 scalar_t__ xe ; 
 scalar_t__ xm ; 
 int /*<<< orphan*/  xs ; 

ieee754dp ieee754dp_modf(ieee754dp x, ieee754dp * ip)
{
	COMPXDP;

	CLEARCX;

	EXPLODEXDP;

	switch (xc) {
	case IEEE754_CLASS_SNAN:
	case IEEE754_CLASS_QNAN:
	case IEEE754_CLASS_INF:
	case IEEE754_CLASS_ZERO:
		*ip = x;
		return x;
	case IEEE754_CLASS_DNORM:
		/* far to small */
		*ip = ieee754dp_zero(xs);
		return x;
	case IEEE754_CLASS_NORM:
		break;
	}
	if (xe < 0) {
		*ip = ieee754dp_zero(xs);
		return x;
	}
	if (xe >= DP_MBITS) {
		*ip = x;
		return ieee754dp_zero(xs);
	}
	/* generate ipart mantissa by clearing bottom bits
	 */
	*ip = builddp(xs, xe + DP_EBIAS,
		      ((xm >> (DP_MBITS - xe)) << (DP_MBITS - xe)) &
		      ~DP_HIDDEN_BIT);

	/* generate fpart mantissa by clearing top bits
	 * and normalizing (must be able to normalize)
	 */
	xm = (xm << (64 - (DP_MBITS - xe))) >> (64 - (DP_MBITS - xe));
	if (xm == 0)
		return ieee754dp_zero(xs);

	while ((xm >> DP_MBITS) == 0) {
		xm <<= 1;
		xe--;
	}
	return builddp(xs, xe + DP_EBIAS, xm & ~DP_HIDDEN_BIT);
}