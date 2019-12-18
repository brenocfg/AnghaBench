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
struct TYPE_4__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct ks8695_priv {int /*<<< orphan*/  tx_ring_used; TYPE_3__* tx_buffers; int /*<<< orphan*/  dev; TYPE_2__* tx_ring; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/ * skb; scalar_t__ length; int /*<<< orphan*/  dma_ptr; } ;
struct TYPE_5__ {int owner; scalar_t__ data_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MAX_TX_DESC ; 
 int /*<<< orphan*/  TDES_OWN ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct ks8695_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static irqreturn_t
ks8695_tx_irq(int irq, void *dev_id)
{
	struct net_device *ndev = (struct net_device *)dev_id;
	struct ks8695_priv *ksp = netdev_priv(ndev);
	int buff_n;

	for (buff_n = 0; buff_n < MAX_TX_DESC; ++buff_n) {
		if (ksp->tx_buffers[buff_n].skb &&
		    !(ksp->tx_ring[buff_n].owner & cpu_to_le32(TDES_OWN))) {
			rmb();
			/* An SKB which is not owned by HW is present */
			/* Update the stats for the net_device */
			ndev->stats.tx_packets++;
			ndev->stats.tx_bytes += ksp->tx_buffers[buff_n].length;

			/* Free the packet from the ring */
			ksp->tx_ring[buff_n].data_ptr = 0;

			/* Free the sk_buff */
			dma_unmap_single(ksp->dev,
					 ksp->tx_buffers[buff_n].dma_ptr,
					 ksp->tx_buffers[buff_n].length,
					 DMA_TO_DEVICE);
			dev_kfree_skb_irq(ksp->tx_buffers[buff_n].skb);
			ksp->tx_buffers[buff_n].skb = NULL;
			ksp->tx_ring_used--;
		}
	}

	netif_wake_queue(ndev);

	return IRQ_HANDLED;
}