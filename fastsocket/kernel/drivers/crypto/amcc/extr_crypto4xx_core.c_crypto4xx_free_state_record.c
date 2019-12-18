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
struct sa_state_record {int dummy; } ;
struct crypto4xx_ctx {scalar_t__ state_record_dma_addr; int /*<<< orphan*/ * state_record; TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* core_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 

void crypto4xx_free_state_record(struct crypto4xx_ctx *ctx)
{
	if (ctx->state_record != NULL)
		dma_free_coherent(ctx->dev->core_dev->device,
				  sizeof(struct sa_state_record),
				  ctx->state_record,
				  ctx->state_record_dma_addr);
	ctx->state_record_dma_addr = 0;
}