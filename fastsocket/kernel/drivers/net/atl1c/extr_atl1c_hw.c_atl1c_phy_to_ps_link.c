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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct atl1c_hw {int autoneg_advertised; int phy_configured; scalar_t__ adapter; } ;
struct atl1c_adapter {int link_speed; int link_duplex; struct pci_dev* pdev; } ;

/* Variables and functions */
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int AT_SUSPEND_LINK_TIMEOUT ; 
 int BMSR_LSTATUS ; 
 int FULL_DUPLEX ; 
 int HALF_DUPLEX ; 
 int LPA_100FULL ; 
 int LPA_100HALF ; 
 int LPA_10FULL ; 
 int LPA_10HALF ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_LPA ; 
 int SPEED_0 ; 
 int SPEED_10 ; 
 scalar_t__ atl1c_get_speed_and_duplex (struct atl1c_hw*,int*,int*) ; 
 int /*<<< orphan*/  atl1c_read_phy_reg (struct atl1c_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ atl1c_restart_autoneg (struct atl1c_hw*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 

int atl1c_phy_to_ps_link(struct atl1c_hw *hw)
{
	struct atl1c_adapter *adapter = (struct atl1c_adapter *)hw->adapter;
	struct pci_dev *pdev = adapter->pdev;
	int ret = 0;
	u16 autoneg_advertised = ADVERTISED_10baseT_Half;
	u16 save_autoneg_advertised;
	u16 phy_data;
	u16 mii_lpa_data;
	u16 speed = SPEED_0;
	u16 duplex = FULL_DUPLEX;
	int i;

	atl1c_read_phy_reg(hw, MII_BMSR, &phy_data);
	atl1c_read_phy_reg(hw, MII_BMSR, &phy_data);
	if (phy_data & BMSR_LSTATUS) {
		atl1c_read_phy_reg(hw, MII_LPA, &mii_lpa_data);
		if (mii_lpa_data & LPA_10FULL)
			autoneg_advertised = ADVERTISED_10baseT_Full;
		else if (mii_lpa_data & LPA_10HALF)
			autoneg_advertised = ADVERTISED_10baseT_Half;
		else if (mii_lpa_data & LPA_100HALF)
			autoneg_advertised = ADVERTISED_100baseT_Half;
		else if (mii_lpa_data & LPA_100FULL)
			autoneg_advertised = ADVERTISED_100baseT_Full;

		save_autoneg_advertised = hw->autoneg_advertised;
		hw->phy_configured = false;
		hw->autoneg_advertised = autoneg_advertised;
		if (atl1c_restart_autoneg(hw) != 0) {
			dev_dbg(&pdev->dev, "phy autoneg failed\n");
			ret = -1;
		}
		hw->autoneg_advertised = save_autoneg_advertised;

		if (mii_lpa_data) {
			for (i = 0; i < AT_SUSPEND_LINK_TIMEOUT; i++) {
				mdelay(100);
				atl1c_read_phy_reg(hw, MII_BMSR, &phy_data);
				atl1c_read_phy_reg(hw, MII_BMSR, &phy_data);
				if (phy_data & BMSR_LSTATUS) {
					if (atl1c_get_speed_and_duplex(hw, &speed,
									&duplex) != 0)
						dev_dbg(&pdev->dev,
							"get speed and duplex failed\n");
					break;
				}
			}
		}
	} else {
		speed = SPEED_10;
		duplex = HALF_DUPLEX;
	}
	adapter->link_speed = speed;
	adapter->link_duplex = duplex;

	return ret;
}