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
struct asn1_ctx {unsigned int end; unsigned int pointer; } ;

/* Variables and functions */
 int /*<<< orphan*/  asn1_octet_decode (struct asn1_ctx*,unsigned char*) ; 

__attribute__((used)) static unsigned char asn1_length_decode(struct asn1_ctx *ctx,
					unsigned int *def,
					unsigned int *len)
{
	unsigned char ch, cnt;

	if (!asn1_octet_decode(ctx, &ch))
		return 0;

	if (ch == 0x80)
		*def = 0;
	else {
		*def = 1;

		if (ch < 0x80)
			*len = ch;
		else {
			cnt = ch & 0x7F;
			*len = 0;

			while (cnt > 0) {
				if (!asn1_octet_decode(ctx, &ch))
					return 0;
				*len <<= 8;
				*len |= ch;
				cnt--;
			}
		}
	}

	/* don't trust len bigger than ctx buffer */
	if (*len > ctx->end - ctx->pointer)
		return 0;

	return 1;
}