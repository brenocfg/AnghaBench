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
struct asn_buf {scalar_t__ asn_len; int /*<<< orphan*/  asn_cptr; } ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;
typedef  scalar_t__ asn_len_t ;

/* Variables and functions */
 int ASN_ERR_EOBUF ; 
 int ASN_ERR_OK ; 

enum asn_err
asn_skip(struct asn_buf *b, asn_len_t len)
{
	if (b->asn_len < len)
		return (ASN_ERR_EOBUF);
	b->asn_cptr += len;
	b->asn_len -= len;
	return (ASN_ERR_OK);
}