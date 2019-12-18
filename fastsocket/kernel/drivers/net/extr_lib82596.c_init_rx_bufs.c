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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct i596_rfd {void* cmd; void* b_next; struct i596_rfd* v_next; struct i596_rfd* v_prev; void* rbd; void* size; void* b_data; int /*<<< orphan*/  v_data; struct sk_buff* skb; void* b_addr; } ;
struct i596_rbd {void* cmd; void* b_next; struct i596_rbd* v_next; struct i596_rbd* v_prev; void* rbd; void* size; void* b_data; int /*<<< orphan*/  v_data; struct sk_buff* skb; void* b_addr; } ;
struct i596_private {struct i596_rfd* rbd_head; struct i596_rfd* rfd_head; struct i596_dma* dma; } ;
struct TYPE_4__ {void* rfd; } ;
struct i596_dma {struct i596_rfd* rfds; TYPE_2__ scb; struct i596_rfd* rbds; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int CMD_EOL ; 
 int CMD_FLEX ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_WBACK_INV (struct net_device*,struct i596_dma*,int) ; 
 void* I596_NULL ; 
 int PKT_BUF_SZ ; 
 void* SWAP16 (int) ; 
 void* SWAP32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 struct i596_private* netdev_priv (struct net_device*) ; 
 int rx_ring_size ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  virt_to_dma (struct i596_private*,struct i596_rfd*) ; 

__attribute__((used)) static inline int init_rx_bufs(struct net_device *dev)
{
	struct i596_private *lp = netdev_priv(dev);
	struct i596_dma *dma = lp->dma;
	int i;
	struct i596_rfd *rfd;
	struct i596_rbd *rbd;

	/* First build the Receive Buffer Descriptor List */

	for (i = 0, rbd = dma->rbds; i < rx_ring_size; i++, rbd++) {
		dma_addr_t dma_addr;
		struct sk_buff *skb = netdev_alloc_skb(dev, PKT_BUF_SZ + 4);

		if (skb == NULL)
			return -1;
		skb_reserve(skb, 2);
		dma_addr = dma_map_single(dev->dev.parent, skb->data,
					  PKT_BUF_SZ, DMA_FROM_DEVICE);
		rbd->v_next = rbd+1;
		rbd->b_next = SWAP32(virt_to_dma(lp, rbd+1));
		rbd->b_addr = SWAP32(virt_to_dma(lp, rbd));
		rbd->skb = skb;
		rbd->v_data = skb->data;
		rbd->b_data = SWAP32(dma_addr);
		rbd->size = SWAP16(PKT_BUF_SZ);
	}
	lp->rbd_head = dma->rbds;
	rbd = dma->rbds + rx_ring_size - 1;
	rbd->v_next = dma->rbds;
	rbd->b_next = SWAP32(virt_to_dma(lp, dma->rbds));

	/* Now build the Receive Frame Descriptor List */

	for (i = 0, rfd = dma->rfds; i < rx_ring_size; i++, rfd++) {
		rfd->rbd = I596_NULL;
		rfd->v_next = rfd+1;
		rfd->v_prev = rfd-1;
		rfd->b_next = SWAP32(virt_to_dma(lp, rfd+1));
		rfd->cmd = SWAP16(CMD_FLEX);
	}
	lp->rfd_head = dma->rfds;
	dma->scb.rfd = SWAP32(virt_to_dma(lp, dma->rfds));
	rfd = dma->rfds;
	rfd->rbd = SWAP32(virt_to_dma(lp, lp->rbd_head));
	rfd->v_prev = dma->rfds + rx_ring_size - 1;
	rfd = dma->rfds + rx_ring_size - 1;
	rfd->v_next = dma->rfds;
	rfd->b_next = SWAP32(virt_to_dma(lp, dma->rfds));
	rfd->cmd = SWAP16(CMD_EOL|CMD_FLEX);

	DMA_WBACK_INV(dev, dma, sizeof(struct i596_dma));
	return 0;
}