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
struct asn_buf {scalar_t__ asn_len; int /*<<< orphan*/ * asn_ptr; } ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;

/* Variables and functions */
 int ASN_ERR_EOBUF ; 
 int ASN_ERR_OK ; 
 int /*<<< orphan*/  ASN_MAXLEN ; 
 scalar_t__ TEMP_LEN ; 
 int asn_put_header (struct asn_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

enum asn_err
asn_put_temp_header(struct asn_buf *b, u_char type, u_char **ptr)
{
	int ret;

	if (b->asn_len < TEMP_LEN)
		return (ASN_ERR_EOBUF);
	*ptr = b->asn_ptr;
	if ((ret = asn_put_header(b, type, ASN_MAXLEN)) == ASN_ERR_OK)
		assert(b->asn_ptr == *ptr + TEMP_LEN);
	return (ret);
}