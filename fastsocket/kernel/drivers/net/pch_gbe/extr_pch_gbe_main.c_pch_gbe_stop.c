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
struct pch_gbe_hw {int dummy; } ;
struct pch_gbe_adapter {int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  wake_up_evt; struct pch_gbe_hw hw; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pch_gbe_down (struct pch_gbe_adapter*) ; 
 int /*<<< orphan*/  pch_gbe_free_rx_resources (struct pch_gbe_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_gbe_free_tx_resources (struct pch_gbe_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_gbe_hal_power_down_phy (struct pch_gbe_hw*) ; 

__attribute__((used)) static int pch_gbe_stop(struct net_device *netdev)
{
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);
	struct pch_gbe_hw *hw = &adapter->hw;

	pch_gbe_down(adapter);
	if (!adapter->wake_up_evt)
		pch_gbe_hal_power_down_phy(hw);
	pch_gbe_free_tx_resources(adapter, adapter->tx_ring);
	pch_gbe_free_rx_resources(adapter, adapter->rx_ring);
	return 0;
}