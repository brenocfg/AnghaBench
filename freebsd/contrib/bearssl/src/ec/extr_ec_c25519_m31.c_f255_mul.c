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
 int MUL15 (int,int) ; 
 int MUL31 (int,int) ; 
 int /*<<< orphan*/  mul9 (int*,int const*,int const*) ; 

__attribute__((used)) static void
f255_mul(uint32_t *d, const uint32_t *a, const uint32_t *b)
{
	uint32_t t[18], cc;
	int i;

	/*
	 * Compute raw multiplication. All result words fit in 30 bits
	 * each; upper word (t[17]) must fit on 2 bits, since the product
	 * of two 256-bit integers must fit on 512 bits.
	 */
	mul9(t, a, b);

	/*
	 * Modular reduction: each high word is added where necessary.
	 * Since the modulus is 2^255-19 and word 9 corresponds to
	 * offset 9*30 = 270, word 9+k must be added to word k with
	 * a factor of 19*2^15 = 622592. The extra bits in word 8 are also
	 * added that way.
	 *
	 * Keeping the carry on 32 bits helps with 32-bit architectures,
	 * and does not noticeably impact performance on 64-bit systems.
	 */
	cc = MUL15(t[8] >> 15, 19);  /* at most 19*(2^15-1) = 622573 */
	t[8] &= 0x7FFF;
	for (i = 0; i < 9; i ++) {
		uint64_t w;

		w = (uint64_t)t[i] + (uint64_t)cc + MUL31(t[i + 9], 622592);
		t[i] = (uint32_t)w & 0x3FFFFFFF;
		cc = (uint32_t)(w >> 30);  /* at most 622592 */
	}

	/*
	 * Original product was up to (2^256-1)^2, i.e. a 512-bit integer.
	 * This was split into two parts (upper of 257 bits, lower of 255
	 * bits), and the upper was added to the lower with a factor 19,
	 * which means that the intermediate value is less than 77*2^255
	 * (19*2^257 + 2^255). Therefore, the extra bits "t[8] >> 15" are
	 * less than 77, and the initial carry cc is at most 76*19 = 1444.
	 */
	cc = MUL15(t[8] >> 15, 19);
	t[8] &= 0x7FFF;
	for (i = 0; i < 9; i ++) {
		uint32_t z;

		z = t[i] + cc;
		d[i] = z & 0x3FFFFFFF;
		cc = z >> 30;
	}

	/*
	 * Final result is at most 2^255 + 1443. In particular, the last
	 * carry is necessarily 0, since t[8] was truncated to 15 bits.
	 */
}