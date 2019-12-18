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
typedef  int u32 ;
struct rx_header {scalar_t__ flags; scalar_t__ len; } ;
struct ring_info {int /*<<< orphan*/  mapping; TYPE_1__* skb; } ;
struct dma_desc {int /*<<< orphan*/  addr; int /*<<< orphan*/  ctrl; } ;
struct b44 {int flags; TYPE_2__* sdev; int /*<<< orphan*/  rx_ring_dma; struct ring_info* rx_buffers; struct dma_desc* rx_ring; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_5__ {int /*<<< orphan*/  dma_dev; } ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 int B44_FLAG_RX_RING_HACK ; 
 int B44_RX_RING_SIZE ; 
 int /*<<< orphan*/  DESC_CTRL_EOT ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  RX_PKT_BUF_SZ ; 
 int /*<<< orphan*/  b44_sync_dma_desc_for_cpu (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b44_sync_dma_desc_for_device (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b44_recycle_rx(struct b44 *bp, int src_idx, u32 dest_idx_unmasked)
{
	struct dma_desc *src_desc, *dest_desc;
	struct ring_info *src_map, *dest_map;
	struct rx_header *rh;
	int dest_idx;
	__le32 ctrl;

	dest_idx = dest_idx_unmasked & (B44_RX_RING_SIZE - 1);
	dest_desc = &bp->rx_ring[dest_idx];
	dest_map = &bp->rx_buffers[dest_idx];
	src_desc = &bp->rx_ring[src_idx];
	src_map = &bp->rx_buffers[src_idx];

	dest_map->skb = src_map->skb;
	rh = (struct rx_header *) src_map->skb->data;
	rh->len = 0;
	rh->flags = 0;
	dest_map->mapping = src_map->mapping;

	if (bp->flags & B44_FLAG_RX_RING_HACK)
		b44_sync_dma_desc_for_cpu(bp->sdev, bp->rx_ring_dma,
			                 src_idx * sizeof(*src_desc),
			                 DMA_BIDIRECTIONAL);

	ctrl = src_desc->ctrl;
	if (dest_idx == (B44_RX_RING_SIZE - 1))
		ctrl |= cpu_to_le32(DESC_CTRL_EOT);
	else
		ctrl &= cpu_to_le32(~DESC_CTRL_EOT);

	dest_desc->ctrl = ctrl;
	dest_desc->addr = src_desc->addr;

	src_map->skb = NULL;

	if (bp->flags & B44_FLAG_RX_RING_HACK)
		b44_sync_dma_desc_for_device(bp->sdev, bp->rx_ring_dma,
					     dest_idx * sizeof(*dest_desc),
					     DMA_BIDIRECTIONAL);

	dma_sync_single_for_device(bp->sdev->dma_dev, dest_map->mapping,
				   RX_PKT_BUF_SZ,
				   DMA_FROM_DEVICE);
}