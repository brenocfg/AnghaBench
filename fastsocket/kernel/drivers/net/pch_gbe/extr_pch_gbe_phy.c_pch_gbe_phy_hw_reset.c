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
struct pch_gbe_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_1000T_CTRL ; 
 int /*<<< orphan*/  PHY_1000T_CTRL_DEFAULT ; 
 int /*<<< orphan*/  PHY_AUTONEG_ADV ; 
 int /*<<< orphan*/  PHY_AUTONEG_ADV_DEFAULT ; 
 int /*<<< orphan*/  PHY_CONTROL ; 
 int /*<<< orphan*/  PHY_CONTROL_DEFAULT ; 
 int /*<<< orphan*/  PHY_NEXT_PAGE_TX ; 
 int /*<<< orphan*/  PHY_NEXT_PAGE_TX_DEFAULT ; 
 int /*<<< orphan*/  PHY_PHYSP_CONTROL ; 
 int /*<<< orphan*/  PHY_PHYSP_CONTROL_DEFAULT ; 
 int /*<<< orphan*/  pch_gbe_phy_write_reg_miic (struct pch_gbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pch_gbe_phy_hw_reset(struct pch_gbe_hw *hw)
{
	pch_gbe_phy_write_reg_miic(hw, PHY_CONTROL, PHY_CONTROL_DEFAULT);
	pch_gbe_phy_write_reg_miic(hw, PHY_AUTONEG_ADV,
					PHY_AUTONEG_ADV_DEFAULT);
	pch_gbe_phy_write_reg_miic(hw, PHY_NEXT_PAGE_TX,
					PHY_NEXT_PAGE_TX_DEFAULT);
	pch_gbe_phy_write_reg_miic(hw, PHY_1000T_CTRL, PHY_1000T_CTRL_DEFAULT);
	pch_gbe_phy_write_reg_miic(hw, PHY_PHYSP_CONTROL,
					PHY_PHYSP_CONTROL_DEFAULT);
}