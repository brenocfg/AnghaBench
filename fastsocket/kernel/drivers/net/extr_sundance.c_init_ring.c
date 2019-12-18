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
struct sk_buff {int /*<<< orphan*/  data; struct net_device* dev; } ;
struct netdev_private {unsigned int dirty_rx; unsigned int dirty_tx; int rx_buf_sz; int rx_ring_dma; TYPE_3__* tx_ring; int /*<<< orphan*/ ** tx_skbuff; TYPE_2__* rx_ring; int /*<<< orphan*/  pci_dev; struct sk_buff** rx_skbuff; scalar_t__ cur_task; scalar_t__ cur_tx; scalar_t__ cur_rx; } ;
struct net_device {int mtu; } ;
struct TYPE_6__ {scalar_t__ status; } ;
struct TYPE_5__ {TYPE_1__* frag; scalar_t__ status; void* next_desc; } ;
struct TYPE_4__ {void* length; void* addr; } ;

/* Variables and functions */
 int LastFrag ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int PKT_BUF_SZ ; 
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 void* cpu_to_le32 (int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static void init_ring(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	int i;

	np->cur_rx = np->cur_tx = 0;
	np->dirty_rx = np->dirty_tx = 0;
	np->cur_task = 0;

	np->rx_buf_sz = (dev->mtu <= 1520 ? PKT_BUF_SZ : dev->mtu + 16);

	/* Initialize all Rx descriptors. */
	for (i = 0; i < RX_RING_SIZE; i++) {
		np->rx_ring[i].next_desc = cpu_to_le32(np->rx_ring_dma +
			((i+1)%RX_RING_SIZE)*sizeof(*np->rx_ring));
		np->rx_ring[i].status = 0;
		np->rx_ring[i].frag[0].length = 0;
		np->rx_skbuff[i] = NULL;
	}

	/* Fill in the Rx buffers.  Handle allocation failure gracefully. */
	for (i = 0; i < RX_RING_SIZE; i++) {
		struct sk_buff *skb = dev_alloc_skb(np->rx_buf_sz);
		np->rx_skbuff[i] = skb;
		if (skb == NULL)
			break;
		skb->dev = dev;		/* Mark as being used by this device. */
		skb_reserve(skb, 2);	/* 16 byte align the IP header. */
		np->rx_ring[i].frag[0].addr = cpu_to_le32(
			pci_map_single(np->pci_dev, skb->data, np->rx_buf_sz,
				PCI_DMA_FROMDEVICE));
		np->rx_ring[i].frag[0].length = cpu_to_le32(np->rx_buf_sz | LastFrag);
	}
	np->dirty_rx = (unsigned int)(i - RX_RING_SIZE);

	for (i = 0; i < TX_RING_SIZE; i++) {
		np->tx_skbuff[i] = NULL;
		np->tx_ring[i].status = 0;
	}
	return;
}