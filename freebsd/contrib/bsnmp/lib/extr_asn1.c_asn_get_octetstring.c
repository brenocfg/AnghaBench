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
typedef  int /*<<< orphan*/  u_int ;
typedef  scalar_t__ u_char ;
struct asn_buf {int dummy; } ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;
typedef  int /*<<< orphan*/  asn_len_t ;

/* Variables and functions */
 int ASN_ERR_OK ; 
 int ASN_ERR_TAG ; 
 scalar_t__ ASN_TYPE_OCTETSTRING ; 
 int /*<<< orphan*/  asn_error (struct asn_buf*,char*,scalar_t__) ; 
 int asn_get_header (struct asn_buf*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int asn_get_octetstring_raw (struct asn_buf*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

enum asn_err
asn_get_octetstring(struct asn_buf *b, u_char *octets, u_int *noctets)
{
	enum asn_err err;
	u_char type;
	asn_len_t len;

	if ((err = asn_get_header(b, &type, &len)) != ASN_ERR_OK)
		return (err);
	if (type != ASN_TYPE_OCTETSTRING) {
		asn_error(b, "bad type for octetstring (%u)", type);
		return (ASN_ERR_TAG);
	}
	return (asn_get_octetstring_raw(b, len, octets, noctets));
}