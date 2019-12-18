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
struct pch_gbe_rx_ring {int /*<<< orphan*/ * rx_buff_pool; scalar_t__ rx_buff_pool_size; scalar_t__ rx_buff_pool_logic; } ;
struct pch_gbe_adapter {int /*<<< orphan*/  pdev; struct pch_gbe_rx_ring* rx_ring; int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  tx_queue_len; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  irq_sem; int /*<<< orphan*/  napi; struct net_device* netdev; } ;
struct net_device {int /*<<< orphan*/  tx_queue_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pch_gbe_clean_rx_ring (struct pch_gbe_adapter*,struct pch_gbe_rx_ring*) ; 
 int /*<<< orphan*/  pch_gbe_clean_tx_ring (struct pch_gbe_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_gbe_free_irq (struct pch_gbe_adapter*) ; 
 int /*<<< orphan*/  pch_gbe_irq_disable (struct pch_gbe_adapter*) ; 
 int /*<<< orphan*/  pch_gbe_reset (struct pch_gbe_adapter*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 

void pch_gbe_down(struct pch_gbe_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct pch_gbe_rx_ring *rx_ring = adapter->rx_ring;

	/* signal that we're down so the interrupt handler does not
	 * reschedule our watchdog timer */
	napi_disable(&adapter->napi);
	atomic_set(&adapter->irq_sem, 0);

	pch_gbe_irq_disable(adapter);
	pch_gbe_free_irq(adapter);

	del_timer_sync(&adapter->watchdog_timer);

	netdev->tx_queue_len = adapter->tx_queue_len;
	netif_carrier_off(netdev);
	netif_stop_queue(netdev);

	pch_gbe_reset(adapter);
	pch_gbe_clean_tx_ring(adapter, adapter->tx_ring);
	pch_gbe_clean_rx_ring(adapter, adapter->rx_ring);

	pci_free_consistent(adapter->pdev, rx_ring->rx_buff_pool_size,
			    rx_ring->rx_buff_pool, rx_ring->rx_buff_pool_logic);
	rx_ring->rx_buff_pool_logic = 0;
	rx_ring->rx_buff_pool_size = 0;
	rx_ring->rx_buff_pool = NULL;
}