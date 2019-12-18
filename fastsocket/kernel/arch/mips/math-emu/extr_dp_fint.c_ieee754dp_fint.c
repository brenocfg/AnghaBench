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
typedef  int u64 ;
typedef  int /*<<< orphan*/  ieee754dp ;

/* Variables and functions */
 int /*<<< orphan*/  CLEARCX ; 
 int /*<<< orphan*/  DPNORMRET1 (int,int,int,char*,int) ; 
 scalar_t__ DP_EBIAS ; 
 int DP_HIDDEN_BIT ; 
 int DP_MBITS ; 
 int /*<<< orphan*/  builddp (int,scalar_t__,int) ; 
 int /*<<< orphan*/  ieee754dp_one (int) ; 
 int /*<<< orphan*/  ieee754dp_ten (int) ; 
 int /*<<< orphan*/  ieee754dp_zero (int /*<<< orphan*/ ) ; 

ieee754dp ieee754dp_fint(int x)
{
	u64 xm;
	int xe;
	int xs;

	CLEARCX;

	if (x == 0)
		return ieee754dp_zero(0);
	if (x == 1 || x == -1)
		return ieee754dp_one(x < 0);
	if (x == 10 || x == -10)
		return ieee754dp_ten(x < 0);

	xs = (x < 0);
	if (xs) {
		if (x == (1 << 31))
			xm = ((unsigned) 1 << 31);	/* max neg can't be safely negated */
		else
			xm = -x;
	} else {
		xm = x;
	}

#if 1
	/* normalize - result can never be inexact or overflow */
	xe = DP_MBITS;
	while ((xm >> DP_MBITS) == 0) {
		xm <<= 1;
		xe--;
	}
	return builddp(xs, xe + DP_EBIAS, xm & ~DP_HIDDEN_BIT);
#else
	/* normalize */
	xe = DP_MBITS + 3;
	while ((xm >> (DP_MBITS + 3)) == 0) {
		xm <<= 1;
		xe--;
	}
	DPNORMRET1(xs, xe, xm, "fint", x);
#endif
}