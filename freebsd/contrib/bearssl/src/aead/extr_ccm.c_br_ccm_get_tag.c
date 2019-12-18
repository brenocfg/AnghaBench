#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t ptr; size_t tag_len; int /*<<< orphan*/ * cbcmac; int /*<<< orphan*/ * tagmask; int /*<<< orphan*/  buf; TYPE_2__** bctx; } ;
typedef  TYPE_1__ br_ccm_context ;
struct TYPE_5__ {int /*<<< orphan*/  (* mac ) (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

size_t
br_ccm_get_tag(br_ccm_context *ctx, void *tag)
{
	size_t ptr;
	size_t u;

	/*
	 * If there is some buffered data, then we need to pad it with
	 * zeros and finish up CBC-MAC.
	 */
	ptr = ctx->ptr;
	if (ptr != 0) {
		memset(ctx->buf + ptr, 0, (sizeof ctx->buf) - ptr);
		(*ctx->bctx)->mac(ctx->bctx, ctx->cbcmac,
			ctx->buf, sizeof ctx->buf);
	}

	/*
	 * XOR the tag mask into the CBC-MAC output.
	 */
	for (u = 0; u < ctx->tag_len; u ++) {
		ctx->cbcmac[u] ^= ctx->tagmask[u];
	}
	memcpy(tag, ctx->cbcmac, ctx->tag_len);
	return ctx->tag_len;
}