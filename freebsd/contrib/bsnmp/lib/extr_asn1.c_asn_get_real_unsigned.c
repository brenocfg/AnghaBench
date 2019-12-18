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
struct asn_buf {int asn_len; int* asn_cptr; } ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;
typedef  int asn_len_t ;

/* Variables and functions */
 int ASN_ERR_BADLEN ; 
 int ASN_ERR_EOBUF ; 
 int ASN_ERR_OK ; 
 int ASN_ERR_RANGE ; 
 int /*<<< orphan*/  asn_error (struct asn_buf*,char*) ; 

__attribute__((used)) static enum asn_err
asn_get_real_unsigned(struct asn_buf *b, asn_len_t len, uint64_t *vp)
{
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
	*vp = 0;
	if ((*b->asn_cptr & 0x80) || (len == 9 && *b->asn_cptr != 0)) {
		/* negative integer or too larger */
		*vp = 0xffffffffffffffffULL;
		err = ASN_ERR_RANGE;
	} else if (len > 1 &&
	    *b->asn_cptr == 0x00 && (b->asn_cptr[1] & 0x80) == 0) {
		asn_error(b, "non-minimal unsigned");
		err = ASN_ERR_BADLEN;
	}

	while (len--) {
		*vp = (*vp << 8) | *b->asn_cptr++;
		b->asn_len--;
	}
	return (err);
}