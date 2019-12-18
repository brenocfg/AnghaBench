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
typedef  scalar_t__ u16 ;
struct vlan_group {int dummy; } ;
struct net_device {int flags; } ;
struct e1000_hw {int dummy; } ;
struct e1000_adapter {scalar_t__ mng_vlan_id; int /*<<< orphan*/  flags; struct vlan_group* vlgrp; struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  E1000_CTRL_VME ; 
 scalar_t__ E1000_MNG_VLAN_NONE ; 
 int /*<<< orphan*/  E1000_RCTL_CFIEN ; 
 int /*<<< orphan*/  E1000_RCTL_VFE ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  __E1000_DOWN ; 
 int /*<<< orphan*/  e1000_irq_disable (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_irq_enable (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_update_mng_vlan (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_vlan_rx_kill_vid (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void e1000_vlan_rx_register(struct net_device *netdev,
				   struct vlan_group *grp)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u32 ctrl, rctl;

	if (!test_bit(__E1000_DOWN, &adapter->flags))
		e1000_irq_disable(adapter);
	adapter->vlgrp = grp;

	if (grp) {
		/* enable VLAN tag insert/strip */
		ctrl = er32(CTRL);
		ctrl |= E1000_CTRL_VME;
		ew32(CTRL, ctrl);

		/* enable VLAN receive filtering */
		rctl = er32(RCTL);
		rctl &= ~E1000_RCTL_CFIEN;
		if (!(netdev->flags & IFF_PROMISC))
			rctl |= E1000_RCTL_VFE;
		ew32(RCTL, rctl);
		e1000_update_mng_vlan(adapter);
	} else {
		/* disable VLAN tag insert/strip */
		ctrl = er32(CTRL);
		ctrl &= ~E1000_CTRL_VME;
		ew32(CTRL, ctrl);

		/* disable VLAN receive filtering */
		rctl = er32(RCTL);
		rctl &= ~E1000_RCTL_VFE;
		ew32(RCTL, rctl);

		if (adapter->mng_vlan_id != (u16)E1000_MNG_VLAN_NONE) {
			e1000_vlan_rx_kill_vid(netdev, adapter->mng_vlan_id);
			adapter->mng_vlan_id = E1000_MNG_VLAN_NONE;
		}
	}

	if (!test_bit(__E1000_DOWN, &adapter->flags))
		e1000_irq_enable(adapter);
}