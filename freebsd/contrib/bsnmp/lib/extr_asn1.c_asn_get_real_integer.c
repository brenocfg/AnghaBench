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
typedef  int u_char ;
struct asn_buf {int asn_len; int* asn_cptr; } ;
typedef  int int64_t ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;
typedef  int asn_len_t ;

/* Variables and functions */
 int ASN_ERR_BADLEN ; 
 int ASN_ERR_EOBUF ; 
 int ASN_ERR_OK ; 
 int ASN_ERR_RANGE ; 
 int /*<<< orphan*/  asn_error (struct asn_buf*,char*) ; 

__attribute__((used)) static enum asn_err
asn_get_real_integer(struct asn_buf *b, asn_len_t len, int64_t *vp)
{
	uint64_t val;
	int neg = 0;
	enum asn_err err;

	if (b->asn_len < len) {
		asn_error(b, "truncated integer");
		return (ASN_ERR_EOBUF);
	}
	if (len == 0) {
		asn_error(b, "zero-length integer");
		*vp = 0;
		return (ASN_ERR_BADLEN);
	}
	err = ASN_ERR_OK;
	if (len > 8)
		err = ASN_ERR_RANGE;
	else if (len > 1 &&
	    ((*b->asn_cptr == 0x00 && (b->asn_cptr[1] & 0x80) == 0) ||
	    (*b->asn_cptr == 0xff && (b->asn_cptr[1] & 0x80) == 0x80))) {
		asn_error(b, "non-minimal integer");
		err = ASN_ERR_BADLEN;
	}

	if (*b->asn_cptr & 0x80)
		neg = 1;
	val = 0;
	while (len--) {
		val <<= 8;
		val |= neg ? (u_char)~*b->asn_cptr : *b->asn_cptr;
		b->asn_len--;
		b->asn_cptr++;
	}
	if (neg) {
		*vp = -(int64_t)val - 1;
	} else
		*vp = (int64_t)val;
	return (err);
}