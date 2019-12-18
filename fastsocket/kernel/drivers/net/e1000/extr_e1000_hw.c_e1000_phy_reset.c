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
typedef  int /*<<< orphan*/  u16 ;
struct e1000_hw {int phy_type; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  MII_CR_RESET ; 
 int /*<<< orphan*/  PHY_CTRL ; 
 int /*<<< orphan*/  e1000_phy_hw_reset (struct e1000_hw*) ; 
#define  e1000_phy_igp 128 
 int /*<<< orphan*/  e1000_phy_init_script (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

s32 e1000_phy_reset(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 phy_data;

	e_dbg("e1000_phy_reset");

	switch (hw->phy_type) {
	case e1000_phy_igp:
		ret_val = e1000_phy_hw_reset(hw);
		if (ret_val)
			return ret_val;
		break;
	default:
		ret_val = e1000_read_phy_reg(hw, PHY_CTRL, &phy_data);
		if (ret_val)
			return ret_val;

		phy_data |= MII_CR_RESET;
		ret_val = e1000_write_phy_reg(hw, PHY_CTRL, phy_data);
		if (ret_val)
			return ret_val;

		udelay(1);
		break;
	}

	if (hw->phy_type == e1000_phy_igp)
		e1000_phy_init_script(hw);

	return E1000_SUCCESS;
}