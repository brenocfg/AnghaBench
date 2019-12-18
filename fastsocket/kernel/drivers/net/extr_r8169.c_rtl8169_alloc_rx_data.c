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
typedef  void sk_buff ;
struct rtl8169_private {struct net_device* dev; TYPE_1__* pci_dev; } ;
struct TYPE_4__ {scalar_t__ parent; } ;
struct net_device {TYPE_2__ dev; } ;
struct device {int dummy; } ;
struct RxDesc {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dev_to_node (scalar_t__) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc_node (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netif_err (struct rtl8169_private*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 void* rtl8169_align (void*) ; 
 int /*<<< orphan*/  rtl8169_map_to_asic (struct RxDesc*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ rx_buf_sz ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *rtl8169_alloc_rx_data(struct rtl8169_private *tp,
					     struct RxDesc *desc)
{
	void *data;
	dma_addr_t mapping;
	struct device *d = &tp->pci_dev->dev;
	struct net_device *dev = tp->dev;
	int node = dev->dev.parent ? dev_to_node(dev->dev.parent) : -1;

	data = kmalloc_node(rx_buf_sz, GFP_KERNEL, node);
	if (!data)
		return NULL;

	if (rtl8169_align(data) != data) {
		kfree(data);
		data = kmalloc_node(rx_buf_sz + 15, GFP_KERNEL, node);
		if (!data)
			return NULL;
	}

	mapping = dma_map_single(d, rtl8169_align(data), rx_buf_sz,
				 DMA_FROM_DEVICE);
	if (unlikely(dma_mapping_error(d, mapping))) {
		if (net_ratelimit())
			netif_err(tp, drv, tp->dev, "Failed to map RX DMA!\n");
		goto err_out;
	}

	rtl8169_map_to_asic(desc, mapping, rx_buf_sz);
	return data;

err_out:
	kfree(data);
	return NULL;
}