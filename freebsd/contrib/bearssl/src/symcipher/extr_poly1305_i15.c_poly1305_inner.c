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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  NOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P0I ; 
 int /*<<< orphan*/  P1305 ; 
 int /*<<< orphan*/  br_i15_add (int*,int*,int) ; 
 int /*<<< orphan*/  br_i15_decode_mod (int*,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_i15_montymul (int*,int*,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_i15_sub (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
poly1305_inner(uint16_t *a, const uint16_t *r, const void *data, size_t len)
{
	const unsigned char *buf;

	buf = data;
	while (len > 0) {
		unsigned char tmp[16], rev[16];
		uint16_t b[10];
		uint32_t ctl;
		int i;

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
		 * Decode next block and apply the "high bit". Since
		 * decoding is little-endian, we must byte-swap the buffer.
		 */
		for (i = 0; i < 16; i ++) {
			rev[i] = buf[15 - i];
		}
		br_i15_decode_mod(b, rev, sizeof rev, P1305);
		b[9] |= 0x0100;

		/*
		 * Add the accumulator to the decoded block (modular
		 * addition).
		 */
		ctl = br_i15_add(b, a, 1);
		ctl |= NOT(br_i15_sub(b, P1305, 0));
		br_i15_sub(b, P1305, ctl);

		/*
		 * Multiply by r, result is the new accumulator value.
		 */
		br_i15_montymul(a, b, r, P1305, P0I);

		buf += 16;
		len -= 16;
	}
}