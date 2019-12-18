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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbevf_adapter {int flags; int num_tx_queues; int /*<<< orphan*/  pdev; TYPE_1__* tx_ring; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  state; struct ixgbe_hw hw; struct net_device* netdev; } ;
struct TYPE_2__ {int reg_idx; } ;

/* Variables and functions */
 int IXGBE_FLAG_IN_WATCHDOG_TASK ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int IXGBE_TXDCTL_ENABLE ; 
 int /*<<< orphan*/  IXGBE_VFTXDCTL (int) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __IXGBEVF_DOWN ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbevf_clean_all_rx_rings (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_clean_all_tx_rings (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_irq_disable (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_napi_disable_all (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_reset (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  pci_channel_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ixgbevf_down(struct ixgbevf_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct ixgbe_hw *hw = &adapter->hw;
	u32 txdctl;
	int i, j;

	/* signal that we are down to the interrupt handler */
	set_bit(__IXGBEVF_DOWN, &adapter->state);
	/* disable receives */

	netif_tx_disable(netdev);

	msleep(10);

	netif_tx_stop_all_queues(netdev);

	ixgbevf_irq_disable(adapter);

	ixgbevf_napi_disable_all(adapter);

	del_timer_sync(&adapter->watchdog_timer);
	/* can't call flush scheduled work here because it can deadlock
	 * if linkwatch_event tries to acquire the rtnl_lock which we are
	 * holding */
	while (adapter->flags & IXGBE_FLAG_IN_WATCHDOG_TASK)
		msleep(1);

	/* disable transmits in the hardware now that interrupts are off */
	for (i = 0; i < adapter->num_tx_queues; i++) {
		j = adapter->tx_ring[i].reg_idx;
		txdctl = IXGBE_READ_REG(hw, IXGBE_VFTXDCTL(j));
		IXGBE_WRITE_REG(hw, IXGBE_VFTXDCTL(j),
				(txdctl & ~IXGBE_TXDCTL_ENABLE));
	}

	netif_carrier_off(netdev);

	if (!pci_channel_offline(adapter->pdev))
		ixgbevf_reset(adapter);

	ixgbevf_clean_all_tx_rings(adapter);
	ixgbevf_clean_all_rx_rings(adapter);
}