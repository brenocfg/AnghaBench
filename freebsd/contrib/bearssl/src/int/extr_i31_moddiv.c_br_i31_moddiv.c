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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int int64_t ;

/* Variables and functions */
 int EQ0 (int) ; 
 int NOT (int) ; 
 int co_reduce (int*,int*,size_t,int,int,int,int) ; 
 int /*<<< orphan*/  co_reduce_mod (int*,int*,size_t,int,int,int,int,int const*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,size_t) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t) ; 

uint32_t
br_i31_moddiv(uint32_t *x, const uint32_t *y, const uint32_t *m, uint32_t m0i,
	uint32_t *t)
{
	/*
	 * Algorithm is an extended binary GCD. We maintain four values
	 * a, b, u and v, with the following invariants:
	 *
	 *   a * x = y * u mod m
	 *   b * x = y * v mod m
	 *
	 * Starting values are:
	 *
	 *   a = y
	 *   b = m
	 *   u = x
	 *   v = 0
	 *
	 * The formal definition of the algorithm is a sequence of steps:
	 *
	 *   - If a is even, then a <- a/2 and u <- u/2 mod m.
	 *   - Otherwise, if b is even, then b <- b/2 and v <- v/2 mod m.
	 *   - Otherwise, if a > b, then a <- (a-b)/2 and u <- (u-v)/2 mod m.
	 *   - Otherwise, b <- (b-a)/2 and v <- (v-u)/2 mod m.
	 *
	 * Algorithm stops when a = b. At that point, they both are equal
	 * to GCD(y,m); the modular division succeeds if that value is 1.
	 * The result of the modular division is then u (or v: both are
	 * equal at that point).
	 *
	 * Each step makes either a or b shrink by at least one bit; hence,
	 * if m has bit length k bits, then 2k-2 steps are sufficient.
	 *
	 *
	 * Though complexity is quadratic in the size of m, the bit-by-bit
	 * processing is not very efficient. We can speed up processing by
	 * remarking that the decisions are taken based only on observation
	 * of the top and low bits of a and b.
	 *
	 * In the loop below, at each iteration, we use the two top words
	 * of a and b, and the low words of a and b, to compute reduction
	 * parameters pa, pb, qa and qb such that the new values for a
	 * and b are:
	 *
	 *   a' = (a*pa + b*pb) / (2^31)
	 *   b' = (a*qa + b*qb) / (2^31)
	 *
	 * the division being exact.
	 *
	 * Since the choices are based on the top words, they may be slightly
	 * off, requiring an optional correction: if a' < 0, then we replace
	 * pa with -pa, and pb with -pb. The total length of a and b is
	 * thus reduced by at least 30 bits at each iteration.
	 *
	 * The stopping conditions are still the same, though: when a
	 * and b become equal, they must be both odd (since m is odd,
	 * the GCD cannot be even), therefore the next operation is a
	 * subtraction, and one of the values becomes 0. At that point,
	 * nothing else happens, i.e. one value is stuck at 0, and the
	 * other one is the GCD.
	 */
	size_t len, k;
	uint32_t *a, *b, *u, *v;
	uint32_t num, r;

	len = (m[0] + 31) >> 5;
	a = t;
	b = a + len;
	u = x + 1;
	v = b + len;
	memcpy(a, y + 1, len * sizeof *y);
	memcpy(b, m + 1, len * sizeof *m);
	memset(v, 0, len * sizeof *v);

	/*
	 * Loop below ensures that a and b are reduced by some bits each,
	 * for a total of at least 30 bits.
	 */
	for (num = ((m[0] - (m[0] >> 5)) << 1) + 30; num >= 30; num -= 30) {
		size_t j;
		uint32_t c0, c1;
		uint32_t a0, a1, b0, b1;
		uint64_t a_hi, b_hi;
		uint32_t a_lo, b_lo;
		int64_t pa, pb, qa, qb;
		int i;

		/*
		 * Extract top words of a and b. If j is the highest
		 * index >= 1 such that a[j] != 0 or b[j] != 0, then we want
		 * (a[j] << 31) + a[j - 1], and (b[j] << 31) + b[j - 1].
		 * If a and b are down to one word each, then we use a[0]
		 * and b[0].
		 */
		c0 = (uint32_t)-1;
		c1 = (uint32_t)-1;
		a0 = 0;
		a1 = 0;
		b0 = 0;
		b1 = 0;
		j = len;
		while (j -- > 0) {
			uint32_t aw, bw;

			aw = a[j];
			bw = b[j];
			a0 ^= (a0 ^ aw) & c0;
			a1 ^= (a1 ^ aw) & c1;
			b0 ^= (b0 ^ bw) & c0;
			b1 ^= (b1 ^ bw) & c1;
			c1 = c0;
			c0 &= (((aw | bw) + 0x7FFFFFFF) >> 31) - (uint32_t)1;
		}

		/*
		 * If c1 = 0, then we grabbed two words for a and b.
		 * If c1 != 0 but c0 = 0, then we grabbed one word. It
		 * is not possible that c1 != 0 and c0 != 0, because that
		 * would mean that both integers are zero.
		 */
		a1 |= a0 & c1;
		a0 &= ~c1;
		b1 |= b0 & c1;
		b0 &= ~c1;
		a_hi = ((uint64_t)a0 << 31) + a1;
		b_hi = ((uint64_t)b0 << 31) + b1;
		a_lo = a[0];
		b_lo = b[0];

		/*
		 * Compute reduction factors:
		 *
		 *   a' = a*pa + b*pb
		 *   b' = a*qa + b*qb
		 *
		 * such that a' and b' are both multiple of 2^31, but are
		 * only marginally larger than a and b.
		 */
		pa = 1;
		pb = 0;
		qa = 0;
		qb = 1;
		for (i = 0; i < 31; i ++) {
			/*
			 * At each iteration:
			 *
			 *   a <- (a-b)/2 if: a is odd, b is odd, a_hi > b_hi
			 *   b <- (b-a)/2 if: a is odd, b is odd, a_hi <= b_hi
			 *   a <- a/2 if: a is even
			 *   b <- b/2 if: a is odd, b is even
			 *
			 * We multiply a_lo and b_lo by 2 at each
			 * iteration, thus a division by 2 really is a
			 * non-multiplication by 2.
			 */
			uint32_t r, oa, ob, cAB, cBA, cA;
			uint64_t rz;

			/*
			 * r = GT(a_hi, b_hi)
			 * But the GT() function works on uint32_t operands,
			 * so we inline a 64-bit version here.
			 */
			rz = b_hi - a_hi;
			r = (uint32_t)((rz ^ ((a_hi ^ b_hi)
				& (a_hi ^ rz))) >> 63);

			/*
			 * cAB = 1 if b must be subtracted from a
			 * cBA = 1 if a must be subtracted from b
			 * cA = 1 if a is divided by 2, 0 otherwise
			 *
			 * Rules:
			 *
			 *   cAB and cBA cannot be both 1.
			 *   if a is not divided by 2, b is.
			 */
			oa = (a_lo >> i) & 1;
			ob = (b_lo >> i) & 1;
			cAB = oa & ob & r;
			cBA = oa & ob & NOT(r);
			cA = cAB | NOT(oa);

			/*
			 * Conditional subtractions.
			 */
			a_lo -= b_lo & -cAB;
			a_hi -= b_hi & -(uint64_t)cAB;
			pa -= qa & -(int64_t)cAB;
			pb -= qb & -(int64_t)cAB;
			b_lo -= a_lo & -cBA;
			b_hi -= a_hi & -(uint64_t)cBA;
			qa -= pa & -(int64_t)cBA;
			qb -= pb & -(int64_t)cBA;

			/*
			 * Shifting.
			 */
			a_lo += a_lo & (cA - 1);
			pa += pa & ((int64_t)cA - 1);
			pb += pb & ((int64_t)cA - 1);
			a_hi ^= (a_hi ^ (a_hi >> 1)) & -(uint64_t)cA;
			b_lo += b_lo & -cA;
			qa += qa & -(int64_t)cA;
			qb += qb & -(int64_t)cA;
			b_hi ^= (b_hi ^ (b_hi >> 1)) & ((uint64_t)cA - 1);
		}

		/*
		 * Replace a and b with new values a' and b'.
		 */
		r = co_reduce(a, b, len, pa, pb, qa, qb);
		pa -= pa * ((r & 1) << 1);
		pb -= pb * ((r & 1) << 1);
		qa -= qa * (r & 2);
		qb -= qb * (r & 2);
		co_reduce_mod(u, v, len, pa, pb, qa, qb, m + 1, m0i);
	}

	/*
	 * Now one of the arrays should be 0, and the other contains
	 * the GCD. If a is 0, then u is 0 as well, and v contains
	 * the division result.
	 * Result is correct if and only if GCD is 1.
	 */
	r = (a[0] | b[0]) ^ 1;
	u[0] |= v[0];
	for (k = 1; k < len; k ++) {
		r |= a[k] | b[k];
		u[k] |= v[k];
	}
	return EQ0(r);
}