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
struct atl1e_hw {int phy_configured; int re_autoneg; struct atl1e_adapter* adapter; } ;
struct atl1e_adapter {struct pci_dev* pdev; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  AT_WRITE_REGW (struct atl1e_hw*,int /*<<< orphan*/ ,int) ; 
 int GPHY_CTRL_DEFAULT ; 
 int GPHY_CTRL_EXT_RESET ; 
 int /*<<< orphan*/  MII_DBG_ADDR ; 
 int /*<<< orphan*/  MII_DBG_DATA ; 
 int /*<<< orphan*/  MII_INT_CTRL ; 
 int /*<<< orphan*/  REG_GPHY_CTRL ; 
 int atl1e_phy_commit (struct atl1e_hw*) ; 
 int atl1e_phy_setup_autoneg_adv (struct atl1e_hw*) ; 
 int atl1e_restart_autoneg (struct atl1e_hw*) ; 
 int atl1e_write_phy_reg (struct atl1e_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

int atl1e_phy_init(struct atl1e_hw *hw)
{
	struct atl1e_adapter *adapter = hw->adapter;
	struct pci_dev *pdev = adapter->pdev;
	s32 ret_val;
	u16 phy_val;

	if (hw->phy_configured) {
		if (hw->re_autoneg) {
			hw->re_autoneg = false;
			return atl1e_restart_autoneg(hw);
		}
		return 0;
	}

	/* RESET GPHY Core */
	AT_WRITE_REGW(hw, REG_GPHY_CTRL, GPHY_CTRL_DEFAULT);
	msleep(2);
	AT_WRITE_REGW(hw, REG_GPHY_CTRL, GPHY_CTRL_DEFAULT |
		      GPHY_CTRL_EXT_RESET);
	msleep(2);

	/* patches */
	/* p1. eable hibernation mode */
	ret_val = atl1e_write_phy_reg(hw, MII_DBG_ADDR, 0xB);
	if (ret_val)
		return ret_val;
	ret_val = atl1e_write_phy_reg(hw, MII_DBG_DATA, 0xBC00);
	if (ret_val)
		return ret_val;
	/* p2. set Class A/B for all modes */
	ret_val = atl1e_write_phy_reg(hw, MII_DBG_ADDR, 0);
	if (ret_val)
		return ret_val;
	phy_val = 0x02ef;
	/* remove Class AB */
	/* phy_val = hw->emi_ca ? 0x02ef : 0x02df; */
	ret_val = atl1e_write_phy_reg(hw, MII_DBG_DATA, phy_val);
	if (ret_val)
		return ret_val;
	/* p3. 10B ??? */
	ret_val = atl1e_write_phy_reg(hw, MII_DBG_ADDR, 0x12);
	if (ret_val)
		return ret_val;
	ret_val = atl1e_write_phy_reg(hw, MII_DBG_DATA, 0x4C04);
	if (ret_val)
		return ret_val;
	/* p4. 1000T power */
	ret_val = atl1e_write_phy_reg(hw, MII_DBG_ADDR, 0x4);
	if (ret_val)
		return ret_val;
	ret_val = atl1e_write_phy_reg(hw, MII_DBG_DATA, 0x8BBB);
	if (ret_val)
		return ret_val;

	ret_val = atl1e_write_phy_reg(hw, MII_DBG_ADDR, 0x5);
	if (ret_val)
		return ret_val;
	ret_val = atl1e_write_phy_reg(hw, MII_DBG_DATA, 0x2C46);
	if (ret_val)
		return ret_val;

	msleep(1);

	/*Enable PHY LinkChange Interrupt */
	ret_val = atl1e_write_phy_reg(hw, MII_INT_CTRL, 0xC00);
	if (ret_val) {
		dev_err(&pdev->dev, "Error enable PHY linkChange Interrupt\n");
		return ret_val;
	}
	/* setup AutoNeg parameters */
	ret_val = atl1e_phy_setup_autoneg_adv(hw);
	if (ret_val) {
		dev_err(&pdev->dev, "Error Setting up Auto-Negotiation\n");
		return ret_val;
	}
	/* SW.Reset & En-Auto-Neg to restart Auto-Neg*/
	dev_dbg(&pdev->dev, "Restarting Auto-Neg");
	ret_val = atl1e_phy_commit(hw);
	if (ret_val) {
		dev_err(&pdev->dev, "Error Resetting the phy");
		return ret_val;
	}

	hw->phy_configured = true;

	return 0;
}