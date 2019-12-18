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
struct pch_gbe_adapter {int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  wake_up_evt; struct pch_gbe_hw hw; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pch_gbe_free_rx_resources (struct pch_gbe_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_gbe_free_tx_resources (struct pch_gbe_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_gbe_hal_power_down_phy (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pch_gbe_hal_power_up_phy (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pch_gbe_reset (struct pch_gbe_adapter*) ; 
 int pch_gbe_setup_rx_resources (struct pch_gbe_adapter*,int /*<<< orphan*/ ) ; 
 int pch_gbe_setup_tx_resources (struct pch_gbe_adapter*,int /*<<< orphan*/ ) ; 
 int pch_gbe_up (struct pch_gbe_adapter*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int pch_gbe_open(struct net_device *netdev)
{
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);
	struct pch_gbe_hw *hw = &adapter->hw;
	int err;

	/* allocate transmit descriptors */
	err = pch_gbe_setup_tx_resources(adapter, adapter->tx_ring);
	if (err)
		goto err_setup_tx;
	/* allocate receive descriptors */
	err = pch_gbe_setup_rx_resources(adapter, adapter->rx_ring);
	if (err)
		goto err_setup_rx;
	pch_gbe_hal_power_up_phy(hw);
	err = pch_gbe_up(adapter);
	if (err)
		goto err_up;
	pr_debug("Success End\n");
	return 0;

err_up:
	if (!adapter->wake_up_evt)
		pch_gbe_hal_power_down_phy(hw);
	pch_gbe_free_rx_resources(adapter, adapter->rx_ring);
err_setup_rx:
	pch_gbe_free_tx_resources(adapter, adapter->tx_ring);
err_setup_tx:
	pch_gbe_reset(adapter);
	pr_err("Error End\n");
	return err;
}