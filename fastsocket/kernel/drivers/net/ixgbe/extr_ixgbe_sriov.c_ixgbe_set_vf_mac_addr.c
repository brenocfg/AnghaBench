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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct ixgbe_adapter {TYPE_1__* vfinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  vf_mac_addresses; scalar_t__ pf_set_mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e_warn (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ ixgbe_set_vf_mac (struct ixgbe_adapter*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixgbe_set_vf_mac_addr(struct ixgbe_adapter *adapter,
				 u32 *msgbuf, u32 vf)
{
	u8 *new_mac = ((u8 *)(&msgbuf[1]));

	if (!is_valid_ether_addr(new_mac)) {
		e_warn(drv, "VF %d attempted to set invalid mac\n", vf);
		return -1;
	}

	if (adapter->vfinfo[vf].pf_set_mac &&
	    memcmp(adapter->vfinfo[vf].vf_mac_addresses, new_mac,
		   ETH_ALEN)) {
		e_warn(drv,
		       "VF %d attempted to override administratively set MAC address\n"
		       "Reload the VF driver to resume operations\n",
		       vf);
		return -1;
	}

	return ixgbe_set_vf_mac(adapter, vf, new_mac) < 0;
}