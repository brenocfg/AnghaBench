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
struct asn_buf {scalar_t__ asn_len; int /*<<< orphan*/  asn_ptr; } ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;

/* Variables and functions */
 int ASN_ERR_EOBUF ; 
 int ASN_ERR_OK ; 
 int /*<<< orphan*/  ASN_TYPE_OCTETSTRING ; 
 int asn_put_header (struct asn_buf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__) ; 

enum asn_err
asn_put_octetstring(struct asn_buf *b, const u_char *octets, u_int noctets)
{
	enum asn_err ret;

	if ((ret = asn_put_header(b, ASN_TYPE_OCTETSTRING, noctets)) != ASN_ERR_OK)
		return (ret);
	if (b->asn_len < noctets)
		return (ASN_ERR_EOBUF);

	memcpy(b->asn_ptr, octets, noctets);
	b->asn_ptr += noctets;
	b->asn_len -= noctets;
	return (ASN_ERR_OK);
}