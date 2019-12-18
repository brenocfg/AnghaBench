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
 int M (int,int) ; 
 int br_dec32le (unsigned char const*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
poly1305_inner(uint32_t *acc, const uint32_t *r, const void *data, size_t len)
{
	/*
	 * Implementation notes: we split the 130-bit values into five
	 * 26-bit words. This gives us some space for carries.
	 *
	 * This code is inspired from the public-domain code available
	 * on:
	 *      https://github.com/floodyberry/poly1305-donna
	 *
	 * Since we compute modulo 2^130-5, the "upper words" become
	 * low words with a factor of 5; that is, x*2^130 = x*5 mod p.
	 */
	const unsigned char *buf;
	uint32_t a0, a1, a2, a3, a4;
	uint32_t r0, r1, r2, r3, r4;
	uint32_t u1, u2, u3, u4;

	r0 = r[0];
	r1 = r[1];
	r2 = r[2];
	r3 = r[3];
	r4 = r[4];

	u1 = r1 * 5;
	u2 = r2 * 5;
	u3 = r3 * 5;
	u4 = r4 * 5;

	a0 = acc[0];
	a1 = acc[1];
	a2 = acc[2];
	a3 = acc[3];
	a4 = acc[4];

	buf = data;
	while (len > 0) {
		uint64_t w0, w1, w2, w3, w4;
		uint64_t c;
		unsigned char tmp[16];

		/*
		 * If there is a partial block, right-pad it with zeros.
		 */
		if (len < 16) {
			memset(tmp, 0, sizeof tmp);
			memcpy(tmp, buf, len);
			buf = tmp;
			len = 16;
		}

		/*
		 * Decode next block and apply the "high bit"; that value
		 * is added to the accumulator.
		 */
		a0 += br_dec32le(buf) & 0x03FFFFFF;
		a1 += (br_dec32le(buf +  3) >> 2) & 0x03FFFFFF;
		a2 += (br_dec32le(buf +  6) >> 4) & 0x03FFFFFF;
		a3 += (br_dec32le(buf +  9) >> 6) & 0x03FFFFFF;
		a4 += (br_dec32le(buf + 12) >> 8) | 0x01000000;

		/*
		 * Compute multiplication.
		 */
#define M(x, y)   ((uint64_t)(x) * (uint64_t)(y))

		w0 = M(a0, r0) + M(a1, u4) + M(a2, u3) + M(a3, u2) + M(a4, u1);
		w1 = M(a0, r1) + M(a1, r0) + M(a2, u4) + M(a3, u3) + M(a4, u2);
		w2 = M(a0, r2) + M(a1, r1) + M(a2, r0) + M(a3, u4) + M(a4, u3);
		w3 = M(a0, r3) + M(a1, r2) + M(a2, r1) + M(a3, r0) + M(a4, u4);
		w4 = M(a0, r4) + M(a1, r3) + M(a2, r2) + M(a3, r1) + M(a4, r0);

#undef M
		/*
		 * Perform some (partial) modular reduction. This step is
		 * enough to keep values in ranges such that there won't
		 * be carry overflows. Most of the reduction was done in
		 * the multiplication step (by using the 'u*' values, and
		 * using the fact that 2^130 = -5 mod p); here we perform
		 * some carry propagation.
		 */
		c = w0 >> 26;
		a0 = (uint32_t)w0 & 0x3FFFFFF;
		w1 += c;
		c = w1 >> 26;
		a1 = (uint32_t)w1 & 0x3FFFFFF;
		w2 += c;
		c = w2 >> 26;
		a2 = (uint32_t)w2 & 0x3FFFFFF;
		w3 += c;
		c = w3 >> 26;
		a3 = (uint32_t)w3 & 0x3FFFFFF;
		w4 += c;
		c = w4 >> 26;
		a4 = (uint32_t)w4 & 0x3FFFFFF;
		a0 += (uint32_t)c * 5;
		a1 += a0 >> 26;
		a0 &= 0x3FFFFFF;

		buf += 16;
		len -= 16;
	}

	acc[0] = a0;
	acc[1] = a1;
	acc[2] = a2;
	acc[3] = a3;
	acc[4] = a4;
}