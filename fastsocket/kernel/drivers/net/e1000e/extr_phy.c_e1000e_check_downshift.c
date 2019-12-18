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
typedef  int u16 ;
struct e1000_phy_info {int type; int speed_downgraded; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int IGP01E1000_PHY_LINK_HEALTH ; 
 int IGP01E1000_PLHR_SS_DOWNGRADE ; 
 int M88E1000_PHY_SPEC_STATUS ; 
 int M88E1000_PSSR_DOWNSHIFT ; 
#define  e1000_phy_82578 133 
#define  e1000_phy_bm 132 
#define  e1000_phy_gg82563 131 
#define  e1000_phy_igp_2 130 
#define  e1000_phy_igp_3 129 
#define  e1000_phy_m88 128 
 int /*<<< orphan*/  e1e_rphy (struct e1000_hw*,int,int*) ; 

s32 e1000e_check_downshift(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data, offset, mask;

	switch (phy->type) {
	case e1000_phy_m88:
	case e1000_phy_gg82563:
	case e1000_phy_bm:
	case e1000_phy_82578:
		offset = M88E1000_PHY_SPEC_STATUS;
		mask = M88E1000_PSSR_DOWNSHIFT;
		break;
	case e1000_phy_igp_2:
	case e1000_phy_igp_3:
		offset = IGP01E1000_PHY_LINK_HEALTH;
		mask = IGP01E1000_PLHR_SS_DOWNGRADE;
		break;
	default:
		/* speed downshift not supported */
		phy->speed_downgraded = false;
		return 0;
	}

	ret_val = e1e_rphy(hw, offset, &phy_data);

	if (!ret_val)
		phy->speed_downgraded = !!(phy_data & mask);

	return ret_val;
}