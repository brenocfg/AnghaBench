#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crypto4xx_ctx {int sa_len; scalar_t__ sa_out_dma_addr; scalar_t__ sa_in_dma_addr; int /*<<< orphan*/ * sa_out; TYPE_1__* dev; int /*<<< orphan*/ * sa_in; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {TYPE_2__* core_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 

void crypto4xx_free_sa(struct crypto4xx_ctx *ctx)
{
	if (ctx->sa_in != NULL)
		dma_free_coherent(ctx->dev->core_dev->device, ctx->sa_len * 4,
				  ctx->sa_in, ctx->sa_in_dma_addr);
	if (ctx->sa_out != NULL)
		dma_free_coherent(ctx->dev->core_dev->device, ctx->sa_len * 4,
				  ctx->sa_out, ctx->sa_out_dma_addr);

	ctx->sa_in_dma_addr = 0;
	ctx->sa_out_dma_addr = 0;
	ctx->sa_len = 0;
}