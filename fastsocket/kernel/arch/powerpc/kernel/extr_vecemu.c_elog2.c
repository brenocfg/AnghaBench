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

/* Variables and functions */

__attribute__((used)) static unsigned int elog2(unsigned int s)
{
	int exp, mant, lz, frac;

	exp = s & 0x7f800000;
	mant = s & 0x7fffff;
	if (exp == 0x7f800000) {	/* Inf or NaN */
		if (mant != 0)
			s |= 0x400000;	/* turn NaN into QNaN */
		return s;
	}
	if ((exp | mant) == 0)		/* +0 or -0 */
		return 0xff800000;	/* return -Inf */

	if (exp == 0) {
		/* denormalized */
		asm("cntlzw %0,%1" : "=r" (lz) : "r" (mant));
		mant <<= lz - 8;
		exp = (-118 - lz) << 23;
	} else {
		mant |= 0x800000;
		exp -= 127 << 23;
	}

	if (mant >= 0xb504f3) {				/* 2^0.5 * 2^23 */
		exp |= 0x400000;			/* 0.5 * 2^23 */
		asm("mulhwu %0,%1,%2" : "=r" (mant)
		    : "r" (mant), "r" (0xb504f334));	/* 2^-0.5 * 2^32 */
	}
	if (mant >= 0x9837f0) {				/* 2^0.25 * 2^23 */
		exp |= 0x200000;			/* 0.25 * 2^23 */
		asm("mulhwu %0,%1,%2" : "=r" (mant)
		    : "r" (mant), "r" (0xd744fccb));	/* 2^-0.25 * 2^32 */
	}
	if (mant >= 0x8b95c2) {				/* 2^0.125 * 2^23 */
		exp |= 0x100000;			/* 0.125 * 2^23 */
		asm("mulhwu %0,%1,%2" : "=r" (mant)
		    : "r" (mant), "r" (0xeac0c6e8));	/* 2^-0.125 * 2^32 */
	}
	if (mant > 0x800000) {				/* 1.0 * 2^23 */
		/* calculate (mant - 1) * 1.381097463 */
		/* 1.381097463 == 0.125 / (2^0.125 - 1) */
		asm("mulhwu %0,%1,%2" : "=r" (frac)
		    : "r" ((mant - 0x800000) << 1), "r" (0xb0c7cd3a));
		exp += frac;
	}
	s = exp & 0x80000000;
	if (exp != 0) {
		if (s)
			exp = -exp;
		asm("cntlzw %0,%1" : "=r" (lz) : "r" (exp));
		lz = 8 - lz;
		if (lz > 0)
			exp >>= lz;
		else if (lz < 0)
			exp <<= -lz;
		s += ((lz + 126) << 23) + exp;
	}
	return s;
}