#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct ixgbe_hw {int dummy; } ;
struct ixgbe_adapter {int /*<<< orphan*/  vlgrp; TYPE_2__* netdev; TYPE_1__* vfinfo; struct ixgbe_hw hw; } ;
typedef  int s32 ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {scalar_t__ pf_vlan; } ;

/* Variables and functions */
 int IFF_PROMISC ; 
 size_t IXGBE_READ_REG (struct ixgbe_hw*,scalar_t__) ; 
 scalar_t__ IXGBE_VLVF (int) ; 
 scalar_t__ IXGBE_VLVFB (int) ; 
 size_t IXGBE_VLVF_VLANID_MASK ; 
 size_t IXGBE_VT_MSGINFO_MASK ; 
 size_t IXGBE_VT_MSGINFO_SHIFT ; 
 size_t VLAN_VID_MASK ; 
 int VMDQ_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_warn (int /*<<< orphan*/ ,char*,size_t) ; 
 int ixgbe_find_vlvf_entry (struct ixgbe_hw*,int) ; 
 int ixgbe_set_vf_vlan (struct ixgbe_adapter*,int,int,int) ; 
 scalar_t__ netdev_get_num_tc (TYPE_2__*) ; 

__attribute__((used)) static int ixgbe_set_vf_vlan_msg(struct ixgbe_adapter *adapter,
				 u32 *msgbuf, u32 vf)
{
	struct ixgbe_hw *hw = &adapter->hw;
	int add = (msgbuf[0] & IXGBE_VT_MSGINFO_MASK) >> IXGBE_VT_MSGINFO_SHIFT;
	int vid = (msgbuf[1] & IXGBE_VLVF_VLANID_MASK);
	int err;
	s32 reg_ndx;
	u32 vlvf;
	u32 bits;
	u8 tcs = netdev_get_num_tc(adapter->netdev);

	if (adapter->vfinfo[vf].pf_vlan || tcs) {
		e_warn(drv,
		       "VF %d attempted to override administratively set VLAN configuration\n"
		       "Reload the VF driver to resume operations\n",
		       vf);
		return -1;
	}

	/* in case of promiscuous mode any VLAN filter set for a VF must
	 * also have the PF pool added to it.
	 */
	if (add && adapter->netdev->flags & IFF_PROMISC)
		err = ixgbe_set_vf_vlan(adapter, add, vid, VMDQ_P(0));

	err = ixgbe_set_vf_vlan(adapter, add, vid, vf);

	/* Go through all the checks to see if the VLAN filter should
	 * be wiped completely.
	 */
	if (!add && adapter->netdev->flags & IFF_PROMISC) {
		reg_ndx = ixgbe_find_vlvf_entry(hw, vid);
		if (reg_ndx < 0)
			goto out;
		vlvf = IXGBE_READ_REG(hw, IXGBE_VLVF(reg_ndx));
		/* See if any other pools are set for this VLAN filter
		 * entry other than the PF.
		 */
		if (VMDQ_P(0) < 32) {
			bits = IXGBE_READ_REG(hw, IXGBE_VLVFB(reg_ndx * 2));
			bits &= ~(1 << VMDQ_P(0));
			bits |= IXGBE_READ_REG(hw,
					       IXGBE_VLVFB(reg_ndx * 2) + 1);
		} else {
			bits = IXGBE_READ_REG(hw,
					      IXGBE_VLVFB(reg_ndx * 2) + 1);
			bits &= ~(1 << (VMDQ_P(0) - 32));
			bits |= IXGBE_READ_REG(hw, IXGBE_VLVFB(reg_ndx * 2));
		}

		/* If the filter was removed then ensure PF pool bit
		 * is cleared if the PF only added itself to the pool
		 * because the PF is in promiscuous mode.
		 */
		if ((vlvf & VLAN_VID_MASK) == vid &&
		    !adapter->vlgrp && !bits)
			ixgbe_set_vf_vlan(adapter, add, vid, VMDQ_P(0));
	}

out:

	return err;
}