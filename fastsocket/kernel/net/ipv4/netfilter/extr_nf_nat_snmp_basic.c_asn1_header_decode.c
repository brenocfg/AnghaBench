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
struct asn1_ctx {unsigned char* pointer; } ;

/* Variables and functions */
 unsigned int ASN1_PRI ; 
 int /*<<< orphan*/  asn1_id_decode (struct asn1_ctx*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  asn1_length_decode (struct asn1_ctx*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static unsigned char asn1_header_decode(struct asn1_ctx *ctx,
					unsigned char **eoc,
					unsigned int *cls,
					unsigned int *con,
					unsigned int *tag)
{
	unsigned int def, len;

	if (!asn1_id_decode(ctx, cls, con, tag))
		return 0;

	def = len = 0;
	if (!asn1_length_decode(ctx, &def, &len))
		return 0;

	/* primitive shall be definite, indefinite shall be constructed */
	if (*con == ASN1_PRI && !def)
		return 0;

	if (def)
		*eoc = ctx->pointer + len;
	else
		*eoc = NULL;
	return 1;
}