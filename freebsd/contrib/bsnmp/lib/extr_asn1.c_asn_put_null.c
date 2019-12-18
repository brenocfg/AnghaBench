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
struct asn_buf {int dummy; } ;
typedef  enum asn_err { ____Placeholder_asn_err } asn_err ;

/* Variables and functions */
 int /*<<< orphan*/  ASN_TYPE_NULL ; 
 int asn_put_header (struct asn_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum asn_err
asn_put_null(struct asn_buf *b)
{
	return (asn_put_header(b, ASN_TYPE_NULL, 0));
}