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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ data; } ;
struct idt77252_dev {int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDT77252_PRV_PADDR (struct sk_buff*) ; 
 int /*<<< orphan*/  IDT77252_PRV_POOL (struct sk_buff*) ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  POOL_QUEUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int push_rx_skb (struct idt77252_dev*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_pool_remove (struct idt77252_dev*,struct sk_buff*) ; 
 scalar_t__ skb_end_pointer (struct sk_buff*) ; 

__attribute__((used)) static void
recycle_rx_skb(struct idt77252_dev *card, struct sk_buff *skb)
{
	u32 handle = IDT77252_PRV_POOL(skb);
	int err;

	pci_dma_sync_single_for_device(card->pcidev, IDT77252_PRV_PADDR(skb),
				       skb_end_pointer(skb) - skb->data,
				       PCI_DMA_FROMDEVICE);

	err = push_rx_skb(card, skb, POOL_QUEUE(handle));
	if (err) {
		pci_unmap_single(card->pcidev, IDT77252_PRV_PADDR(skb),
				 skb_end_pointer(skb) - skb->data,
				 PCI_DMA_FROMDEVICE);
		sb_pool_remove(card, skb);
		dev_kfree_skb(skb);
	}
}