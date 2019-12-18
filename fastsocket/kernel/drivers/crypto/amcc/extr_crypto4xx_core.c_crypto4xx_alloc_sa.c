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
typedef  int u32 ;
struct crypto4xx_ctx {int sa_len; int /*<<< orphan*/ * sa_out; int /*<<< orphan*/ * sa_in; int /*<<< orphan*/  sa_in_dma_addr; TYPE_2__* dev; int /*<<< orphan*/  sa_out_dma_addr; } ;
struct TYPE_4__ {TYPE_1__* core_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int crypto4xx_alloc_sa(struct crypto4xx_ctx *ctx, u32 size)
{
	ctx->sa_in = dma_alloc_coherent(ctx->dev->core_dev->device, size * 4,
					&ctx->sa_in_dma_addr, GFP_ATOMIC);
	if (ctx->sa_in == NULL)
		return -ENOMEM;

	ctx->sa_out = dma_alloc_coherent(ctx->dev->core_dev->device, size * 4,
					 &ctx->sa_out_dma_addr, GFP_ATOMIC);
	if (ctx->sa_out == NULL) {
		dma_free_coherent(ctx->dev->core_dev->device,
				  ctx->sa_len * 4,
				  ctx->sa_in, ctx->sa_in_dma_addr);
		return -ENOMEM;
	}

	memset(ctx->sa_in, 0, size * 4);
	memset(ctx->sa_out, 0, size * 4);
	ctx->sa_len = size;

	return 0;
}