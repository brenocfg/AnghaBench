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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ vlan_id; int status; } ;
struct e1000_hw {TYPE_1__ mng_cookie; } ;
struct igb_adapter {scalar_t__ mng_vlan_id; int /*<<< orphan*/  vlgrp; struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_MNG_DHCP_COOKIE_STATUS_VLAN ; 
 scalar_t__ IGB_MNG_VLAN_NONE ; 
 int /*<<< orphan*/  igb_vfta_set (struct e1000_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  vlan_group_get_device (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void igb_update_mng_vlan(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u16 vid = adapter->hw.mng_cookie.vlan_id;
	u16 old_vid = adapter->mng_vlan_id;

	if (hw->mng_cookie.status & E1000_MNG_DHCP_COOKIE_STATUS_VLAN) {
		/* add VID to filter table */
		igb_vfta_set(hw, vid, true);
		adapter->mng_vlan_id = vid;
	} else {
		adapter->mng_vlan_id = IGB_MNG_VLAN_NONE;
	}

	if ((old_vid != (u16)IGB_MNG_VLAN_NONE) &&
	    (vid != old_vid) &&
	    !vlan_group_get_device(adapter->vlgrp, old_vid)) {
		/* remove VID from filter table */
		igb_vfta_set(hw, old_vid, false);
	}
}