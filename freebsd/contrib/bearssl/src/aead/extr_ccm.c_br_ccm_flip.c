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
struct TYPE_4__ {size_t ptr; int /*<<< orphan*/  buf; int /*<<< orphan*/  cbcmac; TYPE_2__** bctx; } ;
typedef  TYPE_1__ br_ccm_context ;
struct TYPE_5__ {int /*<<< orphan*/  (* mac ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
br_ccm_flip(br_ccm_context *ctx)
{
	size_t ptr;

	/*
	 * Complete AAD partial block with zeros, if necessary.
	 */
	ptr = ctx->ptr;
	if (ptr != 0) {
		memset(ctx->buf + ptr, 0, (sizeof ctx->buf) - ptr);
		(*ctx->bctx)->mac(ctx->bctx, ctx->cbcmac,
			ctx->buf, sizeof ctx->buf);
		ctx->ptr = 0;
	}

	/*
	 * Counter was already set by br_ccm_reset().
	 */
}