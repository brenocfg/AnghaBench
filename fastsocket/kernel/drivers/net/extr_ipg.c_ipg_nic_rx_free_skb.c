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
struct net_device {int dummy; } ;
struct ipg_rx {int /*<<< orphan*/  frag_info; } ;
struct ipg_nic_private {unsigned int rx_current; int /*<<< orphan*/ ** rx_buff; int /*<<< orphan*/  rx_buf_sz; int /*<<< orphan*/  pdev; struct ipg_rx* rxd; } ;

/* Variables and functions */
 unsigned int IPG_RFDLIST_LENGTH ; 
 int IPG_RFI_FRAGLEN ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (int /*<<< orphan*/ *) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct ipg_nic_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipg_nic_rx_free_skb(struct net_device *dev)
{
	struct ipg_nic_private *sp = netdev_priv(dev);
	unsigned int entry = sp->rx_current % IPG_RFDLIST_LENGTH;

	if (sp->rx_buff[entry]) {
		struct ipg_rx *rxfd = sp->rxd + entry;

		pci_unmap_single(sp->pdev,
			le64_to_cpu(rxfd->frag_info) & ~IPG_RFI_FRAGLEN,
			sp->rx_buf_sz, PCI_DMA_FROMDEVICE);
		dev_kfree_skb_irq(sp->rx_buff[entry]);
		sp->rx_buff[entry] = NULL;
	}
}