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
struct atl1c_hw {int dummy; } ;

/* Variables and functions */
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_RESET ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int atl1c_phy_setup_adv (struct atl1c_hw*) ; 
 int atl1c_write_phy_reg (struct atl1c_hw*,int /*<<< orphan*/ ,int) ; 

int atl1c_restart_autoneg(struct atl1c_hw *hw)
{
	int err = 0;
	u16 mii_bmcr_data = BMCR_RESET;

	err = atl1c_phy_setup_adv(hw);
	if (err)
		return err;
	mii_bmcr_data |= BMCR_ANENABLE | BMCR_ANRESTART;

	return atl1c_write_phy_reg(hw, MII_BMCR, mii_bmcr_data);
}