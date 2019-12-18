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
struct dma_async_tx_descriptor {int flags; } ;
struct iop_adma_desc_slot {int unmap_len; int unmap_src_cnt; struct iop_adma_desc_slot* group_head; scalar_t__ pq_check_result; struct dma_async_tx_descriptor async_tx; } ;
struct iop_adma_chan {TYPE_2__* device; } ;
struct device {int dummy; } ;
typedef  enum dma_ctrl_flags { ____Placeholder_dma_ctrl_flags } dma_ctrl_flags ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int DMA_COMPL_SKIP_DEST_UNMAP ; 
 int DMA_COMPL_SKIP_SRC_UNMAP ; 
 int DMA_PREP_CONTINUE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iop_desc_get_dest_addr (struct iop_adma_desc_slot*,struct iop_adma_chan*) ; 
 int /*<<< orphan*/  iop_desc_get_qdest_addr (struct iop_adma_desc_slot*,struct iop_adma_chan*) ; 
 int /*<<< orphan*/  iop_desc_get_src_addr (struct iop_adma_desc_slot*,struct iop_adma_chan*,int) ; 

__attribute__((used)) static void
iop_desc_unmap_pq(struct iop_adma_chan *iop_chan, struct iop_adma_desc_slot *desc)
{
	struct dma_async_tx_descriptor *tx = &desc->async_tx;
	struct iop_adma_desc_slot *unmap = desc->group_head;
	struct device *dev = &iop_chan->device->pdev->dev;
	u32 len = unmap->unmap_len;
	enum dma_ctrl_flags flags = tx->flags;
	u32 src_cnt = unmap->unmap_src_cnt;
	dma_addr_t pdest = iop_desc_get_dest_addr(unmap, iop_chan);
	dma_addr_t qdest = iop_desc_get_qdest_addr(unmap, iop_chan);
	int i;

	if (tx->flags & DMA_PREP_CONTINUE)
		src_cnt -= 3;

	if (!(flags & DMA_COMPL_SKIP_DEST_UNMAP) && !desc->pq_check_result) {
		dma_unmap_page(dev, pdest, len, DMA_BIDIRECTIONAL);
		dma_unmap_page(dev, qdest, len, DMA_BIDIRECTIONAL);
	}

	if (!(flags & DMA_COMPL_SKIP_SRC_UNMAP)) {
		dma_addr_t addr;

		for (i = 0; i < src_cnt; i++) {
			addr = iop_desc_get_src_addr(unmap, iop_chan, i);
			dma_unmap_page(dev, addr, len, DMA_TO_DEVICE);
		}
		if (desc->pq_check_result) {
			dma_unmap_page(dev, pdest, len, DMA_TO_DEVICE);
			dma_unmap_page(dev, qdest, len, DMA_TO_DEVICE);
		}
	}

	desc->group_head = NULL;
}