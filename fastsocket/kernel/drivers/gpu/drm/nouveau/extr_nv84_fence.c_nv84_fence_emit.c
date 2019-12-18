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
struct TYPE_6__ {int (* emit32 ) (struct nouveau_channel*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {scalar_t__ offset; } ;
struct TYPE_4__ {scalar_t__ offset; } ;
struct nv84_fence_chan {TYPE_3__ base; TYPE_2__ vma; TYPE_1__ vma_gart; } ;
struct nouveau_fifo_chan {int chid; } ;
struct nouveau_fence {int /*<<< orphan*/  sequence; scalar_t__ sysmem; struct nouveau_channel* channel; } ;
struct nouveau_channel {scalar_t__ object; struct nv84_fence_chan* fence; } ;

/* Variables and functions */
 int stub1 (struct nouveau_channel*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv84_fence_emit(struct nouveau_fence *fence)
{
	struct nouveau_channel *chan = fence->channel;
	struct nv84_fence_chan *fctx = chan->fence;
	struct nouveau_fifo_chan *fifo = (void *)chan->object;
	u64 addr = fifo->chid * 16;

	if (fence->sysmem)
		addr += fctx->vma_gart.offset;
	else
		addr += fctx->vma.offset;

	return fctx->base.emit32(chan, addr, fence->sequence);
}