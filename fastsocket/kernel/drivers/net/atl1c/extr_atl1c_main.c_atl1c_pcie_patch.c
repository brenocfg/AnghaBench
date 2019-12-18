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
struct atl1c_hw {scalar_t__ nic_type; scalar_t__ revision_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_READ_REG (struct atl1c_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1c_hw*,int /*<<< orphan*/ ,int) ; 
 int DMA_DBG_VENDOR_MSG ; 
 int FIELD_SETX (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2CB1_PCIE_PHYMISC2_CDR_BW ; 
 int /*<<< orphan*/  L2CB1_PCIE_PHYMISC2_L0S_TH ; 
 scalar_t__ L2CB_V10 ; 
 int LINK_CTRL_EXT_SYNC ; 
 int MASTER_CTRL_CLK_SEL_DIS ; 
 int MASTER_CTRL_WAKEN_25M ; 
 int /*<<< orphan*/  PCIE_PHYMISC2_CDR_BW ; 
 int /*<<< orphan*/  PCIE_PHYMISC2_L0S_TH ; 
 int PCIE_PHYMISC_FORCE_RCV_DET ; 
 int PM_CTRL_L0S_BUFSRX_EN ; 
 int /*<<< orphan*/  REG_DMA_DBG ; 
 int /*<<< orphan*/  REG_LINK_CTRL ; 
 int /*<<< orphan*/  REG_MASTER_CTRL ; 
 int /*<<< orphan*/  REG_PCIE_PHYMISC ; 
 int /*<<< orphan*/  REG_PCIE_PHYMISC2 ; 
 int /*<<< orphan*/  REG_PM_CTRL ; 
 scalar_t__ athr_l1c ; 
 scalar_t__ athr_l1d ; 
 scalar_t__ athr_l2c ; 
 scalar_t__ athr_l2c_b ; 

__attribute__((used)) static void atl1c_pcie_patch(struct atl1c_hw *hw)
{
	u32 mst_data, data;

	/* pclk sel could switch to 25M */
	AT_READ_REG(hw, REG_MASTER_CTRL, &mst_data);
	mst_data &= ~MASTER_CTRL_CLK_SEL_DIS;
	AT_WRITE_REG(hw, REG_MASTER_CTRL, mst_data);

	/* WoL/PCIE related settings */
	if (hw->nic_type == athr_l1c || hw->nic_type == athr_l2c) {
		AT_READ_REG(hw, REG_PCIE_PHYMISC, &data);
		data |= PCIE_PHYMISC_FORCE_RCV_DET;
		AT_WRITE_REG(hw, REG_PCIE_PHYMISC, data);
	} else { /* new dev set bit5 of MASTER */
		if (!(mst_data & MASTER_CTRL_WAKEN_25M))
			AT_WRITE_REG(hw, REG_MASTER_CTRL,
				mst_data | MASTER_CTRL_WAKEN_25M);
	}
	/* aspm/PCIE setting only for l2cb 1.0 */
	if (hw->nic_type == athr_l2c_b && hw->revision_id == L2CB_V10) {
		AT_READ_REG(hw, REG_PCIE_PHYMISC2, &data);
		data = FIELD_SETX(data, PCIE_PHYMISC2_CDR_BW,
			L2CB1_PCIE_PHYMISC2_CDR_BW);
		data = FIELD_SETX(data, PCIE_PHYMISC2_L0S_TH,
			L2CB1_PCIE_PHYMISC2_L0S_TH);
		AT_WRITE_REG(hw, REG_PCIE_PHYMISC2, data);
		/* extend L1 sync timer */
		AT_READ_REG(hw, REG_LINK_CTRL, &data);
		data |= LINK_CTRL_EXT_SYNC;
		AT_WRITE_REG(hw, REG_LINK_CTRL, data);
	}
	/* l2cb 1.x & l1d 1.x */
	if (hw->nic_type == athr_l2c_b || hw->nic_type == athr_l1d) {
		AT_READ_REG(hw, REG_PM_CTRL, &data);
		data |= PM_CTRL_L0S_BUFSRX_EN;
		AT_WRITE_REG(hw, REG_PM_CTRL, data);
		/* clear vendor msg */
		AT_READ_REG(hw, REG_DMA_DBG, &data);
		AT_WRITE_REG(hw, REG_DMA_DBG, data & ~DMA_DBG_VENDOR_MSG);
	}
}