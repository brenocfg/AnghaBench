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
typedef  int /*<<< orphan*/  u32 ;
struct sky2_hw {scalar_t__ chip_id; int chip_rev; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2_TST_CTRL1 ; 
 scalar_t__ CHIP_ID_YUKON_FE ; 
 scalar_t__ CHIP_ID_YUKON_XL ; 
 int /*<<< orphan*/  GPC_RST_CLR ; 
 int /*<<< orphan*/  GPHY_CTRL ; 
 int /*<<< orphan*/  PCI_DEV_REG1 ; 
 int /*<<< orphan*/  PHY_CT_ANE ; 
 int /*<<< orphan*/  PHY_MARV_CTRL ; 
 int SKY2_HW_ADV_POWER_CTL ; 
 int /*<<< orphan*/  SK_REG (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TST_CFG_WRITE_OFF ; 
 int /*<<< orphan*/  TST_CFG_WRITE_ON ; 
 int /*<<< orphan*/ * coma_mode ; 
 int /*<<< orphan*/  gm_phy_write (struct sky2_hw*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * phy_power ; 
 int /*<<< orphan*/  sky2_pci_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_pci_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_phy_power_up(struct sky2_hw *hw, unsigned port)
{
	u32 reg1;

	sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
	reg1 = sky2_pci_read32(hw, PCI_DEV_REG1);
	reg1 &= ~phy_power[port];

	if (hw->chip_id == CHIP_ID_YUKON_XL && hw->chip_rev > 1)
		reg1 |= coma_mode[port];

	sky2_pci_write32(hw, PCI_DEV_REG1, reg1);
	sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);
	sky2_pci_read32(hw, PCI_DEV_REG1);

	if (hw->chip_id == CHIP_ID_YUKON_FE)
		gm_phy_write(hw, port, PHY_MARV_CTRL, PHY_CT_ANE);
	else if (hw->flags & SKY2_HW_ADV_POWER_CTL)
		sky2_write8(hw, SK_REG(port, GPHY_CTRL), GPC_RST_CLR);
}