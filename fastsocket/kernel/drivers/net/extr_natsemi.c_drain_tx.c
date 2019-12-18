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
struct TYPE_3__ {int /*<<< orphan*/  tx_dropped; } ;
struct netdev_private {TYPE_2__** tx_skbuff; TYPE_1__ stats; int /*<<< orphan*/ * tx_dma; int /*<<< orphan*/  pci_dev; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (TYPE_2__*) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drain_tx(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);
	int i;

	for (i = 0; i < TX_RING_SIZE; i++) {
		if (np->tx_skbuff[i]) {
			pci_unmap_single(np->pci_dev,
				np->tx_dma[i], np->tx_skbuff[i]->len,
				PCI_DMA_TODEVICE);
			dev_kfree_skb(np->tx_skbuff[i]);
			np->stats.tx_dropped++;
		}
		np->tx_skbuff[i] = NULL;
	}
}