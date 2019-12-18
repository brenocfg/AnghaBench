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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCOPY (int,int*,int*,size_t) ; 
 int /*<<< orphan*/  br_i32_montymul (int*,int*,int*,int const*,int) ; 
 int /*<<< orphan*/  br_i32_to_monty (int*,int const*) ; 
 int /*<<< orphan*/  br_i32_zero (int*,int const) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 

void
br_i32_modpow(uint32_t *x,
	const unsigned char *e, size_t elen,
	const uint32_t *m, uint32_t m0i, uint32_t *t1, uint32_t *t2)
{
	size_t mlen;
	uint32_t k;

	/*
	 * 'mlen' is the length of m[] expressed in bytes (including
	 * the "bit length" first field).
	 */
	mlen = ((m[0] + 63) >> 5) * sizeof m[0];

	/*
	 * Throughout the algorithm:
	 * -- t1[] is in Montgomery representation; it contains x, x^2,
	 * x^4, x^8...
	 * -- The result is accumulated, in normal representation, in
	 * the x[] array.
	 * -- t2[] is used as destination buffer for each multiplication.
	 *
	 * Note that there is no need to call br_i32_from_monty().
	 */
	memcpy(t1, x, mlen);
	br_i32_to_monty(t1, m);
	br_i32_zero(x, m[0]);
	x[1] = 1;
	for (k = 0; k < ((uint32_t)elen << 3); k ++) {
		uint32_t ctl;

		ctl = (e[elen - 1 - (k >> 3)] >> (k & 7)) & 1;
		br_i32_montymul(t2, x, t1, m, m0i);
		CCOPY(ctl, x, t2, mlen);
		br_i32_montymul(t2, t1, t1, m, m0i);
		memcpy(t1, t2, mlen);
	}
}