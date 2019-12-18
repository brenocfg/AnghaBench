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
struct net_device {int dummy; } ;
struct ixgb_adapter {scalar_t__ link_duplex; scalar_t__ link_speed; int /*<<< orphan*/  watchdog_timer; TYPE_1__* pdev; scalar_t__ have_msi; int /*<<< orphan*/  napi; int /*<<< orphan*/  flags; struct net_device* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGB_DOWN ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  ixgb_clean_rx_ring (struct ixgb_adapter*) ; 
 int /*<<< orphan*/  ixgb_clean_tx_ring (struct ixgb_adapter*) ; 
 int /*<<< orphan*/  ixgb_irq_disable (struct ixgb_adapter*) ; 
 int /*<<< orphan*/  ixgb_reset (struct ixgb_adapter*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ixgb_down(struct ixgb_adapter *adapter, bool kill_watchdog)
{
	struct net_device *netdev = adapter->netdev;

	/* prevent the interrupt handler from restarting watchdog */
	set_bit(__IXGB_DOWN, &adapter->flags);

	napi_disable(&adapter->napi);
	/* waiting for NAPI to complete can re-enable interrupts */
	ixgb_irq_disable(adapter);
	free_irq(adapter->pdev->irq, netdev);

	if (adapter->have_msi)
		pci_disable_msi(adapter->pdev);

	if (kill_watchdog)
		del_timer_sync(&adapter->watchdog_timer);

	adapter->link_speed = 0;
	adapter->link_duplex = 0;
	netif_carrier_off(netdev);
	netif_stop_queue(netdev);

	ixgb_reset(adapter);
	ixgb_clean_tx_ring(adapter);
	ixgb_clean_rx_ring(adapter);
}