#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_5__ {int (* sync32 ) (struct nouveau_channel*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {scalar_t__ offset; } ;
struct TYPE_6__ {scalar_t__ offset; } ;
struct nv84_fence_chan {TYPE_2__ base; TYPE_1__ vma; TYPE_3__ vma_gart; } ;
struct nouveau_fifo_chan {int chid; } ;
struct nouveau_fence {int /*<<< orphan*/  sequence; scalar_t__ sysmem; } ;
struct nouveau_channel {scalar_t__ object; struct nv84_fence_chan* fence; } ;

/* Variables and functions */
 int stub1 (struct nouveau_channel*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv84_fence_sync(struct nouveau_fence *fence,
		struct nouveau_channel *prev, struct nouveau_channel *chan)
{
	struct nv84_fence_chan *fctx = chan->fence;
	struct nouveau_fifo_chan *fifo = (void *)prev->object;
	u64 addr = fifo->chid * 16;

	if (fence->sysmem)
		addr += fctx->vma_gart.offset;
	else
		addr += fctx->vma.offset;

	return fctx->base.sync32(chan, addr, fence->sequence);
}