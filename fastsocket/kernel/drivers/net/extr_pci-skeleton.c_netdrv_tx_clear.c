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
struct ring_info {scalar_t__ mapping; TYPE_2__* skb; } ;
struct netdrv_private {int /*<<< orphan*/  pci_dev; struct ring_info* tx_info; int /*<<< orphan*/  dirty_tx; int /*<<< orphan*/  cur_tx; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int NUM_TX_DESC ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (TYPE_2__*) ; 
 struct netdrv_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netdrv_tx_clear (struct net_device *dev)
{
	int i;
	struct netdrv_private *tp = netdev_priv(dev);

	atomic_set (&tp->cur_tx, 0);
	atomic_set (&tp->dirty_tx, 0);

	/* Dump the unsent Tx packets. */
	for (i = 0; i < NUM_TX_DESC; i++) {
		struct ring_info *rp = &tp->tx_info[i];
		if (rp->mapping != 0) {
			pci_unmap_single (tp->pci_dev, rp->mapping,
					  rp->skb->len, PCI_DMA_TODEVICE);
			rp->mapping = 0;
		}
		if (rp->skb) {
			dev_kfree_skb (rp->skb);
			rp->skb = NULL;
			dev->stats.tx_dropped++;
		}
	}
}