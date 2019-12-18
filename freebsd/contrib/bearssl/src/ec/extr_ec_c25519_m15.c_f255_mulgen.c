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
 int /*<<< orphan*/  MM1 (int) ; 
 int /*<<< orphan*/  MM2 (int) ; 
 int MUL15 (int,int) ; 
 int /*<<< orphan*/  mul20 (int*,int const*,int const*) ; 
 int /*<<< orphan*/  square20 (int*,int const*) ; 

__attribute__((used)) static void
f255_mulgen(uint32_t *d, const uint32_t *a, const uint32_t *b, int square)
{
	uint32_t t[40], cc, w;

	/*
	 * Compute raw multiplication. All result words fit in 13 bits
	 * each; upper word (t[39]) must fit on 5 bits, since the product
	 * of two 256-bit integers must fit on 512 bits.
	 */
	if (square) {
		square20(t, a);
	} else {
		mul20(t, a, b);
	}

	/*
	 * Modular reduction: each high word is added where necessary.
	 * Since the modulus is 2^255-19 and word 20 corresponds to
	 * offset 20*13 = 260, word 20+k must be added to word k with
	 * a factor of 19*2^5 = 608. The extra bits in word 19 are also
	 * added that way.
	 */
	cc = MUL15(t[19] >> 8, 19);
	t[19] &= 0xFF;

#define MM1(x)   do { \
		w = t[x] + cc + MUL15(t[(x) + 20], 608); \
		t[x] = w & 0x1FFF; \
		cc = w >> 13; \
	} while (0)

	MM1( 0);
	MM1( 1);
	MM1( 2);
	MM1( 3);
	MM1( 4);
	MM1( 5);
	MM1( 6);
	MM1( 7);
	MM1( 8);
	MM1( 9);
	MM1(10);
	MM1(11);
	MM1(12);
	MM1(13);
	MM1(14);
	MM1(15);
	MM1(16);
	MM1(17);
	MM1(18);
	MM1(19);

#undef MM1

	cc = MUL15(w >> 8, 19);
	t[19] &= 0xFF;

#define MM2(x)   do { \
		w = t[x] + cc; \
		d[x] = w & 0x1FFF; \
		cc = w >> 13; \
	} while (0)

	MM2( 0);
	MM2( 1);
	MM2( 2);
	MM2( 3);
	MM2( 4);
	MM2( 5);
	MM2( 6);
	MM2( 7);
	MM2( 8);
	MM2( 9);
	MM2(10);
	MM2(11);
	MM2(12);
	MM2(13);
	MM2(14);
	MM2(15);
	MM2(16);
	MM2(17);
	MM2(18);
	MM2(19);

#undef MM2
}