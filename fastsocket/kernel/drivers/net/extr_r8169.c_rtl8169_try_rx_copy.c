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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct rtl8169_private {int /*<<< orphan*/  dev; TYPE_1__* pci_dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prefetch (void*) ; 
 void* rtl8169_align (void*) ; 

__attribute__((used)) static struct sk_buff *rtl8169_try_rx_copy(void *data,
					   struct rtl8169_private *tp,
					   int pkt_size,
					   dma_addr_t addr)
{
	struct sk_buff *skb;
	struct device *d = &tp->pci_dev->dev;

	data = rtl8169_align(data);
	dma_sync_single_for_cpu(d, addr, pkt_size, DMA_FROM_DEVICE);
	prefetch(data);
	skb = netdev_alloc_skb_ip_align(tp->dev, pkt_size);
	if (skb)
		memcpy(skb->data, data, pkt_size);
	dma_sync_single_for_device(d, addr, pkt_size, DMA_FROM_DEVICE);

	return skb;
}