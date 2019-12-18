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
struct asn1_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  asn1_octet_decode (struct asn1_ctx*,unsigned char*) ; 
 int /*<<< orphan*/  asn1_tag_decode (struct asn1_ctx*,unsigned int*) ; 

__attribute__((used)) static unsigned char
asn1_id_decode(struct asn1_ctx *ctx,
	       unsigned int *cls, unsigned int *con, unsigned int *tag)
{
	unsigned char ch;

	if (!asn1_octet_decode(ctx, &ch))
		return 0;

	*cls = (ch & 0xC0) >> 6;
	*con = (ch & 0x20) >> 5;
	*tag = (ch & 0x1F);

	if (*tag == 0x1F) {
		if (!asn1_tag_decode(ctx, tag))
			return 0;
	}
	return 1;
}