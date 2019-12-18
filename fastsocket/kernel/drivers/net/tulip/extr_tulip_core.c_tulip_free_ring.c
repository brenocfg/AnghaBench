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
struct tulip_private {TYPE_3__* tx_buffers; int /*<<< orphan*/  pdev; TYPE_2__* rx_ring; TYPE_1__* rx_buffers; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_6__ {scalar_t__ mapping; struct sk_buff* skb; } ;
struct TYPE_5__ {int /*<<< orphan*/  buffer1; scalar_t__ length; scalar_t__ status; } ;
struct TYPE_4__ {scalar_t__ mapping; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  PKT_BUF_SZ ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct tulip_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tulip_free_ring (struct net_device *dev)
{
	struct tulip_private *tp = netdev_priv(dev);
	int i;

	/* Free all the skbuffs in the Rx queue. */
	for (i = 0; i < RX_RING_SIZE; i++) {
		struct sk_buff *skb = tp->rx_buffers[i].skb;
		dma_addr_t mapping = tp->rx_buffers[i].mapping;

		tp->rx_buffers[i].skb = NULL;
		tp->rx_buffers[i].mapping = 0;

		tp->rx_ring[i].status = 0;	/* Not owned by Tulip chip. */
		tp->rx_ring[i].length = 0;
		/* An invalid address. */
		tp->rx_ring[i].buffer1 = cpu_to_le32(0xBADF00D0);
		if (skb) {
			pci_unmap_single(tp->pdev, mapping, PKT_BUF_SZ,
					 PCI_DMA_FROMDEVICE);
			dev_kfree_skb (skb);
		}
	}

	for (i = 0; i < TX_RING_SIZE; i++) {
		struct sk_buff *skb = tp->tx_buffers[i].skb;

		if (skb != NULL) {
			pci_unmap_single(tp->pdev, tp->tx_buffers[i].mapping,
					 skb->len, PCI_DMA_TODEVICE);
			dev_kfree_skb (skb);
		}
		tp->tx_buffers[i].skb = NULL;
		tp->tx_buffers[i].mapping = 0;
	}
}