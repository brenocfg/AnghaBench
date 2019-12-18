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
 scalar_t__ CMP (int,int) ; 
 int /*<<< orphan*/  EQ (int,int /*<<< orphan*/ ) ; 
 int MUX (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  br_i32_zero (int*,int const) ; 

uint32_t
br_i32_decode_mod(uint32_t *x, const void *src, size_t len, const uint32_t *m)
{
	const unsigned char *buf;
	uint32_t r;
	size_t u, v, mlen;

	buf = src;

	/*
	 * First pass: determine whether the value fits. The 'r' value
	 * will contain the comparison result, as 0x00000000 (value is
	 * equal to the modulus), 0x00000001 (value is greater than the
	 * modulus), or 0xFFFFFFFF (value is lower than the modulus).
	 */
	mlen = (m[0] + 7) >> 3;
	r = 0;
	for (u = (mlen > len) ? mlen : len; u > 0; u --) {
		uint32_t mb, xb;

		v = u - 1;
		if (v >= mlen) {
			mb = 0;
		} else {
			mb = (m[1 + (v >> 2)] >> ((v & 3) << 3)) & 0xFF;
		}
		if (v >= len) {
			xb = 0;
		} else {
			xb = buf[len - u];
		}
		r = MUX(EQ(r, 0), (uint32_t)CMP(xb, mb), r);
	}

	/*
	 * Only r == 0xFFFFFFFF is acceptable. We want to set r to 0xFF if
	 * the value fits, 0x00 otherwise.
	 */
	r >>= 24;
	br_i32_zero(x, m[0]);
	u = (mlen > len) ? len : mlen;
	while (u > 0) {
		uint32_t xb;

		xb = buf[len - u] & r;
		u --;
		x[1 + (u >> 2)] |= xb << ((u & 3) << 3);
	}
	return r >> 7;
}