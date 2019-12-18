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
typedef  int /*<<< orphan*/  u32 ;
struct vlan_group {int dummy; } ;
struct net_device {int dummy; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {int /*<<< orphan*/  state; struct vlan_group* vlgrp; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL ; 
 int /*<<< orphan*/  E1000_CTRL_VME ; 
 int /*<<< orphan*/  E1000_RCTL ; 
 int /*<<< orphan*/  E1000_RCTL_CFIEN ; 
 int /*<<< orphan*/  __IGB_DOWN ; 
 int /*<<< orphan*/  igb_irq_disable (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_irq_enable (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_rlpml_set (struct igb_adapter*) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igb_vlan_rx_register(struct net_device *netdev,
				 struct vlan_group *grp)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u32 ctrl, rctl;

	igb_irq_disable(adapter);
	adapter->vlgrp = grp;

	if (grp) {
		/* enable VLAN tag insert/strip */
		ctrl = rd32(E1000_CTRL);
		ctrl |= E1000_CTRL_VME;
		wr32(E1000_CTRL, ctrl);

		/* Disable CFI check */
		rctl = rd32(E1000_RCTL);
		rctl &= ~E1000_RCTL_CFIEN;
		wr32(E1000_RCTL, rctl);
	} else {
		/* disable VLAN tag insert/strip */
		ctrl = rd32(E1000_CTRL);
		ctrl &= ~E1000_CTRL_VME;
		wr32(E1000_CTRL, ctrl);
	}

	igb_rlpml_set(adapter);

	if (!test_bit(__IGB_DOWN, &adapter->state))
		igb_irq_enable(adapter);
}