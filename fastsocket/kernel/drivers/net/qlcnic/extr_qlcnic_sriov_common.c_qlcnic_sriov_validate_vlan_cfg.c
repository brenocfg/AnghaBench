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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct qlcnic_sriov {scalar_t__ vlan; scalar_t__ vlan_mode; int num_allowed_vlans; scalar_t__* allowed_vlans; scalar_t__ any_vlan; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ QLC_GUEST_VLAN_MODE ; 

__attribute__((used)) static int qlcnic_sriov_validate_vlan_cfg(struct qlcnic_sriov *sriov,
					  u16 vid, u8 enable)
{
	u16 vlan = sriov->vlan;
	u8 allowed = 0;
	int i;

	if (sriov->vlan_mode != QLC_GUEST_VLAN_MODE)
		return -EINVAL;

	if (enable) {
		if (vlan)
			return -EINVAL;

		if (sriov->any_vlan) {
			for (i = 0; i < sriov->num_allowed_vlans; i++) {
				if (sriov->allowed_vlans[i] == vid)
					allowed = 1;
			}

			if (!allowed)
				return -EINVAL;
		}
	} else {
		if (!vlan || vlan != vid)
			return -EINVAL;
	}

	return 0;
}