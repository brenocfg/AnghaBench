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
 int /*<<< orphan*/  br_i15_decode (int*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  br_i15_muladd_small (int*,int,int const*) ; 
 int /*<<< orphan*/  br_i15_rshift (int*,int) ; 
 int /*<<< orphan*/  br_i15_zero (int*,int) ; 

void
br_i15_decode_reduce(uint16_t *x,
	const void *src, size_t len, const uint16_t *m)
{
	uint32_t m_ebitlen, m_rbitlen;
	size_t mblen, k;
	const unsigned char *buf;
	uint32_t acc;
	int acc_len;

	/*
	 * Get the encoded bit length.
	 */
	m_ebitlen = m[0];

	/*
	 * Special case for an invalid (null) modulus.
	 */
	if (m_ebitlen == 0) {
		x[0] = 0;
		return;
	}

	/*
	 * Clear the destination.
	 */
	br_i15_zero(x, m_ebitlen);

	/*
	 * First decode directly as many bytes as possible. This requires
	 * computing the actual bit length.
	 */
	m_rbitlen = m_ebitlen >> 4;
	m_rbitlen = (m_ebitlen & 15) + (m_rbitlen << 4) - m_rbitlen;
	mblen = (m_rbitlen + 7) >> 3;
	k = mblen - 1;
	if (k >= len) {
		br_i15_decode(x, src, len);
		x[0] = m_ebitlen;
		return;
	}
	buf = src;
	br_i15_decode(x, buf, k);
	x[0] = m_ebitlen;

	/*
	 * Input remaining bytes, using 15-bit words.
	 */
	acc = 0;
	acc_len = 0;
	while (k < len) {
		uint32_t v;

		v = buf[k ++];
		acc = (acc << 8) | v;
		acc_len += 8;
		if (acc_len >= 15) {
			br_i15_muladd_small(x, acc >> (acc_len - 15), m);
			acc_len -= 15;
			acc &= ~((uint32_t)-1 << acc_len);
		}
	}

	/*
	 * We may have some bits accumulated. We then perform a shift to
	 * be able to inject these bits as a full 15-bit word.
	 */
	if (acc_len != 0) {
		acc = (acc | (x[1] << acc_len)) & 0x7FFF;
		br_i15_rshift(x, 15 - acc_len);
		br_i15_muladd_small(x, acc, m);
	}
}