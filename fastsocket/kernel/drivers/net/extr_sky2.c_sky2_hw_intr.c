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
typedef  int u32 ;
typedef  int u16 ;
struct sky2_hw {struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ B0_HWE_IMSK ; 
 scalar_t__ B0_HWE_ISRC ; 
 int /*<<< orphan*/  B2_TST_CTRL1 ; 
 int /*<<< orphan*/  GMAC_TI_ST_CTRL ; 
 int /*<<< orphan*/  GMT_ST_CLR_IRQ ; 
 scalar_t__ PCI_ERR_UNCOR_STATUS ; 
 int /*<<< orphan*/  PCI_STATUS ; 
 int PCI_STATUS_ERROR_BITS ; 
 int /*<<< orphan*/  TST_CFG_WRITE_OFF ; 
 int /*<<< orphan*/  TST_CFG_WRITE_ON ; 
 scalar_t__ Y2_CFG_AER ; 
 int Y2_HWE_L1_MASK ; 
 int Y2_IS_IRQ_STAT ; 
 int Y2_IS_MST_ERR ; 
 int Y2_IS_PCI_EXP ; 
 int Y2_IS_TIST_OV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  sky2_hw_error (struct sky2_hw*,int,int) ; 
 int sky2_pci_read16 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_pci_write16 (struct sky2_hw*,int /*<<< orphan*/ ,int) ; 
 int sky2_read32 (struct sky2_hw*,scalar_t__) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_hw_intr(struct sky2_hw *hw)
{
	struct pci_dev *pdev = hw->pdev;
	u32 status = sky2_read32(hw, B0_HWE_ISRC);
	u32 hwmsk = sky2_read32(hw, B0_HWE_IMSK);

	status &= hwmsk;

	if (status & Y2_IS_TIST_OV)
		sky2_write8(hw, GMAC_TI_ST_CTRL, GMT_ST_CLR_IRQ);

	if (status & (Y2_IS_MST_ERR | Y2_IS_IRQ_STAT)) {
		u16 pci_err;

		sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
		pci_err = sky2_pci_read16(hw, PCI_STATUS);
		if (net_ratelimit())
			dev_err(&pdev->dev, "PCI hardware error (0x%x)\n",
			        pci_err);

		sky2_pci_write16(hw, PCI_STATUS,
				      pci_err | PCI_STATUS_ERROR_BITS);
		sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);
	}

	if (status & Y2_IS_PCI_EXP) {
		/* PCI-Express uncorrectable Error occurred */
		u32 err;

		sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
		err = sky2_read32(hw, Y2_CFG_AER + PCI_ERR_UNCOR_STATUS);
		sky2_write32(hw, Y2_CFG_AER + PCI_ERR_UNCOR_STATUS,
			     0xfffffffful);
		if (net_ratelimit())
			dev_err(&pdev->dev, "PCI Express error (0x%x)\n", err);

		sky2_read32(hw, Y2_CFG_AER + PCI_ERR_UNCOR_STATUS);
		sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);
	}

	if (status & Y2_HWE_L1_MASK)
		sky2_hw_error(hw, 0, status);
	status >>= 8;
	if (status & Y2_HWE_L1_MASK)
		sky2_hw_error(hw, 1, status);
}