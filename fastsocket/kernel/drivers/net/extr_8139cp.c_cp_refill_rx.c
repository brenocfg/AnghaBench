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
struct net_device {int dummy; } ;
struct cp_private {int rx_buf_sz; TYPE_2__* rx_ring; struct sk_buff** rx_skb; TYPE_1__* pdev; struct net_device* dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {void* opts1; int /*<<< orphan*/  addr; scalar_t__ opts2; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int CP_RX_RING_SIZE ; 
 int DescOwn ; 
 int ENOMEM ; 
 int NET_IP_ALIGN ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int RingEnd ; 
 int /*<<< orphan*/  cp_clean_rings (struct cp_private*) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static int cp_refill_rx(struct cp_private *cp)
{
	struct net_device *dev = cp->dev;
	unsigned i;

	for (i = 0; i < CP_RX_RING_SIZE; i++) {
		struct sk_buff *skb;
		dma_addr_t mapping;

		skb = netdev_alloc_skb(dev, cp->rx_buf_sz + NET_IP_ALIGN);
		if (!skb)
			goto err_out;

		skb_reserve(skb, NET_IP_ALIGN);

		mapping = dma_map_single(&cp->pdev->dev, skb->data,
					 cp->rx_buf_sz, PCI_DMA_FROMDEVICE);
		cp->rx_skb[i] = skb;

		cp->rx_ring[i].opts2 = 0;
		cp->rx_ring[i].addr = cpu_to_le64(mapping);
		if (i == (CP_RX_RING_SIZE - 1))
			cp->rx_ring[i].opts1 =
				cpu_to_le32(DescOwn | RingEnd | cp->rx_buf_sz);
		else
			cp->rx_ring[i].opts1 =
				cpu_to_le32(DescOwn | cp->rx_buf_sz);
	}

	return 0;

err_out:
	cp_clean_rings(cp);
	return -ENOMEM;
}