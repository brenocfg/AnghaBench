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
 scalar_t__ ARSH (int,int) ; 
 int norm13 (int*,int*,int) ; 
 int /*<<< orphan*/  square20 (int*,int const*) ; 

__attribute__((used)) static void
square_f256(uint32_t *d, const uint32_t *a)
{
	uint32_t t[40], cc;
	int i;

	/*
	 * Compute raw square. All result words fit in 13 bits each.
	 */
	square20(t, a);

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
	 */
	for (i = 39; i >= 20; i --) {
		uint32_t x;

		x = t[i];
		t[i - 2] += ARSH(x, 6);
		t[i - 3] += (x << 7) & 0x1FFF;
		t[i - 4] -= ARSH(x, 12);
		t[i - 5] -= (x << 1) & 0x1FFF;
		t[i - 12] -= ARSH(x, 4);
		t[i - 13] -= (x << 9) & 0x1FFF;
		t[i - 19] += ARSH(x, 9);
		t[i - 20] += (x << 4) & 0x1FFF;
	}

	/*
	 * Propagate carries. This is a signed propagation, and the
	 * result may be negative. The loop above may enlarge values,
	 * but not two much: worst case is the chain involving t[i - 3],
	 * in which a value may be added to itself up to 7 times. Since
	 * starting values are 13-bit each, all words fit on 20 bits
	 * (21 to account for the sign bit).
	 */
	cc = norm13(t, t, 20);

	/*
	 * Perform modular reduction again for the bits beyond 256 (the carry
	 * and the bits 256..259). Since the largest shift below is by 10
	 * bits, and the values fit on 21 bits, values fit in 32-bit words,
	 * thereby allowing injecting full word values.
	 */
	cc = (cc << 4) | (t[19] >> 9);
	t[19] &= 0x01FF;
	t[17] += cc << 3;
	t[14] -= cc << 10;
	t[7] -= cc << 5;
	t[0] += cc;

	/*
	 * If the carry is negative, then after carry propagation, we may
	 * end up with a value which is negative, and we don't want that.
	 * Thus, in that case, we add the modulus. Note that the subtraction
	 * result, when the carry is negative, is always smaller than the
	 * modulus, so the extra addition will not make the value exceed
	 * twice the modulus.
	 */
	cc >>= 31;
	t[0] -= cc;
	t[7] += cc << 5;
	t[14] += cc << 10;
	t[17] -= cc << 3;
	t[19] += cc << 9;

	norm13(d, t, 20);
}