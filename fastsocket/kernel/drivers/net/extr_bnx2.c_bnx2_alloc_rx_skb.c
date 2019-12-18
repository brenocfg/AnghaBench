#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  size_t u16 ;
struct sk_buff {scalar_t__ data; } ;
struct l2_fhdr {int dummy; } ;
struct bnx2_sw_bd {struct l2_fhdr* desc; struct sk_buff* skb; } ;
struct bnx2_rx_ring_info {int /*<<< orphan*/  rx_prod_bseq; struct bnx2_rx_bd** rx_desc_ring; struct bnx2_sw_bd* rx_buf_ring; } ;
struct bnx2_rx_bd {int rx_bd_haddr_hi; int rx_bd_haddr_lo; } ;
struct bnx2 {int /*<<< orphan*/  rx_buf_use_size; TYPE_1__* pdev; int /*<<< orphan*/  rx_buf_size; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BNX2_RX_ALIGN ; 
 size_t BNX2_RX_IDX (size_t) ; 
 size_t BNX2_RX_RING (size_t) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 struct sk_buff* __netdev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pci_unmap_addr_set (struct bnx2_sw_bd*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 scalar_t__ unlikely (unsigned long) ; 

__attribute__((used)) static inline int
bnx2_alloc_rx_skb(struct bnx2 *bp, struct bnx2_rx_ring_info *rxr, u16 index, gfp_t gfp)
{
	struct sk_buff *skb;
	struct bnx2_sw_bd *rx_buf = &rxr->rx_buf_ring[index];
	dma_addr_t mapping;
	struct bnx2_rx_bd *rxbd =
		&rxr->rx_desc_ring[BNX2_RX_RING(index)][BNX2_RX_IDX(index)];
	unsigned long align;

	skb = __netdev_alloc_skb(bp->dev, bp->rx_buf_size, gfp);
	if (skb == NULL) {
		return -ENOMEM;
	}

	if (unlikely((align = (unsigned long) skb->data & (BNX2_RX_ALIGN - 1))))
		skb_reserve(skb, BNX2_RX_ALIGN - align);

	mapping = dma_map_single(&bp->pdev->dev, skb->data, bp->rx_buf_use_size,
				 PCI_DMA_FROMDEVICE);
	if (dma_mapping_error(&bp->pdev->dev, mapping)) {
		dev_kfree_skb(skb);
		return -EIO;
	}

	rx_buf->skb = skb;
	rx_buf->desc = (struct l2_fhdr *) skb->data;
	pci_unmap_addr_set(rx_buf, mapping, mapping);

	rxbd->rx_bd_haddr_hi = (u64) mapping >> 32;
	rxbd->rx_bd_haddr_lo = (u64) mapping & 0xffffffff;

	rxr->rx_prod_bseq += bp->rx_buf_use_size;

	return 0;
}