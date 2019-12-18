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
 int /*<<< orphan*/  EQ (int,int) ; 
 int GT (int,int) ; 
 int LT (int,int) ; 
 int MUL15 (int,int) ; 
 int MUX (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  br_i15_add (int*,int const*,int) ; 
 int /*<<< orphan*/  br_i15_sub (int*,int const*,int) ; 
 int divrem16 (int,int const,int*) ; 
 int /*<<< orphan*/  memmove (int*,int*,size_t) ; 

void
br_i15_muladd_small(uint16_t *x, uint16_t z, const uint16_t *m)
{
	/*
	 * Constant-time: we accept to leak the exact bit length of the
	 * modulus m.
	 */
	unsigned m_bitlen, mblr;
	size_t u, mlen;
	uint32_t hi, a0, a, b, q;
	uint32_t cc, tb, over, under;

	/*
	 * Simple case: the modulus fits on one word.
	 */
	m_bitlen = m[0];
	if (m_bitlen == 0) {
		return;
	}
	if (m_bitlen <= 15) {
		uint32_t rem;

		divrem16(((uint32_t)x[1] << 15) | z, m[1], &rem);
		x[1] = rem;
		return;
	}
	mlen = (m_bitlen + 15) >> 4;
	mblr = m_bitlen & 15;

	/*
	 * Principle: we estimate the quotient (x*2^15+z)/m by
	 * doing a 30/15 division with the high words.
	 *
	 * Let:
	 *   w = 2^15
	 *   a = (w*a0 + a1) * w^N + a2
	 *   b = b0 * w^N + b2
	 * such that:
	 *   0 <= a0 < w
	 *   0 <= a1 < w
	 *   0 <= a2 < w^N
	 *   w/2 <= b0 < w
	 *   0 <= b2 < w^N
	 *   a < w*b
	 * I.e. the two top words of a are a0:a1, the top word of b is
	 * b0, we ensured that b0 is "full" (high bit set), and a is
	 * such that the quotient q = a/b fits on one word (0 <= q < w).
	 *
	 * If a = b*q + r (with 0 <= r < q), then we can estimate q by
	 * using a division on the top words:
	 *   a0*w + a1 = b0*u + v (with 0 <= v < b0)
	 * Then the following holds:
	 *   0 <= u <= w
	 *   u-2 <= q <= u
	 */
	hi = x[mlen];
	if (mblr == 0) {
		a0 = x[mlen];
		memmove(x + 2, x + 1, (mlen - 1) * sizeof *x);
		x[1] = z;
		a = (a0 << 15) + x[mlen];
		b = m[mlen];
	} else {
		a0 = (x[mlen] << (15 - mblr)) | (x[mlen - 1] >> mblr);
		memmove(x + 2, x + 1, (mlen - 1) * sizeof *x);
		x[1] = z;
		a = (a0 << 15) | (((x[mlen] << (15 - mblr))
			| (x[mlen - 1] >> mblr)) & 0x7FFF);
		b = (m[mlen] << (15 - mblr)) | (m[mlen - 1] >> mblr);
	}
	q = divrem16(a, b, NULL);

	/*
	 * We computed an estimate for q, but the real one may be q,
	 * q-1 or q-2; moreover, the division may have returned a value
	 * 8000 or even 8001 if the two high words were identical, and
	 * we want to avoid values beyond 7FFF. We thus adjust q so
	 * that the "true" multiplier will be q+1, q or q-1, and q is
	 * in the 0000..7FFF range.
	 */
	q = MUX(EQ(b, a0), 0x7FFF, q - 1 + ((q - 1) >> 31));

	/*
	 * We subtract q*m from x (x has an extra high word of value 'hi').
	 * Since q may be off by 1 (in either direction), we may have to
	 * add or subtract m afterwards.
	 *
	 * The 'tb' flag will be true (1) at the end of the loop if the
	 * result is greater than or equal to the modulus (not counting
	 * 'hi' or the carry).
	 */
	cc = 0;
	tb = 1;
	for (u = 1; u <= mlen; u ++) {
		uint32_t mw, zl, xw, nxw;

		mw = m[u];
		zl = MUL15(mw, q) + cc;
		cc = zl >> 15;
		zl &= 0x7FFF;
		xw = x[u];
		nxw = xw - zl;
		cc += nxw >> 31;
		nxw &= 0x7FFF;
		x[u] = nxw;
		tb = MUX(EQ(nxw, mw), tb, GT(nxw, mw));
	}

	/*
	 * If we underestimated q, then either cc < hi (one extra bit
	 * beyond the top array word), or cc == hi and tb is true (no
	 * extra bit, but the result is not lower than the modulus).
	 *
	 * If we overestimated q, then cc > hi.
	 */
	over = GT(cc, hi);
	under = ~over & (tb | LT(cc, hi));
	br_i15_add(x, m, over);
	br_i15_sub(x, m, under);
}