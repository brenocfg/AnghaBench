#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t ptr; unsigned char const* buf; int /*<<< orphan*/  cbcmac; TYPE_2__** bctx; } ;
typedef  TYPE_1__ br_ccm_context ;
struct TYPE_6__ {int /*<<< orphan*/  (* mac ) (TYPE_2__**,int /*<<< orphan*/ ,unsigned char const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char const*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__**,int /*<<< orphan*/ ,unsigned char const*,size_t) ; 

void
br_ccm_aad_inject(br_ccm_context *ctx, const void *data, size_t len)
{
	const unsigned char *dbuf;
	size_t ptr;

	dbuf = data;

	/*
	 * Complete partial block, if needed.
	 */
	ptr = ctx->ptr;
	if (ptr != 0) {
		size_t clen;

		clen = (sizeof ctx->buf) - ptr;
		if (clen > len) {
			memcpy(ctx->buf + ptr, dbuf, len);
			ctx->ptr = ptr + len;
			return;
		}
		memcpy(ctx->buf + ptr, dbuf, clen);
		dbuf += clen;
		len -= clen;
		(*ctx->bctx)->mac(ctx->bctx, ctx->cbcmac,
			ctx->buf, sizeof ctx->buf);
	}

	/*
	 * Process complete blocks.
	 */
	ptr = len & 15;
	len -= ptr;
	(*ctx->bctx)->mac(ctx->bctx, ctx->cbcmac, dbuf, len);
	dbuf += len;

	/*
	 * Copy last partial block in the context buffer.
	 */
	memcpy(ctx->buf, dbuf, ptr);
	ctx->ptr = ptr;
}