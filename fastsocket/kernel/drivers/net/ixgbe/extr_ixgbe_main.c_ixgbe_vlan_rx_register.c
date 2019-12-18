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
struct vlan_group {int dummy; } ;
struct net_device {int dummy; } ;
struct ixgbe_adapter {int /*<<< orphan*/  state; struct vlan_group* vlgrp; } ;

/* Variables and functions */
 int /*<<< orphan*/  __IXGBE_DOWN ; 
 int /*<<< orphan*/  ixgbe_irq_disable (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_irq_enable (struct ixgbe_adapter*,int,int) ; 
 int /*<<< orphan*/  ixgbe_vlan_filter_enable (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_vlan_rx_add_vid (struct net_device*,int /*<<< orphan*/ ) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ixgbe_vlan_rx_register(struct net_device *netdev,
				   struct vlan_group *grp)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);

	if (!test_bit(__IXGBE_DOWN, &adapter->state))
		ixgbe_irq_disable(adapter);
	adapter->vlgrp = grp;

	/*
	 * For a DCB driver, always enable VLAN tag stripping so we can
	 * still receive traffic from a DCB-enabled host even if we're
	 * not in DCB mode.
	 */
	ixgbe_vlan_filter_enable(adapter);

	ixgbe_vlan_rx_add_vid(netdev, 0);

	if (!test_bit(__IXGBE_DOWN, &adapter->state))
		ixgbe_irq_enable(adapter, true, true);
}