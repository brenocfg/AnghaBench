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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCOPY (int /*<<< orphan*/ ,int*,int*,size_t) ; 
 int EQ (size_t,int) ; 
 int /*<<< orphan*/  NEQ (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_i15_from_monty (int*,int const*,int) ; 
 int /*<<< orphan*/  br_i15_montymul (int*,int*,int*,int const*,int) ; 
 int /*<<< orphan*/  br_i15_muladd_small (int*,int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/  br_i15_to_monty (int*,int const*) ; 
 int /*<<< orphan*/  br_i15_zero (int*,int const) ; 
 int /*<<< orphan*/  memcpy (int*,int*,size_t) ; 

uint32_t
br_i15_modpow_opt(uint16_t *x,
	const unsigned char *e, size_t elen,
	const uint16_t *m, uint16_t m0i, uint16_t *tmp, size_t twlen)
{
	size_t mlen, mwlen;
	uint16_t *t1, *t2, *base;
	size_t u, v;
	uint32_t acc;
	int acc_len, win_len;

	/*
	 * Get modulus size.
	 */
	mwlen = (m[0] + 31) >> 4;
	mlen = mwlen * sizeof m[0];
	mwlen += (mwlen & 1);
	t1 = tmp;
	t2 = tmp + mwlen;

	/*
	 * Compute possible window size, with a maximum of 5 bits.
	 * When the window has size 1 bit, we use a specific code
	 * that requires only two temporaries. Otherwise, for a
	 * window of k bits, we need 2^k+1 temporaries.
	 */
	if (twlen < (mwlen << 1)) {
		return 0;
	}
	for (win_len = 5; win_len > 1; win_len --) {
		if ((((uint32_t)1 << win_len) + 1) * mwlen <= twlen) {
			break;
		}
	}

	/*
	 * Everything is done in Montgomery representation.
	 */
	br_i15_to_monty(x, m);

	/*
	 * Compute window contents. If the window has size one bit only,
	 * then t2 is set to x; otherwise, t2[0] is left untouched, and
	 * t2[k] is set to x^k (for k >= 1).
	 */
	if (win_len == 1) {
		memcpy(t2, x, mlen);
	} else {
		memcpy(t2 + mwlen, x, mlen);
		base = t2 + mwlen;
		for (u = 2; u < ((unsigned)1 << win_len); u ++) {
			br_i15_montymul(base + mwlen, base, x, m, m0i);
			base += mwlen;
		}
	}

	/*
	 * We need to set x to 1, in Montgomery representation. This can
	 * be done efficiently by setting the high word to 1, then doing
	 * one word-sized shift.
	 */
	br_i15_zero(x, m[0]);
	x[(m[0] + 15) >> 4] = 1;
	br_i15_muladd_small(x, 0, m);

	/*
	 * We process bits from most to least significant. At each
	 * loop iteration, we have acc_len bits in acc.
	 */
	acc = 0;
	acc_len = 0;
	while (acc_len > 0 || elen > 0) {
		int i, k;
		uint32_t bits;

		/*
		 * Get the next bits.
		 */
		k = win_len;
		if (acc_len < win_len) {
			if (elen > 0) {
				acc = (acc << 8) | *e ++;
				elen --;
				acc_len += 8;
			} else {
				k = acc_len;
			}
		}
		bits = (acc >> (acc_len - k)) & (((uint32_t)1 << k) - 1);
		acc_len -= k;

		/*
		 * We could get exactly k bits. Compute k squarings.
		 */
		for (i = 0; i < k; i ++) {
			br_i15_montymul(t1, x, x, m, m0i);
			memcpy(x, t1, mlen);
		}

		/*
		 * Window lookup: we want to set t2 to the window
		 * lookup value, assuming the bits are non-zero. If
		 * the window length is 1 bit only, then t2 is
		 * already set; otherwise, we do a constant-time lookup.
		 */
		if (win_len > 1) {
			br_i15_zero(t2, m[0]);
			base = t2 + mwlen;
			for (u = 1; u < ((uint32_t)1 << k); u ++) {
				uint32_t mask;

				mask = -EQ(u, bits);
				for (v = 1; v < mwlen; v ++) {
					t2[v] |= mask & base[v];
				}
				base += mwlen;
			}
		}

		/*
		 * Multiply with the looked-up value. We keep the
		 * product only if the exponent bits are not all-zero.
		 */
		br_i15_montymul(t1, x, t2, m, m0i);
		CCOPY(NEQ(bits, 0), x, t1, mlen);
	}

	/*
	 * Convert back from Montgomery representation, and exit.
	 */
	br_i15_from_monty(x, m, m0i);
	return 1;
}