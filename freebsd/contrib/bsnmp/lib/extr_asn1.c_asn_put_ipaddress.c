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
typedef  int /*<<< orphan*/  u_char ;
struct asn_buf {int asn_len; int asn_ptr; } ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;

/* Variables and functions */
 int ASN_APP_IPADDRESS ; 
 int ASN_CLASS_APPLICATION ; 
 int ASN_ERR_EOBUF ; 
 int ASN_ERR_OK ; 
 int asn_put_header (struct asn_buf*,int,int) ; 
 int /*<<< orphan*/  memcpy (int,int /*<<< orphan*/  const*,int) ; 

enum asn_err
asn_put_ipaddress(struct asn_buf *b, const u_char *addr)
{
	enum asn_err err;

	if ((err = asn_put_header(b, ASN_CLASS_APPLICATION|ASN_APP_IPADDRESS,
	    4)) != ASN_ERR_OK)
		return (err);
	if (b->asn_len < 4)
		return (ASN_ERR_EOBUF);

	memcpy(b->asn_ptr, addr, 4);
	b->asn_ptr += 4;
	b->asn_len -= 4;
	return (ASN_ERR_OK);
}