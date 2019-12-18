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
typedef  int u_int ;
typedef  int u_char ;
struct asn_buf {int asn_len; int* asn_cptr; } ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;
typedef  int asn_len_t ;

/* Variables and functions */
 int ASN_ERR_EOBUF ; 
 int ASN_ERR_FAILED ; 
 int ASN_ERR_OK ; 
 int ASN_MAXLENLEN ; 
 int ASN_TYPE_MASK ; 
 int /*<<< orphan*/  asn_error (struct asn_buf*,char*,...) ; 

enum asn_err
asn_get_header(struct asn_buf *b, u_char *type, asn_len_t *len)
{
	u_int length;

	if (b->asn_len == 0) {
		asn_error(b, "no identifier for header");
		return (ASN_ERR_EOBUF);
	}
	*type = *b->asn_cptr;
	if ((*type & ASN_TYPE_MASK) > 0x30) {
		asn_error(b, "types > 0x30 not supported (%u)",
		    *type & ASN_TYPE_MASK);
		return (ASN_ERR_FAILED);
	}
	b->asn_cptr++;
	b->asn_len--;
	if (b->asn_len == 0) {
		asn_error(b, "no length field");
		return (ASN_ERR_EOBUF);
	}
	if (*b->asn_cptr & 0x80) {
		length = *b->asn_cptr++ & 0x7f;
		b->asn_len--;
		if (length == 0) {
			asn_error(b, "indefinite length not supported");
			return (ASN_ERR_FAILED);
		}
		if (length > ASN_MAXLENLEN) {
			asn_error(b, "long length too long (%u)", length);
			return (ASN_ERR_FAILED);
		}
		if (length > b->asn_len) {
			asn_error(b, "long length truncated");
			return (ASN_ERR_EOBUF);
		}
		*len = 0;
		while (length--) {
			*len = (*len << 8) | *b->asn_cptr++;
			b->asn_len--;
		}
	} else {
		*len = *b->asn_cptr++;
		b->asn_len--;
	}
	if (*len > b->asn_len) {
		asn_error(b, "len %u exceeding asn_len %u", *len, b->asn_len);
		return (ASN_ERR_EOBUF);
	}
	
	return (ASN_ERR_OK);
}