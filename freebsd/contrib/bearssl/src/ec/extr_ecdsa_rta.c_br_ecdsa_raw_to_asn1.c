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
 size_t asn1_int_length (unsigned char*,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,unsigned char*,size_t) ; 

size_t
br_ecdsa_raw_to_asn1(void *sig, size_t sig_len)
{
	/*
	 * Internal buffer is large enough to accommodate a signature
	 * such that r and s fit on 125 bytes each (signed encoding),
	 * meaning a curve order of up to 999 bits. This is the limit
	 * that ensures "simple" length encodings.
	 */
	unsigned char *buf;
	size_t hlen, rlen, slen, zlen, off;
	unsigned char tmp[257];

	buf = sig;
	if ((sig_len & 1) != 0) {
		return 0;
	}

	/*
	 * Compute lengths for the two integers.
	 */
	hlen = sig_len >> 1;
	rlen = asn1_int_length(buf, hlen);
	slen = asn1_int_length(buf + hlen, hlen);
	if (rlen > 125 || slen > 125) {
		return 0;
	}

	/*
	 * SEQUENCE header.
	 */
	tmp[0] = 0x30;
	zlen = rlen + slen + 4;
	if (zlen >= 0x80) {
		tmp[1] = 0x81;
		tmp[2] = zlen;
		off = 3;
	} else {
		tmp[1] = zlen;
		off = 2;
	}

	/*
	 * First INTEGER (r).
	 */
	tmp[off ++] = 0x02;
	tmp[off ++] = rlen;
	if (rlen > hlen) {
		tmp[off] = 0x00;
		memcpy(tmp + off + 1, buf, hlen);
	} else {
		memcpy(tmp + off, buf + hlen - rlen, rlen);
	}
	off += rlen;

	/*
	 * Second INTEGER (s).
	 */
	tmp[off ++] = 0x02;
	tmp[off ++] = slen;
	if (slen > hlen) {
		tmp[off] = 0x00;
		memcpy(tmp + off + 1, buf + hlen, hlen);
	} else {
		memcpy(tmp + off, buf + sig_len - slen, slen);
	}
	off += slen;

	/*
	 * Return ASN.1 signature.
	 */
	memcpy(sig, tmp, off);
	return off;
}