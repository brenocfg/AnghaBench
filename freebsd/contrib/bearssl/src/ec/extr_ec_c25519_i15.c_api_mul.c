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
typedef  unsigned char uint16_t ;

/* Variables and functions */
 unsigned char* C255_A24 ; 
 int* C255_P ; 
 unsigned char* C255_R2 ; 
 size_t ILEN ; 
 int /*<<< orphan*/  NOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P0I ; 
 int /*<<< orphan*/  br_i15_decode_mod (unsigned char*,unsigned char*,int,unsigned char*) ; 
 int /*<<< orphan*/  br_i15_encode (unsigned char*,int,unsigned char*) ; 
 int /*<<< orphan*/  br_i15_montymul (unsigned char*,unsigned char*,unsigned char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_i15_sub (unsigned char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_i15_zero (unsigned char*,int) ; 
 int /*<<< orphan*/  byteswap (unsigned char*) ; 
 int /*<<< orphan*/  c255_add (unsigned char*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  c255_mul (unsigned char*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  c255_sub (unsigned char*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  cswap (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t
api_mul(unsigned char *G, size_t Glen,
	const unsigned char *kb, size_t kblen, int curve)
{
#define ILEN   (18 * sizeof(uint16_t))

	/*
	 * The a[] and b[] arrays have an extra word to allow for
	 * decoding without using br_i15_decode_reduce().
	 */
	uint16_t x1[18], x2[18], x3[18], z2[18], z3[18];
	uint16_t a[19], aa[18], b[19], bb[18];
	uint16_t c[18], d[18], e[18], da[18], cb[18];
	unsigned char k[32];
	uint32_t swap;
	int i;

	(void)curve;

	/*
	 * Points are encoded over exactly 32 bytes. Multipliers must fit
	 * in 32 bytes as well.
	 * RFC 7748 mandates that the high bit of the last point byte must
	 * be ignored/cleared.
	 */
	if (Glen != 32 || kblen > 32) {
		return 0;
	}
	G[31] &= 0x7F;

	/*
	 * Byteswap the point encoding, because it uses little-endian, and
	 * the generic decoding routine uses big-endian.
	 */
	byteswap(G);

	/*
	 * Decode the point ('u' coordinate). This should be reduced
	 * modulo p, but we prefer to avoid the dependency on
	 * br_i15_decode_reduce(). Instead, we use br_i15_decode_mod()
	 * with a synthetic modulus of value 2^255 (this must work
	 * since G was truncated to 255 bits), then use a conditional
	 * subtraction. We use br_i15_decode_mod() and not
	 * br_i15_decode(), because the ec_prime_i15 implementation uses
	 * the former but not the latter.
	 *    br_i15_decode_reduce(a, G, 32, C255_P);
	 */
	br_i15_zero(b, 0x111);
	b[18] = 1;
	br_i15_decode_mod(a, G, 32, b);
	a[0] = 0x110;
	br_i15_sub(a, C255_P, NOT(br_i15_sub(a, C255_P, 0)));

	/*
	 * Initialise variables x1, x2, z2, x3 and z3. We set all of them
	 * into Montgomery representation.
	 */
	br_i15_montymul(x1, a, C255_R2, C255_P, P0I);
	memcpy(x3, x1, ILEN);
	br_i15_zero(z2, C255_P[0]);
	memcpy(x2, z2, ILEN);
	x2[1] = 19;
	memcpy(z3, x2, ILEN);

	memset(k, 0, (sizeof k) - kblen);
	memcpy(k + (sizeof k) - kblen, kb, kblen);
	k[31] &= 0xF8;
	k[0] &= 0x7F;
	k[0] |= 0x40;

	/* obsolete
	print_int_mont("x1", x1);
	*/

	swap = 0;
	for (i = 254; i >= 0; i --) {
		uint32_t kt;

		kt = (k[31 - (i >> 3)] >> (i & 7)) & 1;
		swap ^= kt;
		cswap(x2, x3, swap);
		cswap(z2, z3, swap);
		swap = kt;

		/* obsolete
		print_int_mont("x2", x2);
		print_int_mont("z2", z2);
		print_int_mont("x3", x3);
		print_int_mont("z3", z3);
		*/

		c255_add(a, x2, z2);
		c255_mul(aa, a, a);
		c255_sub(b, x2, z2);
		c255_mul(bb, b, b);
		c255_sub(e, aa, bb);
		c255_add(c, x3, z3);
		c255_sub(d, x3, z3);
		c255_mul(da, d, a);
		c255_mul(cb, c, b);

		/* obsolete
		print_int_mont("a ", a);
		print_int_mont("aa", aa);
		print_int_mont("b ", b);
		print_int_mont("bb", bb);
		print_int_mont("e ", e);
		print_int_mont("c ", c);
		print_int_mont("d ", d);
		print_int_mont("da", da);
		print_int_mont("cb", cb);
		*/

		c255_add(x3, da, cb);
		c255_mul(x3, x3, x3);
		c255_sub(z3, da, cb);
		c255_mul(z3, z3, z3);
		c255_mul(z3, z3, x1);
		c255_mul(x2, aa, bb);
		c255_mul(z2, C255_A24, e);
		c255_add(z2, z2, aa);
		c255_mul(z2, e, z2);

		/* obsolete
		print_int_mont("x2", x2);
		print_int_mont("z2", z2);
		print_int_mont("x3", x3);
		print_int_mont("z3", z3);
		*/
	}
	cswap(x2, x3, swap);
	cswap(z2, z3, swap);

	/*
	 * Inverse z2 with a modular exponentiation. This is a simple
	 * square-and-multiply algorithm; we mutualise most non-squarings
	 * since the exponent contains almost only ones.
	 */
	memcpy(a, z2, ILEN);
	for (i = 0; i < 15; i ++) {
		c255_mul(a, a, a);
		c255_mul(a, a, z2);
	}
	memcpy(b, a, ILEN);
	for (i = 0; i < 14; i ++) {
		int j;

		for (j = 0; j < 16; j ++) {
			c255_mul(b, b, b);
		}
		c255_mul(b, b, a);
	}
	for (i = 14; i >= 0; i --) {
		c255_mul(b, b, b);
		if ((0xFFEB >> i) & 1) {
			c255_mul(b, z2, b);
		}
	}
	c255_mul(b, x2, b);

	/*
	 * To avoid a dependency on br_i15_from_monty(), we use a
	 * Montgomery multiplication with 1.
	 *    memcpy(x2, b, ILEN);
	 *    br_i15_from_monty(x2, C255_P, P0I);
	 */
	br_i15_zero(a, C255_P[0]);
	a[1] = 1;
	br_i15_montymul(x2, a, b, C255_P, P0I);

	br_i15_encode(G, 32, x2);
	byteswap(G);
	return 1;

#undef ILEN
}