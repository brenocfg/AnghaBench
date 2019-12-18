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
struct rx_queue {scalar_t__ rx_desc_count; scalar_t__ rx_ring_size; scalar_t__ rx_used_desc; int index; struct sk_buff** rx_skb; struct rx_desc* rx_desc_area; } ;
struct rx_desc {int cmd_sts; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf_ptr; } ;
struct mv643xx_eth_private {int oom; int work_rx_refill; int /*<<< orphan*/  skb_size; TYPE_2__* dev; int /*<<< orphan*/  rx_recycle; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int BUFFER_OWNED_BY_DMA ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int RX_ENABLE_INTERRUPT ; 
 int SKB_DMA_REALIGN ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mv643xx_eth_private* rxq_to_mp (struct rx_queue*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int rxq_refill(struct rx_queue *rxq, int budget)
{
	struct mv643xx_eth_private *mp = rxq_to_mp(rxq);
	int refilled;

	refilled = 0;
	while (refilled < budget && rxq->rx_desc_count < rxq->rx_ring_size) {
		struct sk_buff *skb;
		int rx;
		struct rx_desc *rx_desc;

		skb = __skb_dequeue(&mp->rx_recycle);
		if (skb == NULL)
			skb = dev_alloc_skb(mp->skb_size);

		if (skb == NULL) {
			mp->oom = 1;
			goto oom;
		}

		if (SKB_DMA_REALIGN)
			skb_reserve(skb, SKB_DMA_REALIGN);

		refilled++;
		rxq->rx_desc_count++;

		rx = rxq->rx_used_desc++;
		if (rxq->rx_used_desc == rxq->rx_ring_size)
			rxq->rx_used_desc = 0;

		rx_desc = rxq->rx_desc_area + rx;

		rx_desc->buf_ptr = dma_map_single(mp->dev->dev.parent,
						  skb->data, mp->skb_size,
						  DMA_FROM_DEVICE);
		rx_desc->buf_size = mp->skb_size;
		rxq->rx_skb[rx] = skb;
		wmb();
		rx_desc->cmd_sts = BUFFER_OWNED_BY_DMA | RX_ENABLE_INTERRUPT;
		wmb();

		/*
		 * The hardware automatically prepends 2 bytes of
		 * dummy data to each received packet, so that the
		 * IP header ends up 16-byte aligned.
		 */
		skb_reserve(skb, 2);
	}

	if (refilled < budget)
		mp->work_rx_refill &= ~(1 << rxq->index);

oom:
	return refilled;
}