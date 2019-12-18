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
 unsigned int* exp2s ; 

__attribute__((used)) static unsigned int eexp2(unsigned int s)
{
	int exp, pwr;
	unsigned int mant, frac;

	/* extract exponent field from input */
	exp = ((s >> 23) & 0xff) - 127;
	if (exp > 7) {
		/* check for NaN input */
		if (exp == 128 && (s & 0x7fffff) != 0)
			return s | 0x400000;	/* return QNaN */
		/* 2^-big = 0, 2^+big = +Inf */
		return (s & 0x80000000)? 0: 0x7f800000;	/* 0 or +Inf */
	}
	if (exp < -23)
		return 0x3f800000;	/* 1.0 */

	/* convert to fixed point integer in 9.23 representation */
	pwr = (s & 0x7fffff) | 0x800000;
	if (exp > 0)
		pwr <<= exp;
	else
		pwr >>= -exp;
	if (s & 0x80000000)
		pwr = -pwr;

	/* extract integer part, which becomes exponent part of result */
	exp = (pwr >> 23) + 126;
	if (exp >= 254)
		return 0x7f800000;
	if (exp < -23)
		return 0;

	/* table lookup on top 3 bits of fraction to get mantissa */
	mant = exp2s[(pwr >> 20) & 7];

	/* linear interpolation using remaining 20 bits of fraction */
	asm("mulhwu %0,%1,%2" : "=r" (frac)
	    : "r" (pwr << 12), "r" (0x172b83ff));
	asm("mulhwu %0,%1,%2" : "=r" (frac) : "r" (frac), "r" (mant));
	mant += frac;

	if (exp >= 0)
		return mant + (exp << 23);

	/* denormalized result */
	exp = -exp;
	mant += 1 << (exp - 1);
	return mant >> exp;
}