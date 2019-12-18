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
struct net_device {int /*<<< orphan*/  irq; } ;
struct et131x_adapter {int /*<<< orphan*/  ErrorTimer; int /*<<< orphan*/  Flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  et131x_disable_interrupts (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_rx_dma_disable (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_tx_dma_disable (struct et131x_adapter*) ; 
 int /*<<< orphan*/  fMP_ADAPTER_INTERRUPT_IN_USE ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

int et131x_close(struct net_device *netdev)
{
	struct et131x_adapter *adapter = netdev_priv(netdev);

	/* First thing is to stop the queue */
	netif_stop_queue(netdev);

	/* Stop the Tx and Rx DMA engines */
	et131x_rx_dma_disable(adapter);
	et131x_tx_dma_disable(adapter);

	/* Disable device interrupts */
	et131x_disable_interrupts(adapter);

	/* Deregistering ISR */
	adapter->Flags &= ~fMP_ADAPTER_INTERRUPT_IN_USE;
	free_irq(netdev->irq, netdev);

	/* Stop the error timer */
	del_timer_sync(&adapter->ErrorTimer);
	return 0;
}