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
struct atl1e_hw {int mii_autoneg_adv_reg; scalar_t__ nic_type; int mii_1000t_ctrl_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_AT001_CR ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int MII_CR_AUTO_NEG_EN ; 
 int MII_CR_RESET ; 
 int MII_CR_RESTART_AUTO_NEG ; 
 scalar_t__ athr_l1e ; 
 scalar_t__ athr_l2e_revA ; 
 int atl1e_write_phy_reg (struct atl1e_hw*,int /*<<< orphan*/ ,int) ; 

int atl1e_restart_autoneg(struct atl1e_hw *hw)
{
	int err = 0;

	err = atl1e_write_phy_reg(hw, MII_ADVERTISE, hw->mii_autoneg_adv_reg);
	if (err)
		return err;

	if (hw->nic_type == athr_l1e || hw->nic_type == athr_l2e_revA) {
		err = atl1e_write_phy_reg(hw, MII_AT001_CR,
				       hw->mii_1000t_ctrl_reg);
		if (err)
			return err;
	}

	err = atl1e_write_phy_reg(hw, MII_BMCR,
			MII_CR_RESET | MII_CR_AUTO_NEG_EN |
			MII_CR_RESTART_AUTO_NEG);
	return err;
}