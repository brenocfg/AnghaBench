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
typedef  int /*<<< orphan*/  u32 ;
struct sa_state_record {int dummy; } ;
struct crypto4xx_ctx {int /*<<< orphan*/  state_record; int /*<<< orphan*/  state_record_dma_addr; TYPE_2__* dev; } ;
struct TYPE_4__ {TYPE_1__* core_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

u32 crypto4xx_alloc_state_record(struct crypto4xx_ctx *ctx)
{
	ctx->state_record = dma_alloc_coherent(ctx->dev->core_dev->device,
				sizeof(struct sa_state_record),
				&ctx->state_record_dma_addr, GFP_ATOMIC);
	if (!ctx->state_record_dma_addr)
		return -ENOMEM;
	memset(ctx->state_record, 0, sizeof(struct sa_state_record));

	return 0;
}