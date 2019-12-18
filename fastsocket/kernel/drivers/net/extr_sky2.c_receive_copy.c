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
struct sky2_port {TYPE_1__* hw; int /*<<< orphan*/  netdev; } ;
struct sk_buff {int /*<<< orphan*/  csum; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  data; } ;
struct rx_ring_info {TYPE_2__* skb; int /*<<< orphan*/  data_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  csum; } ;
struct TYPE_3__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 scalar_t__ likely (struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (TYPE_2__*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 

__attribute__((used)) static struct sk_buff *receive_copy(struct sky2_port *sky2,
				    const struct rx_ring_info *re,
				    unsigned length)
{
	struct sk_buff *skb;

	skb = netdev_alloc_skb(sky2->netdev, length + 2);
	if (likely(skb)) {
		skb_reserve(skb, 2);
		pci_dma_sync_single_for_cpu(sky2->hw->pdev, re->data_addr,
					    length, PCI_DMA_FROMDEVICE);
		skb_copy_from_linear_data(re->skb, skb->data, length);
		skb->ip_summed = re->skb->ip_summed;
		skb->csum = re->skb->csum;
		pci_dma_sync_single_for_device(sky2->hw->pdev, re->data_addr,
					       length, PCI_DMA_FROMDEVICE);
		re->skb->ip_summed = CHECKSUM_NONE;
		skb_put(skb, length);
	}
	return skb;
}