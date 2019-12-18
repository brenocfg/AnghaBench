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
struct sky2_hw {scalar_t__ chip_id; int chip_rev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_CTST ; 
 int /*<<< orphan*/  B0_POWER_CTRL ; 
 int /*<<< orphan*/  B2_Y2_CLK_GATE ; 
 scalar_t__ CHIP_ID_YUKON_XL ; 
 int /*<<< orphan*/  PCI_D3cold ; 
 int PC_VAUX_ENA ; 
 int PC_VAUX_ON ; 
 int PC_VCC_ENA ; 
 int PC_VCC_OFF ; 
 int Y2_CLK_GAT_LNK1_DIS ; 
 int Y2_CLK_GAT_LNK2_DIS ; 
 int Y2_COR_CLK_LNK1_DIS ; 
 int Y2_COR_CLK_LNK2_DIS ; 
 int /*<<< orphan*/  Y2_LED_STAT_OFF ; 
 int Y2_PCI_CLK_LNK1_DIS ; 
 int Y2_PCI_CLK_LNK2_DIS ; 
 int Y2_VAUX_AVAIL ; 
 scalar_t__ pci_pme_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write16 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sky2_power_aux(struct sky2_hw *hw)
{
	if (hw->chip_id == CHIP_ID_YUKON_XL && hw->chip_rev > 1)
		sky2_write8(hw, B2_Y2_CLK_GATE, 0);
	else
		/* enable bits are inverted */
		sky2_write8(hw, B2_Y2_CLK_GATE,
			    Y2_PCI_CLK_LNK1_DIS | Y2_COR_CLK_LNK1_DIS |
			    Y2_CLK_GAT_LNK1_DIS | Y2_PCI_CLK_LNK2_DIS |
			    Y2_COR_CLK_LNK2_DIS | Y2_CLK_GAT_LNK2_DIS);

	/* switch power to VAUX if supported and PME from D3cold */
	if ( (sky2_read32(hw, B0_CTST) & Y2_VAUX_AVAIL) &&
	     pci_pme_capable(hw->pdev, PCI_D3cold))
		sky2_write8(hw, B0_POWER_CTRL,
			    (PC_VAUX_ENA | PC_VCC_ENA |
			     PC_VAUX_ON | PC_VCC_OFF));

	/* turn off "driver loaded LED" */
	sky2_write16(hw, B0_CTST, Y2_LED_STAT_OFF);
}