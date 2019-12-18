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
struct skge_hw {scalar_t__ chip_id; int /*<<< orphan*/  intr_mask; struct pci_dev* pdev; TYPE_1__** dev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  B0_HWE_ISRC ; 
 int /*<<< orphan*/  B0_R1_CSR ; 
 int /*<<< orphan*/  B0_R2_CSR ; 
 int /*<<< orphan*/  B2_TST_CTRL1 ; 
 int /*<<< orphan*/  B3_RI_CTRL ; 
 scalar_t__ CHIP_ID_GENESIS ; 
 int /*<<< orphan*/  CSR_IRQ_CL_P ; 
 int /*<<< orphan*/  GMAC_TI_ST_CTRL ; 
 int /*<<< orphan*/  GMT_ST_CLR_IRQ ; 
 int /*<<< orphan*/  IS_HW_ERR ; 
 int IS_IRQ_MST_ERR ; 
 int IS_IRQ_STAT ; 
 int IS_IRQ_TIST_OV ; 
 int IS_M1_PAR_ERR ; 
 int IS_M2_PAR_ERR ; 
 int IS_NO_STAT_M1 ; 
 int IS_NO_STAT_M2 ; 
 int IS_NO_TIST_M1 ; 
 int IS_NO_TIST_M2 ; 
 int IS_R1_PAR_ERR ; 
 int IS_R2_PAR_ERR ; 
 int IS_RAM_RD_PAR ; 
 int IS_RAM_WR_PAR ; 
 int /*<<< orphan*/  MFF_CLR_INSTAT ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_PARITY ; 
 int PCI_COMMAND_SERR ; 
 int /*<<< orphan*/  PCI_STATUS ; 
 int PCI_STATUS_ERROR_BITS ; 
 int /*<<< orphan*/  RI_CLR_RD_PERR ; 
 int /*<<< orphan*/  RI_CLR_WR_PERR ; 
 int /*<<< orphan*/  RX_MFF_CTRL1 ; 
 int /*<<< orphan*/  RX_MFF_CTRL2 ; 
 int /*<<< orphan*/  TST_CFG_WRITE_OFF ; 
 int /*<<< orphan*/  TST_CFG_WRITE_ON ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skge_mac_parity (struct skge_hw*,int) ; 
 int skge_read32 (struct skge_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_write16 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_write32 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_write8 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skge_error_irq(struct skge_hw *hw)
{
	struct pci_dev *pdev = hw->pdev;
	u32 hwstatus = skge_read32(hw, B0_HWE_ISRC);

	if (hw->chip_id == CHIP_ID_GENESIS) {
		/* clear xmac errors */
		if (hwstatus & (IS_NO_STAT_M1|IS_NO_TIST_M1))
			skge_write16(hw, RX_MFF_CTRL1, MFF_CLR_INSTAT);
		if (hwstatus & (IS_NO_STAT_M2|IS_NO_TIST_M2))
			skge_write16(hw, RX_MFF_CTRL2, MFF_CLR_INSTAT);
	} else {
		/* Timestamp (unused) overflow */
		if (hwstatus & IS_IRQ_TIST_OV)
			skge_write8(hw, GMAC_TI_ST_CTRL, GMT_ST_CLR_IRQ);
	}

	if (hwstatus & IS_RAM_RD_PAR) {
		dev_err(&pdev->dev, "Ram read data parity error\n");
		skge_write16(hw, B3_RI_CTRL, RI_CLR_RD_PERR);
	}

	if (hwstatus & IS_RAM_WR_PAR) {
		dev_err(&pdev->dev, "Ram write data parity error\n");
		skge_write16(hw, B3_RI_CTRL, RI_CLR_WR_PERR);
	}

	if (hwstatus & IS_M1_PAR_ERR)
		skge_mac_parity(hw, 0);

	if (hwstatus & IS_M2_PAR_ERR)
		skge_mac_parity(hw, 1);

	if (hwstatus & IS_R1_PAR_ERR) {
		dev_err(&pdev->dev, "%s: receive queue parity error\n",
			hw->dev[0]->name);
		skge_write32(hw, B0_R1_CSR, CSR_IRQ_CL_P);
	}

	if (hwstatus & IS_R2_PAR_ERR) {
		dev_err(&pdev->dev, "%s: receive queue parity error\n",
			hw->dev[1]->name);
		skge_write32(hw, B0_R2_CSR, CSR_IRQ_CL_P);
	}

	if (hwstatus & (IS_IRQ_MST_ERR|IS_IRQ_STAT)) {
		u16 pci_status, pci_cmd;

		pci_read_config_word(pdev, PCI_COMMAND, &pci_cmd);
		pci_read_config_word(pdev, PCI_STATUS, &pci_status);

		dev_err(&pdev->dev, "PCI error cmd=%#x status=%#x\n",
			pci_cmd, pci_status);

		/* Write the error bits back to clear them. */
		pci_status &= PCI_STATUS_ERROR_BITS;
		skge_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
		pci_write_config_word(pdev, PCI_COMMAND,
				      pci_cmd | PCI_COMMAND_SERR | PCI_COMMAND_PARITY);
		pci_write_config_word(pdev, PCI_STATUS, pci_status);
		skge_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);

		/* if error still set then just ignore it */
		hwstatus = skge_read32(hw, B0_HWE_ISRC);
		if (hwstatus & IS_IRQ_STAT) {
			dev_warn(&hw->pdev->dev, "unable to clear error (so ignoring them)\n");
			hw->intr_mask &= ~IS_HW_ERR;
		}
	}
}