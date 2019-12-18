#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {void const* buf; scalar_t__ count_aad; int /*<<< orphan*/  h; int /*<<< orphan*/  y; int /*<<< orphan*/  (* gh ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,size_t) ;} ;
typedef  TYPE_1__ br_gcm_context ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void const*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,size_t) ; 

void
br_gcm_aad_inject(br_gcm_context *ctx, const void *data, size_t len)
{
	size_t ptr, dlen;

	ptr = (size_t)ctx->count_aad & (size_t)15;
	if (ptr != 0) {
		/*
		 * If there is a partial block, then we first try to
		 * complete it.
		 */
		size_t clen;

		clen = 16 - ptr;
		if (len < clen) {
			memcpy(ctx->buf + ptr, data, len);
			ctx->count_aad += (uint64_t)len;
			return;
		}
		memcpy(ctx->buf + ptr, data, clen);
		ctx->gh(ctx->y, ctx->h, ctx->buf, 16);
		data = (const unsigned char *)data + clen;
		len -= clen;
		ctx->count_aad += (uint64_t)clen;
	}

	/*
	 * Now AAD is aligned on a 16-byte block (with regards to GHASH).
	 * We process all complete blocks, and save the last partial
	 * block.
	 */
	dlen = len & ~(size_t)15;
	ctx->gh(ctx->y, ctx->h, data, dlen);
	memcpy(ctx->buf, (const unsigned char *)data + dlen, len - dlen);
	ctx->count_aad += (uint64_t)len;
}