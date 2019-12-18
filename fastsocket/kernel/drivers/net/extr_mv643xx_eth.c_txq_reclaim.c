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
typedef  int u32 ;
struct tx_queue {int index; scalar_t__ tx_desc_count; int tx_used_desc; int tx_ring_size; int /*<<< orphan*/  tx_skb; struct tx_desc* tx_desc_area; } ;
struct tx_desc {int cmd_sts; int /*<<< orphan*/  byte_cnt; int /*<<< orphan*/  buf_ptr; } ;
struct sk_buff {int dummy; } ;
struct netdev_queue {int dummy; } ;
struct mv643xx_eth_private {scalar_t__ rx_ring_size; int work_tx; int /*<<< orphan*/  rx_recycle; int /*<<< orphan*/  skb_size; TYPE_2__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_errors; } ;
struct TYPE_5__ {TYPE_3__ dev; TYPE_1__ stats; } ;

/* Variables and functions */
 int BUFFER_OWNED_BY_DMA ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ERROR_SUMMARY ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int TX_FIRST_DESC ; 
 int TX_LAST_DESC ; 
 int /*<<< orphan*/  __netif_tx_lock (struct netdev_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __netif_tx_unlock (struct netdev_queue*) ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netdev_queue* netdev_get_tx_queue (TYPE_2__*,int) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_recycle_check (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 struct mv643xx_eth_private* txq_to_mp (struct tx_queue*) ; 

__attribute__((used)) static int txq_reclaim(struct tx_queue *txq, int budget, int force)
{
	struct mv643xx_eth_private *mp = txq_to_mp(txq);
	struct netdev_queue *nq = netdev_get_tx_queue(mp->dev, txq->index);
	int reclaimed;

	__netif_tx_lock(nq, smp_processor_id());

	reclaimed = 0;
	while (reclaimed < budget && txq->tx_desc_count > 0) {
		int tx_index;
		struct tx_desc *desc;
		u32 cmd_sts;
		struct sk_buff *skb;

		tx_index = txq->tx_used_desc;
		desc = &txq->tx_desc_area[tx_index];
		cmd_sts = desc->cmd_sts;

		if (cmd_sts & BUFFER_OWNED_BY_DMA) {
			if (!force)
				break;
			desc->cmd_sts = cmd_sts & ~BUFFER_OWNED_BY_DMA;
		}

		txq->tx_used_desc = tx_index + 1;
		if (txq->tx_used_desc == txq->tx_ring_size)
			txq->tx_used_desc = 0;

		reclaimed++;
		txq->tx_desc_count--;

		skb = NULL;
		if (cmd_sts & TX_LAST_DESC)
			skb = __skb_dequeue(&txq->tx_skb);

		if (cmd_sts & ERROR_SUMMARY) {
			dev_printk(KERN_INFO, &mp->dev->dev, "tx error\n");
			mp->dev->stats.tx_errors++;
		}

		if (cmd_sts & TX_FIRST_DESC) {
			dma_unmap_single(mp->dev->dev.parent, desc->buf_ptr,
					 desc->byte_cnt, DMA_TO_DEVICE);
		} else {
			dma_unmap_page(mp->dev->dev.parent, desc->buf_ptr,
				       desc->byte_cnt, DMA_TO_DEVICE);
		}

		if (skb != NULL) {
			if (skb_queue_len(&mp->rx_recycle) <
					mp->rx_ring_size &&
			    skb_recycle_check(skb, mp->skb_size))
				__skb_queue_head(&mp->rx_recycle, skb);
			else
				dev_kfree_skb(skb);
		}
	}

	__netif_tx_unlock(nq);

	if (reclaimed < budget)
		mp->work_tx &= ~(1 << txq->index);

	return reclaimed;
}