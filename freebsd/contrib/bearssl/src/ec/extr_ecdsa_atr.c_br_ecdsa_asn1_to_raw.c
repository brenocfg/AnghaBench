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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 

size_t
br_ecdsa_asn1_to_raw(void *sig, size_t sig_len)
{
	/*
	 * Note: this code is a bit lenient in that it accepts a few
	 * deviations to DER with regards to minimality of encoding of
	 * lengths and integer values. These deviations are still
	 * unambiguous.
	 *
	 * Signature format is a SEQUENCE of two INTEGER values. We
	 * support only integers of less than 127 bytes each (signed
	 * encoding) so the resulting raw signature will have length
	 * at most 254 bytes.
	 */

	unsigned char *buf, *r, *s;
	size_t zlen, rlen, slen, off;
	unsigned char tmp[254];

	buf = sig;
	if (sig_len < 8) {
		return 0;
	}

	/*
	 * First byte is SEQUENCE tag.
	 */
	if (buf[0] != 0x30) {
		return 0;
	}

	/*
	 * The SEQUENCE length will be encoded over one or two bytes. We
	 * limit the total SEQUENCE contents to 255 bytes, because it
	 * makes things simpler; this is enough for subgroup orders up
	 * to 999 bits.
	 */
	zlen = buf[1];
	if (zlen > 0x80) {
		if (zlen != 0x81) {
			return 0;
		}
		zlen = buf[2];
		if (zlen != sig_len - 3) {
			return 0;
		}
		off = 3;
	} else {
		if (zlen != sig_len - 2) {
			return 0;
		}
		off = 2;
	}

	/*
	 * First INTEGER (r).
	 */
	if (buf[off ++] != 0x02) {
		return 0;
	}
	rlen = buf[off ++];
	if (rlen >= 0x80) {
		return 0;
	}
	r = buf + off;
	off += rlen;

	/*
	 * Second INTEGER (s).
	 */
	if (off + 2 > sig_len) {
		return 0;
	}
	if (buf[off ++] != 0x02) {
		return 0;
	}
	slen = buf[off ++];
	if (slen >= 0x80 || slen != sig_len - off) {
		return 0;
	}
	s = buf + off;

	/*
	 * Removing leading zeros from r and s.
	 */
	while (rlen > 0 && *r == 0) {
		rlen --;
		r ++;
	}
	while (slen > 0 && *s == 0) {
		slen --;
		s ++;
	}

	/*
	 * Compute common length for the two integers, then copy integers
	 * into the temporary buffer, and finally copy it back over the
	 * signature buffer.
	 */
	zlen = rlen > slen ? rlen : slen;
	sig_len = zlen << 1;
	memset(tmp, 0, sig_len);
	memcpy(tmp + zlen - rlen, r, rlen);
	memcpy(tmp + sig_len - slen, s, slen);
	memcpy(sig, tmp, sig_len);
	return sig_len;
}