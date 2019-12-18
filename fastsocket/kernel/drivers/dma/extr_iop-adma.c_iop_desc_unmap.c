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
struct iop_adma_desc_slot {int unmap_len; int unmap_src_cnt; struct iop_adma_desc_slot* group_head; struct dma_async_tx_descriptor async_tx; } ;
struct iop_adma_chan {TYPE_2__* device; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  enum dma_ctrl_flags { ____Placeholder_dma_ctrl_flags } dma_ctrl_flags ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int DMA_BIDIRECTIONAL ; 
 int DMA_COMPL_SKIP_DEST_UNMAP ; 
 int DMA_COMPL_SKIP_SRC_UNMAP ; 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,scalar_t__,int,int) ; 
 scalar_t__ iop_desc_get_dest_addr (struct iop_adma_desc_slot*,struct iop_adma_chan*) ; 
 scalar_t__ iop_desc_get_src_addr (struct iop_adma_desc_slot*,struct iop_adma_chan*,int) ; 

__attribute__((used)) static void
iop_desc_unmap(struct iop_adma_chan *iop_chan, struct iop_adma_desc_slot *desc)
{
	struct dma_async_tx_descriptor *tx = &desc->async_tx;
	struct iop_adma_desc_slot *unmap = desc->group_head;
	struct device *dev = &iop_chan->device->pdev->dev;
	u32 len = unmap->unmap_len;
	enum dma_ctrl_flags flags = tx->flags;
	u32 src_cnt;
	dma_addr_t addr;
	dma_addr_t dest;

	src_cnt = unmap->unmap_src_cnt;
	dest = iop_desc_get_dest_addr(unmap, iop_chan);
	if (!(flags & DMA_COMPL_SKIP_DEST_UNMAP)) {
		enum dma_data_direction dir;

		if (src_cnt > 1) /* is xor? */
			dir = DMA_BIDIRECTIONAL;
		else
			dir = DMA_FROM_DEVICE;

		dma_unmap_page(dev, dest, len, dir);
	}

	if (!(flags & DMA_COMPL_SKIP_SRC_UNMAP)) {
		while (src_cnt--) {
			addr = iop_desc_get_src_addr(unmap, iop_chan, src_cnt);
			if (addr == dest)
				continue;
			dma_unmap_page(dev, addr, len, DMA_TO_DEVICE);
		}
	}
	desc->group_head = NULL;
}