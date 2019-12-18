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
typedef  int u16 ;
struct TYPE_2__ {int (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int*) ;} ;
struct e1000_phy_info {int min_cable_length; int max_cable_length; int cable_length; TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  int s32 ;

/* Variables and functions */
 int E1000_ERR_PHY ; 
 int M88E1000_CABLE_LENGTH_TABLE_SIZE ; 
 int /*<<< orphan*/  M88E1000_PHY_SPEC_STATUS ; 
 int M88E1000_PSSR_CABLE_LENGTH ; 
 int M88E1000_PSSR_CABLE_LENGTH_SHIFT ; 
 void** e1000_m88_cable_length_table ; 
 int stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 

s32 igb_get_cable_length_m88(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data, index;

	ret_val = phy->ops.read_reg(hw, M88E1000_PHY_SPEC_STATUS, &phy_data);
	if (ret_val)
		goto out;

	index = (phy_data & M88E1000_PSSR_CABLE_LENGTH) >>
		M88E1000_PSSR_CABLE_LENGTH_SHIFT;
	if (index >= M88E1000_CABLE_LENGTH_TABLE_SIZE - 1) {
		ret_val = -E1000_ERR_PHY;
		goto out;
	}

	phy->min_cable_length = e1000_m88_cable_length_table[index];
	phy->max_cable_length = e1000_m88_cable_length_table[index + 1];

	phy->cable_length = (phy->min_cable_length + phy->max_cable_length) / 2;

out:
	return ret_val;
}