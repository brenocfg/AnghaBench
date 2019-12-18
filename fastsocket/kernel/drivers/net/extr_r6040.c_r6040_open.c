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
struct r6040_private {scalar_t__ switch_sig; int /*<<< orphan*/  timer; int /*<<< orphan*/  napi; int /*<<< orphan*/  rx_ring_dma; void* rx_ring; int /*<<< orphan*/  pdev; int /*<<< orphan*/  tx_ring_dma; void* tx_ring; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ HZ ; 
 scalar_t__ ICPLUS_PHY_ID ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  RX_DESC_SIZE ; 
 int /*<<< orphan*/  TX_DESC_SIZE ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct r6040_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 void* pci_alloc_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r6040_interrupt ; 
 int /*<<< orphan*/  r6040_mac_address (struct net_device*) ; 
 int /*<<< orphan*/  r6040_timer ; 
 int r6040_up (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int r6040_open(struct net_device *dev)
{
	struct r6040_private *lp = netdev_priv(dev);
	int ret;

	/* Request IRQ and Register interrupt handler */
	ret = request_irq(dev->irq, &r6040_interrupt,
		IRQF_SHARED, dev->name, dev);
	if (ret)
		return ret;

	/* Set MAC address */
	r6040_mac_address(dev);

	/* Allocate Descriptor memory */
	lp->rx_ring =
		pci_alloc_consistent(lp->pdev, RX_DESC_SIZE, &lp->rx_ring_dma);
	if (!lp->rx_ring)
		return -ENOMEM;

	lp->tx_ring =
		pci_alloc_consistent(lp->pdev, TX_DESC_SIZE, &lp->tx_ring_dma);
	if (!lp->tx_ring) {
		pci_free_consistent(lp->pdev, RX_DESC_SIZE, lp->rx_ring,
				     lp->rx_ring_dma);
		return -ENOMEM;
	}

	ret = r6040_up(dev);
	if (ret) {
		pci_free_consistent(lp->pdev, TX_DESC_SIZE, lp->tx_ring,
							lp->tx_ring_dma);
		pci_free_consistent(lp->pdev, RX_DESC_SIZE, lp->rx_ring,
							lp->rx_ring_dma);
		return ret;
	}

	napi_enable(&lp->napi);
	netif_start_queue(dev);

	/* set and active a timer process */
	setup_timer(&lp->timer, r6040_timer, (unsigned long) dev);
	if (lp->switch_sig != ICPLUS_PHY_ID)
		mod_timer(&lp->timer, jiffies + HZ);
	return 0;
}