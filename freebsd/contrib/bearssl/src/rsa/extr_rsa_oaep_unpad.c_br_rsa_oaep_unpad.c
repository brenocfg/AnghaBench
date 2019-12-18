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
typedef  int /*<<< orphan*/  br_hash_class ;

/* Variables and functions */
 int EQ (int,int) ; 
 int GE (int,int) ; 
 int NOT (int) ; 
 size_t br_digest_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  br_mgf1_xor (unsigned char*,size_t,int /*<<< orphan*/  const*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memmove (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  xor_hash_data (int /*<<< orphan*/  const*,unsigned char*,void const*,size_t) ; 

uint32_t
br_rsa_oaep_unpad(const br_hash_class *dig,
	const void *label, size_t label_len,
	void *data, size_t *len)
{
	size_t u, k, hlen;
	unsigned char *buf;
	uint32_t r, s, zlen;

	hlen = br_digest_size(dig);
	k = *len;
	buf = data;

	/*
	 * There must be room for the padding.
	 */
	if (k < ((hlen << 1) + 2)) {
		return 0;
	}

	/*
	 * Unmask the seed, then the DB value.
	 */
	br_mgf1_xor(buf + 1, hlen, dig, buf + 1 + hlen, k - hlen - 1);
	br_mgf1_xor(buf + 1 + hlen, k - hlen - 1, dig, buf + 1, hlen);

	/*
	 * Hash the label and XOR it with the value in the array; if
	 * they are equal then these should yield only zeros.
	 */
	xor_hash_data(dig, buf + 1 + hlen, label, label_len);

	/*
	 * At that point, if the padding was correct, when we should
	 * have: 0x00 || seed || 0x00 ... 0x00 0x01 || M
	 * Padding is valid as long as:
	 *  - There is at least hlen+1 leading bytes of value 0x00.
	 *  - There is at least one non-zero byte.
	 *  - The first (leftmost) non-zero byte has value 0x01.
	 *
	 * Ultimately, we may leak the resulting message length, i.e.
	 * the position of the byte of value 0x01, but we must take care
	 * to do so only if the number of zero bytes has been verified
	 * to be at least hlen+1.
	 *
	 * The loop below counts the number of bytes of value 0x00, and
	 * checks that the next byte has value 0x01, in constant-time.
	 *
	 *  - If the initial byte (before the seed) is not 0x00, then
	 *    r and s are set to 0, and stay there.
	 *  - Value r is 1 until the first non-zero byte is reached
	 *    (after the seed); it switches to 0 at that point.
	 *  - Value s is set to 1 if and only if the data encountered
	 *    at the time of the transition of r from 1 to 0 has value
	 *    exactly 0x01.
	 *  - Value zlen counts the number of leading bytes of value zero
	 *    (after the seed).
	 */
	r = 1 - ((buf[0] + 0xFF) >> 8);
	s = 0;
	zlen = 0;
	for (u = hlen + 1; u < k; u ++) {
		uint32_t w, nz;

		w = buf[u];

		/*
		 * nz == 1 only for the first non-zero byte.
		 */
		nz = r & ((w + 0xFF) >> 8);
		s |= nz & EQ(w, 0x01);
		r &= NOT(nz);
		zlen += r;
	}

	/*
	 * Padding is correct only if s == 1, _and_ zlen >= hlen.
	 */
	s &= GE(zlen, (uint32_t)hlen);

	/*
	 * At that point, padding was verified, and we are now allowed
	 * to make conditional jumps.
	 */
	if (s) {
		size_t plen;

		plen = 2 + hlen + zlen;
		k -= plen;
		memmove(buf, buf + plen, k);
		*len = k;
	}
	return s;
}