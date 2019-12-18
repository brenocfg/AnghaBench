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
struct asn_oid {scalar_t__ len; int* subs; } ;
struct asn_buf {scalar_t__ asn_len; int* asn_cptr; } ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;
typedef  int asn_subid_t ;
typedef  scalar_t__ asn_len_t ;

/* Variables and functions */
 int ASN_ERR_BADLEN ; 
 int ASN_ERR_EOBUF ; 
 int ASN_ERR_OK ; 
 int ASN_ERR_RANGE ; 
 int ASN_MAXID ; 
 scalar_t__ ASN_MAXOIDLEN ; 
 int /*<<< orphan*/  asn_error (struct asn_buf*,char*,...) ; 

enum asn_err
asn_get_objid_raw(struct asn_buf *b, asn_len_t len, struct asn_oid *oid)
{
	asn_subid_t subid;
	enum asn_err err;

	if (b->asn_len < len) {
		asn_error(b, "truncated OBJID");
		return (ASN_ERR_EOBUF);
	}
	oid->len = 0;
	if (len == 0) {
		asn_error(b, "short OBJID");
		oid->subs[oid->len++] = 0;
		oid->subs[oid->len++] = 0;
		return (ASN_ERR_BADLEN);
	}
	err = ASN_ERR_OK;
	while (len != 0) {
		if (oid->len == ASN_MAXOIDLEN) {
			asn_error(b, "OID too long (%u)", oid->len);
			b->asn_cptr += len;
			b->asn_len -= len;
			return (ASN_ERR_BADLEN);
		}
		subid = 0;
		do {
			if (len == 0) {
				asn_error(b, "unterminated subid");
				return (ASN_ERR_EOBUF);
			}
			if (subid > (ASN_MAXID >> 7)) {
				asn_error(b, "OBID subid too larger");
				err = ASN_ERR_RANGE;
			}
			subid = (subid << 7) | (*b->asn_cptr & 0x7f);
			len--;
			b->asn_len--;
		} while (*b->asn_cptr++ & 0x80);
		if (oid->len == 0) {
			if (subid < 80) {
				oid->subs[oid->len++] = subid / 40;
				oid->subs[oid->len++] = subid % 40;
			} else {
				oid->subs[oid->len++] = 2;
				oid->subs[oid->len++] = subid - 80;
			}
		} else {
			oid->subs[oid->len++] = subid;
		}
	}
	return (err);

}