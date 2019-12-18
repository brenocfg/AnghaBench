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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {int vfs_allocated_count; int /*<<< orphan*/  state; int /*<<< orphan*/  vlgrp; struct e1000_hw hw; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  __IGB_DOWN ; 
 int /*<<< orphan*/  igb_irq_disable (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_irq_enable (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_vfta_set (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ igb_vlvf_set (struct igb_adapter*,int /*<<< orphan*/ ,int,int) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_group_set_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igb_vlan_rx_kill_vid(struct net_device *netdev, u16 vid)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	int pf_id = adapter->vfs_allocated_count;
	s32 err;

	igb_irq_disable(adapter);
	vlan_group_set_device(adapter->vlgrp, vid, NULL);

	if (!test_bit(__IGB_DOWN, &adapter->state))
		igb_irq_enable(adapter);

	/* remove vlan from VLVF table array */
	err = igb_vlvf_set(adapter, vid, false, pf_id);

	/* if vid was not present in VLVF just remove it from table */
	if (err)
		igb_vfta_set(hw, vid, false);
}