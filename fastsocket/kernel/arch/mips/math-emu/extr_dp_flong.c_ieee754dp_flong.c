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
typedef  int s64 ;
typedef  int /*<<< orphan*/  ieee754dp ;

/* Variables and functions */
 int /*<<< orphan*/  CLEARCX ; 
 int /*<<< orphan*/  DPNORMRET1 (int,int,int,char*,int) ; 
 int DP_MBITS ; 
 int /*<<< orphan*/  XDPSRSX1 () ; 
 int /*<<< orphan*/  ieee754dp_one (int) ; 
 int /*<<< orphan*/  ieee754dp_ten (int) ; 
 int /*<<< orphan*/  ieee754dp_zero (int /*<<< orphan*/ ) ; 

ieee754dp ieee754dp_flong(s64 x)
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
		if (x == (1ULL << 63))
			xm = (1ULL << 63);	/* max neg can't be safely negated */
		else
			xm = -x;
	} else {
		xm = x;
	}

	/* normalize */
	xe = DP_MBITS + 3;
	if (xm >> (DP_MBITS + 1 + 3)) {
		/* shunt out overflow bits */
		while (xm >> (DP_MBITS + 1 + 3)) {
			XDPSRSX1();
		}
	} else {
		/* normalize in grs extended double precision */
		while ((xm >> (DP_MBITS + 3)) == 0) {
			xm <<= 1;
			xe--;
		}
	}
	DPNORMRET1(xs, xe, xm, "dp_flong", x);
}