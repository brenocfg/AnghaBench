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

/* Variables and functions */
 int ARSH (int,int) ; 
 int ARSHW (int,int) ; 
 int /*<<< orphan*/  square9 (int*,int const*) ; 

__attribute__((used)) static void
square_f256(uint32_t *d, const uint32_t *a)
{
	uint32_t t[18];
	uint64_t s[18];
	uint64_t cc, x;
	uint32_t z, c;
	int i;

	square9(t, a);

	/*
	 * Modular reduction: each high word in added/subtracted where
	 * necessary.
	 *
	 * The modulus is:
	 *    p = 2^256 - 2^224 + 2^192 + 2^96 - 1
	 * Therefore:
	 *    2^256 = 2^224 - 2^192 - 2^96 + 1 mod p
	 *
	 * For a word x at bit offset n (n >= 256), we have:
	 *    x*2^n = x*2^(n-32) - x*2^(n-64)
	 *            - x*2^(n - 160) + x*2^(n-256) mod p
	 *
	 * Thus, we can nullify the high word if we reinject it at some
	 * proper emplacements.
	 *
	 * We use 64-bit intermediate words to allow for carries to
	 * accumulate easily, before performing the final propagation.
	 */
	for (i = 0; i < 18; i ++) {
		s[i] = t[i];
	}

	for (i = 17; i >= 9; i --) {
		uint64_t y;

		y = s[i];
		s[i - 1] += ARSHW(y, 2);
		s[i - 2] += (y << 28) & 0x3FFFFFFF;
		s[i - 2] -= ARSHW(y, 4);
		s[i - 3] -= (y << 26) & 0x3FFFFFFF;
		s[i - 5] -= ARSHW(y, 10);
		s[i - 6] -= (y << 20) & 0x3FFFFFFF;
		s[i - 8] += ARSHW(y, 16);
		s[i - 9] += (y << 14) & 0x3FFFFFFF;
	}

	/*
	 * Carry propagation must be signed. Moreover, we may have overdone
	 * it a bit, and obtain a negative result.
	 *
	 * The loop above ran 9 times; each time, each word was augmented
	 * by at most one extra word (in absolute value). Thus, the top
	 * word must in fine fit in 39 bits, so the carry below will fit
	 * on 9 bits.
	 */
	cc = 0;
	for (i = 0; i < 9; i ++) {
		x = s[i] + cc;
		d[i] = (uint32_t)x & 0x3FFFFFFF;
		cc = ARSHW(x, 30);
	}

	/*
	 * All nine words fit on 30 bits, but there may be an extra
	 * carry for a few bits (at most 9), and that carry may be
	 * negative. Moreover, we want the result to fit on 257 bits.
	 * The two lines below ensure that the word in d[] has length
	 * 256 bits, and the (signed) carry (beyond 2^256) is in cc. The
	 * significant length of cc is less than 24 bits, so we will be
	 * able to switch to 32-bit operations.
	 */
	cc = ARSHW(x, 16);
	d[8] &= 0xFFFF;

	/*
	 * One extra round of reduction, for cc*2^256, which means
	 * adding cc*(2^224-2^192-2^96+1) to a 256-bit (nonnegative)
	 * value. If cc is negative, then it may happen (rarely, but
	 * not neglectibly so) that the result would be negative. In
	 * order to avoid that, if cc is negative, then we add the
	 * modulus once. Note that if cc is negative, then propagating
	 * that carry must yield a value lower than the modulus, so
	 * adding the modulus once will keep the final result under
	 * twice the modulus.
	 */
	z = (uint32_t)cc;
	d[3] -= z << 6;
	d[6] -= (z << 12) & 0x3FFFFFFF;
	d[7] -= ARSH(z, 18);
	d[7] += (z << 14) & 0x3FFFFFFF;
	d[8] += ARSH(z, 16);
	c = z >> 31;
	d[0] -= c;
	d[3] += c << 6;
	d[6] += c << 12;
	d[7] -= c << 14;
	d[8] += c << 16;
	for (i = 0; i < 9; i ++) {
		uint32_t w;

		w = d[i] + z;
		d[i] = w & 0x3FFFFFFF;
		z = ARSH(w, 30);
	}
}