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
struct sk_buff {int /*<<< orphan*/  data; struct net_device* dev; } ;
struct netdev_private {int cur_rx; int dirty_rx; int rx_buf_sz; TYPE_2__* rx_ring; int /*<<< orphan*/  pci_dev; struct sk_buff** rx_skbuff; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ status; TYPE_1__* frag; } ;
struct TYPE_3__ {void* length; void* addr; } ;

/* Variables and functions */
 int LastFrag ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int RX_RING_SIZE ; 
 void* cpu_to_le32 (int) ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static void refill_rx (struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	int entry;
	int cnt = 0;

	/* Refill the Rx ring buffers. */
	for (;(np->cur_rx - np->dirty_rx + RX_RING_SIZE) % RX_RING_SIZE > 0;
		np->dirty_rx = (np->dirty_rx + 1) % RX_RING_SIZE) {
		struct sk_buff *skb;
		entry = np->dirty_rx % RX_RING_SIZE;
		if (np->rx_skbuff[entry] == NULL) {
			skb = dev_alloc_skb(np->rx_buf_sz);
			np->rx_skbuff[entry] = skb;
			if (skb == NULL)
				break;		/* Better luck next round. */
			skb->dev = dev;		/* Mark as being used by this device. */
			skb_reserve(skb, 2);	/* Align IP on 16 byte boundaries */
			np->rx_ring[entry].frag[0].addr = cpu_to_le32(
				pci_map_single(np->pci_dev, skb->data,
					np->rx_buf_sz, PCI_DMA_FROMDEVICE));
		}
		/* Perhaps we need not reset this field. */
		np->rx_ring[entry].frag[0].length =
			cpu_to_le32(np->rx_buf_sz | LastFrag);
		np->rx_ring[entry].status = 0;
		cnt++;
	}
	return;
}