#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_vlan_anti_spoofing ) (struct ixgbe_hw*,int,size_t) ;int /*<<< orphan*/  (* set_mac_anti_spoofing ) (struct ixgbe_hw*,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_2__ ops; } ;
struct ixgbe_hw {TYPE_3__ mac; } ;
struct ixgbe_adapter {int antispoofing_enabled; int /*<<< orphan*/  num_vfs; struct ixgbe_hw hw; TYPE_1__* vfinfo; } ;
struct TYPE_4__ {scalar_t__ pf_set_mac; } ;

/* Variables and functions */
 int ENOSPC ; 
 size_t IXGBE_VT_MSGINFO_MASK ; 
 size_t IXGBE_VT_MSGINFO_SHIFT ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_warn (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int ixgbe_set_vf_macvlan (struct ixgbe_adapter*,size_t,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int,size_t) ; 

__attribute__((used)) static int ixgbe_set_vf_macvlan_msg(struct ixgbe_adapter *adapter,
				    u32 *msgbuf, u32 vf)
{
	u8 *new_mac = ((u8 *)(&msgbuf[1]));
	int index = (msgbuf[0] & IXGBE_VT_MSGINFO_MASK) >>
		    IXGBE_VT_MSGINFO_SHIFT;
	int err;

	if (adapter->vfinfo[vf].pf_set_mac && index > 0) {
		e_warn(drv,
		       "VF %d requested MACVLAN filter but is administratively denied\n",
		       vf);
		return -1;
	}

	/* An non-zero index indicates the VF is setting a filter */
	if (index) {
		if (!is_valid_ether_addr(new_mac)) {
			e_warn(drv, "VF %d attempted to set invalid mac\n", vf);
			return -1;
		}

		/*
		 * If the VF is allowed to set MAC filters then turn off
		 * anti-spoofing to avoid false positives.  An index
		 * greater than 0 will indicate the VF is setting a
		 * macvlan MAC filter.
		 */
		if (index > 0 && adapter->antispoofing_enabled) {
			struct ixgbe_hw *hw = &adapter->hw;
			hw->mac.ops.set_mac_anti_spoofing(hw, false,
							  adapter->num_vfs);
			hw->mac.ops.set_vlan_anti_spoofing(hw, false, vf);
			adapter->antispoofing_enabled = false;
		}
	}

	err = ixgbe_set_vf_macvlan(adapter, vf, index, new_mac);
	if (err == -ENOSPC)
		e_warn(drv,
		       "VF %d has requested a MACVLAN filter but there is no space for it\n",
		       vf);

	return err < 0;
}