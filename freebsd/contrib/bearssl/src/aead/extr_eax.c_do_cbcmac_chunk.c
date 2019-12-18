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
struct TYPE_5__ {int ptr; void const* buf; int /*<<< orphan*/  cbcmac; TYPE_2__** bctx; } ;
typedef  TYPE_1__ br_eax_context ;
struct TYPE_6__ {int /*<<< orphan*/  (* mac ) (TYPE_2__**,int /*<<< orphan*/ ,void const*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void const*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__**,int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static void
do_cbcmac_chunk(br_eax_context *ctx, const void *data, size_t len)
{
	size_t ptr;

	if (len == 0) {
		return;
	}
	ptr = len & (size_t)15;
	if (ptr == 0) {
		len -= 16;
		ptr = 16;
	} else {
		len -= ptr;
	}
	if (ctx->ptr == 16) {
		(*ctx->bctx)->mac(ctx->bctx, ctx->cbcmac,
			ctx->buf, sizeof ctx->buf);
	}
	(*ctx->bctx)->mac(ctx->bctx, ctx->cbcmac, data, len);
	memcpy(ctx->buf, (const unsigned char *)data + len, ptr);
	ctx->ptr = ptr;
}