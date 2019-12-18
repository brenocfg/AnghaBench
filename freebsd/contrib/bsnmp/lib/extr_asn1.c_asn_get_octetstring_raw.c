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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct asn_buf {scalar_t__ asn_len; int /*<<< orphan*/  asn_cptr; } ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;
typedef  scalar_t__ asn_len_t ;

/* Variables and functions */
 int ASN_ERR_EOBUF ; 
 int ASN_ERR_OK ; 
 int ASN_ERR_RANGE ; 
 int /*<<< orphan*/  asn_error (struct asn_buf*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

enum asn_err
asn_get_octetstring_raw(struct asn_buf *b, asn_len_t len, u_char *octets,
    u_int *noctets)
{
	enum asn_err err = ASN_ERR_OK;

	if (*noctets < len) {
		asn_error(b, "octetstring truncated");
		err = ASN_ERR_RANGE;
	}
	if (b->asn_len < len) {
		asn_error(b, "truncatet octetstring");
		return (ASN_ERR_EOBUF);
	}
	if (*noctets < len)
		memcpy(octets, b->asn_cptr, *noctets);
	else
		memcpy(octets, b->asn_cptr, len);
	*noctets = len;
	b->asn_cptr += len;
	b->asn_len -= len;
	return (err);
}