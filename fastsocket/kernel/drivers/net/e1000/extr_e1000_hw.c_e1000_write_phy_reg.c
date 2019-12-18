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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {scalar_t__ phy_type; } ;
typedef  int s32 ;

/* Variables and functions */
 int IGP01E1000_PHY_PAGE_SELECT ; 
 int MAX_PHY_MULTI_PAGE_REG ; 
 int MAX_PHY_REG_ADDRESS ; 
 scalar_t__ e1000_phy_igp ; 
 int e1000_write_phy_reg_ex (struct e1000_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 

s32 e1000_write_phy_reg(struct e1000_hw *hw, u32 reg_addr, u16 phy_data)
{
	u32 ret_val;

	e_dbg("e1000_write_phy_reg");

	if ((hw->phy_type == e1000_phy_igp) &&
	    (reg_addr > MAX_PHY_MULTI_PAGE_REG)) {
		ret_val = e1000_write_phy_reg_ex(hw, IGP01E1000_PHY_PAGE_SELECT,
						 (u16) reg_addr);
		if (ret_val)
			return ret_val;
	}

	ret_val = e1000_write_phy_reg_ex(hw, MAX_PHY_REG_ADDRESS & reg_addr,
					 phy_data);

	return ret_val;
}