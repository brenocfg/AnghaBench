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
typedef  int u16 ;
struct TYPE_2__ {int autoneg; } ;
struct e1000_hw {scalar_t__ device_id; TYPE_1__ mac; } ;
struct igb_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 scalar_t__ E1000_DEV_ID_DH89XXCC_BACKPLANE ; 
 scalar_t__ E1000_DEV_ID_DH89XXCC_SERDES ; 
 scalar_t__ E1000_DEV_ID_DH89XXCC_SFP ; 
 scalar_t__ E1000_DEV_ID_DH89XXCC_SGMII ; 
 int /*<<< orphan*/  E1000_MPHY_ADDR_CTL ; 
 int E1000_MPHY_ADDR_CTL_OFFSET_MASK ; 
 int /*<<< orphan*/  E1000_MPHY_DATA ; 
 int E1000_MPHY_PCS_CLK_REG_DIGINELBEN ; 
 int E1000_MPHY_PCS_CLK_REG_OFFSET ; 
 int /*<<< orphan*/  E1000_RCTL ; 
 int E1000_RCTL_LBM_MAC ; 
 int E1000_RCTL_LBM_TCVR ; 
 int MII_CR_LOOPBACK ; 
 int /*<<< orphan*/  PHY_CONTROL ; 
 int /*<<< orphan*/  igb_phy_sw_reset (struct e1000_hw*) ; 
 int /*<<< orphan*/  igb_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  igb_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void igb_loopback_cleanup(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 rctl;
	u16 phy_reg;

	if ((hw->device_id == E1000_DEV_ID_DH89XXCC_SGMII) ||
	(hw->device_id == E1000_DEV_ID_DH89XXCC_SERDES) ||
	(hw->device_id == E1000_DEV_ID_DH89XXCC_BACKPLANE) ||
	(hw->device_id == E1000_DEV_ID_DH89XXCC_SFP)) {
		u32 reg;

		/* Disable near end loopback on DH89xxCC */
		reg = rd32(E1000_MPHY_ADDR_CTL);
		reg = (reg & E1000_MPHY_ADDR_CTL_OFFSET_MASK) |
		E1000_MPHY_PCS_CLK_REG_OFFSET;
		wr32(E1000_MPHY_ADDR_CTL, reg);

		reg = rd32(E1000_MPHY_DATA);
		reg &= ~E1000_MPHY_PCS_CLK_REG_DIGINELBEN;
		wr32(E1000_MPHY_DATA, reg);
	}

	rctl = rd32(E1000_RCTL);
	rctl &= ~(E1000_RCTL_LBM_TCVR | E1000_RCTL_LBM_MAC);
	wr32(E1000_RCTL, rctl);

	hw->mac.autoneg = true;
	igb_read_phy_reg(hw, PHY_CONTROL, &phy_reg);
	if (phy_reg & MII_CR_LOOPBACK) {
		phy_reg &= ~MII_CR_LOOPBACK;
		igb_write_phy_reg(hw, PHY_CONTROL, phy_reg);
		igb_phy_sw_reset(hw);
	}
}