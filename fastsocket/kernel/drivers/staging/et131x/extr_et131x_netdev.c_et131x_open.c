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
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct et131x_adapter {int /*<<< orphan*/  Flags; TYPE_1__* pdev; int /*<<< orphan*/  ErrorTimer; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  add_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  et131x_enable_interrupts (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_isr ; 
 int /*<<< orphan*/  et131x_rx_dma_enable (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_tx_dma_enable (struct et131x_adapter*) ; 
 int /*<<< orphan*/  fMP_ADAPTER_INTERRUPT_IN_USE ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

int et131x_open(struct net_device *netdev)
{
	int result = 0;
	struct et131x_adapter *adapter = netdev_priv(netdev);

	/* Start the timer to track NIC errors */
	add_timer(&adapter->ErrorTimer);

	/* Register our IRQ */
	result = request_irq(netdev->irq, et131x_isr, IRQF_SHARED,
					netdev->name, netdev);
	if (result) {
		dev_err(&adapter->pdev->dev, "c ould not register IRQ %d\n",
			netdev->irq);
		return result;
	}

	/* Enable the Tx and Rx DMA engines (if not already enabled) */
	et131x_rx_dma_enable(adapter);
	et131x_tx_dma_enable(adapter);

	/* Enable device interrupts */
	et131x_enable_interrupts(adapter);

	adapter->Flags |= fMP_ADAPTER_INTERRUPT_IN_USE;

	/* We're ready to move some data, so start the queue */
	netif_start_queue(netdev);
	return result;
}