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
struct pm8001_hba_info {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MSGU_SCRATCH_PAD_1 ; 
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM8001_INIT_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM8001_MSG_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int SCRATCH_PAD1_BOOTSTATE_CRIT_ERROR ; 
 int SCRATCH_PAD1_BOOTSTATE_HDA_BOOTSTRAP ; 
 int SCRATCH_PAD1_BOOTSTATE_HDA_SEEPROM ; 
 int SCRATCH_PAD1_BOOTSTATE_HDA_SOFTRESET ; 
 int SCRATCH_PAD1_BOOTSTATE_MASK ; 
 int /*<<< orphan*/  SPC_REG_SOFT_RESET ; 
 int /*<<< orphan*/  SPCv_NORMAL_RESET_VALUE ; 
 int SPCv_SOFT_RESET_NORMAL_RESET_OCCURED ; 
 int SPCv_SOFT_RESET_READ_MASK ; 
 int check_fw_ready (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 scalar_t__ mpi_uninit_check (struct pm8001_hba_info*) ; 
 int pm8001_cr32 (struct pm8001_hba_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_cw32 (struct pm8001_hba_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 

__attribute__((used)) static int
pm80xx_chip_soft_rst(struct pm8001_hba_info *pm8001_ha)
{
	u32 regval;
	u32 bootloader_state;

	/* Check if MPI is in ready state to reset */
	if (mpi_uninit_check(pm8001_ha) != 0) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("MPI state is not ready\n"));
		return -1;
	}

	/* checked for reset register normal state; 0x0 */
	regval = pm8001_cr32(pm8001_ha, 0, SPC_REG_SOFT_RESET);
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("reset register before write : 0x%x\n", regval));

	pm8001_cw32(pm8001_ha, 0, SPC_REG_SOFT_RESET, SPCv_NORMAL_RESET_VALUE);
	mdelay(500);

	regval = pm8001_cr32(pm8001_ha, 0, SPC_REG_SOFT_RESET);
	PM8001_INIT_DBG(pm8001_ha,
	pm8001_printk("reset register after write 0x%x\n", regval));

	if ((regval & SPCv_SOFT_RESET_READ_MASK) ==
			SPCv_SOFT_RESET_NORMAL_RESET_OCCURED) {
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk(" soft reset successful [regval: 0x%x]\n",
					regval));
	} else {
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk(" soft reset failed [regval: 0x%x]\n",
					regval));

		/* check bootloader is successfully executed or in HDA mode */
		bootloader_state =
			pm8001_cr32(pm8001_ha, 0, MSGU_SCRATCH_PAD_1) &
			SCRATCH_PAD1_BOOTSTATE_MASK;

		if (bootloader_state == SCRATCH_PAD1_BOOTSTATE_HDA_SEEPROM) {
			PM8001_MSG_DBG(pm8001_ha, pm8001_printk(
				"Bootloader state - HDA mode SEEPROM\n"));
		} else if (bootloader_state ==
				SCRATCH_PAD1_BOOTSTATE_HDA_BOOTSTRAP) {
			PM8001_MSG_DBG(pm8001_ha, pm8001_printk(
				"Bootloader state - HDA mode Bootstrap Pin\n"));
		} else if (bootloader_state ==
				SCRATCH_PAD1_BOOTSTATE_HDA_SOFTRESET) {
			PM8001_MSG_DBG(pm8001_ha, pm8001_printk(
				"Bootloader state - HDA mode soft reset\n"));
		} else if (bootloader_state ==
					SCRATCH_PAD1_BOOTSTATE_CRIT_ERROR) {
			PM8001_MSG_DBG(pm8001_ha, pm8001_printk(
				"Bootloader state-HDA mode critical error\n"));
		}
		return -EBUSY;
	}

	/* check the firmware status after reset */
	if (-1 == check_fw_ready(pm8001_ha)) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("Firmware is not ready!\n"));
		return -EBUSY;
	}
	PM8001_INIT_DBG(pm8001_ha,
		pm8001_printk("SPCv soft reset Complete\n"));
	return 0;
}