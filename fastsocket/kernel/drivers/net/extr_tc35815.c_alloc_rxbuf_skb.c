#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  data; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  RX_BUF_SIZE ; 
 struct sk_buff* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ pci_dma_mapping_error (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *alloc_rxbuf_skb(struct net_device *dev,
				       struct pci_dev *hwdev,
				       dma_addr_t *dma_handle)
{
	struct sk_buff *skb;
	skb = dev_alloc_skb(RX_BUF_SIZE);
	if (!skb)
		return NULL;
	*dma_handle = pci_map_single(hwdev, skb->data, RX_BUF_SIZE,
				     PCI_DMA_FROMDEVICE);
	if (pci_dma_mapping_error(hwdev, *dma_handle)) {
		dev_kfree_skb_any(skb);
		return NULL;
	}
	skb_reserve(skb, 2);	/* make IP header 4byte aligned */
	return skb;
}