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
struct r6040_private {TYPE_1__* tx_insert_ptr; int /*<<< orphan*/  pdev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct TYPE_2__* vndescp; int /*<<< orphan*/ * skb_ptr; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_BUF_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TX_DCNT ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct r6040_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r6040_free_txbufs(struct net_device *dev)
{
	struct r6040_private *lp = netdev_priv(dev);
	int i;

	for (i = 0; i < TX_DCNT; i++) {
		if (lp->tx_insert_ptr->skb_ptr) {
			pci_unmap_single(lp->pdev,
				le32_to_cpu(lp->tx_insert_ptr->buf),
				MAX_BUF_SIZE, PCI_DMA_TODEVICE);
			dev_kfree_skb(lp->tx_insert_ptr->skb_ptr);
			lp->tx_insert_ptr->skb_ptr = NULL;
		}
		lp->tx_insert_ptr = lp->tx_insert_ptr->vndescp;
	}
}