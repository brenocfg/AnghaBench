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
typedef  int u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct e1000_hw {int dummy; } ;
struct e1000_adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/  vlgrp; struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_READ_REG_ARRAY (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VFTA ; 
 int /*<<< orphan*/  __E1000_DOWN ; 
 int /*<<< orphan*/  e1000_irq_disable (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_irq_enable (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_write_vfta (struct e1000_hw*,int,int) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_group_set_device (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void e1000_vlan_rx_kill_vid(struct net_device *netdev, u16 vid)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u32 vfta, index;

	if (!test_bit(__E1000_DOWN, &adapter->flags))
		e1000_irq_disable(adapter);
	vlan_group_set_device(adapter->vlgrp, vid, NULL);
	if (!test_bit(__E1000_DOWN, &adapter->flags))
		e1000_irq_enable(adapter);

	/* remove VID from filter table */
	index = (vid >> 5) & 0x7F;
	vfta = E1000_READ_REG_ARRAY(hw, VFTA, index);
	vfta &= ~(1 << (vid & 0x1F));
	e1000_write_vfta(hw, index, vfta);
}