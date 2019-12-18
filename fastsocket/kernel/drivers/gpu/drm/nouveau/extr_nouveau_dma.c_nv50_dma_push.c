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
typedef  scalar_t__ u64 ;
struct nouveau_vma {scalar_t__ offset; } ;
struct TYPE_5__ {int ib_put; int ib_base; int ib_free; int ib_max; } ;
struct TYPE_4__ {struct nouveau_bo* buffer; } ;
struct nouveau_channel {TYPE_2__ dma; int /*<<< orphan*/  object; int /*<<< orphan*/  cli; TYPE_1__ push; } ;
struct nouveau_bo {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_MEMORYBARRIER () ; 
 int lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  nouveau_bo_rd32 (struct nouveau_bo*,int /*<<< orphan*/ ) ; 
 struct nouveau_vma* nouveau_bo_vma_find (struct nouveau_bo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_bo_wr32 (struct nouveau_bo*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* nv_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_wo32 (int /*<<< orphan*/ ,int,int) ; 
 int upper_32_bits (scalar_t__) ; 

void
nv50_dma_push(struct nouveau_channel *chan, struct nouveau_bo *bo,
	      int delta, int length)
{
	struct nouveau_bo *pb = chan->push.buffer;
	struct nouveau_vma *vma;
	int ip = (chan->dma.ib_put * 2) + chan->dma.ib_base;
	u64 offset;

	vma = nouveau_bo_vma_find(bo, nv_client(chan->cli)->vm);
	BUG_ON(!vma);
	offset = vma->offset + delta;

	BUG_ON(chan->dma.ib_free < 1);

	nouveau_bo_wr32(pb, ip++, lower_32_bits(offset));
	nouveau_bo_wr32(pb, ip++, upper_32_bits(offset) | length << 8);

	chan->dma.ib_put = (chan->dma.ib_put + 1) & chan->dma.ib_max;

	DRM_MEMORYBARRIER();
	/* Flush writes. */
	nouveau_bo_rd32(pb, 0);

	nv_wo32(chan->object, 0x8c, chan->dma.ib_put);
	chan->dma.ib_free--;
}