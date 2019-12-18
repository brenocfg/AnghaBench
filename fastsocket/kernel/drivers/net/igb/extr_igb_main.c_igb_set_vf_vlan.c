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
struct e1000_hw {int dummy; } ;
struct igb_adapter {int vfs_allocated_count; int /*<<< orphan*/  vlgrp; TYPE_1__* netdev; struct e1000_hw hw; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_VLVF (int) ; 
 int /*<<< orphan*/  E1000_VLVF_POOLSEL_SHIFT ; 
 int E1000_VLVF_VLANID_MASK ; 
 int E1000_VT_MSGINFO_MASK ; 
 int E1000_VT_MSGINFO_SHIFT ; 
 int IFF_PROMISC ; 
 int VLAN_VID_MASK ; 
 int igb_find_vlvf_entry (struct igb_adapter*,int) ; 
 int igb_vlvf_set (struct igb_adapter*,int,int,int) ; 
 int rd32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int igb_set_vf_vlan(struct igb_adapter *adapter, u32 *msgbuf, u32 vf)
{
	struct e1000_hw *hw = &adapter->hw;
	int add = (msgbuf[0] & E1000_VT_MSGINFO_MASK) >> E1000_VT_MSGINFO_SHIFT;
	int vid = (msgbuf[1] & E1000_VLVF_VLANID_MASK);
	int err = 0;

	/* If in promiscuous mode we need to make sure the PF also has
	 * the VLAN filter set.
	 */
	if (add && (adapter->netdev->flags & IFF_PROMISC))
		err = igb_vlvf_set(adapter, vid, add,
				   adapter->vfs_allocated_count);
	if (err)
		goto out;

	err = igb_vlvf_set(adapter, vid, add, vf);

	if (err)
		goto out;

	/* Go through all the checks to see if the VLAN filter should
	 * be wiped completely.
	 */
	if (!add && (adapter->netdev->flags & IFF_PROMISC)) {
		u32 vlvf, bits;

		int regndx = igb_find_vlvf_entry(adapter, vid);
		if (regndx < 0)
			goto out;
		/* See if any other pools are set for this VLAN filter
		 * entry other than the PF.
		 */
		vlvf = bits = rd32(E1000_VLVF(regndx));
		bits &= 1 << (E1000_VLVF_POOLSEL_SHIFT +
			      adapter->vfs_allocated_count);
		/* If the filter was removed then ensure PF pool bit
		 * is cleared if the PF only added itself to the pool
		 * because the PF is in promiscuous mode.
		 */
		if ((vlvf & VLAN_VID_MASK) == vid &&
		    !adapter->vlgrp &&
		    !bits)
			igb_vlvf_set(adapter, vid, add,
				     adapter->vfs_allocated_count);
	}

out:
	return err;
}