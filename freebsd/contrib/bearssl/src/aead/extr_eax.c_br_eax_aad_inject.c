#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t ptr; scalar_t__ buf; } ;
typedef  TYPE_1__ br_eax_context ;

/* Variables and functions */
 int /*<<< orphan*/  do_cbcmac_chunk (TYPE_1__*,void const*,size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,size_t) ; 

void
br_eax_aad_inject(br_eax_context *ctx, const void *data, size_t len)
{
	size_t ptr;

	ptr = ctx->ptr;

	/*
	 * If there is a partial block, first complete it.
	 */
	if (ptr < 16) {
		size_t clen;

		clen = 16 - ptr;
		if (len <= clen) {
			memcpy(ctx->buf + ptr, data, len);
			ctx->ptr = ptr + len;
			return;
		}
		memcpy(ctx->buf + ptr, data, clen);
		data = (const unsigned char *)data + clen;
		len -= clen;
	}

	/*
	 * We now have a full block in buf[], and this is not the last
	 * block.
	 */
	do_cbcmac_chunk(ctx, data, len);
}