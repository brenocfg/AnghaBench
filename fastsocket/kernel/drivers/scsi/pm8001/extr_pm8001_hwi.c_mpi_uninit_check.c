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
struct pm8001_hba_info {int /*<<< orphan*/  general_stat_tbl_addr; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int GSM_SM_BASE ; 
 int /*<<< orphan*/  GST_GSTLEN_MPIS_OFFSET ; 
 int GST_MPI_STATE_MASK ; 
 int GST_MPI_STATE_UNINIT ; 
 int /*<<< orphan*/  MSGU_IBDB_SET ; 
 int /*<<< orphan*/  PCI_DEVICE_ID ; 
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int SPC_MSGU_CFG_TABLE_RESET ; 
 int /*<<< orphan*/  init_pci_device_addresses (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pm8001_bar4_shift (struct pm8001_hba_info*,int) ; 
 int pm8001_cr32 (struct pm8001_hba_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_cw32 (struct pm8001_hba_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int pm8001_mr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mpi_uninit_check(struct pm8001_hba_info *pm8001_ha)
{
	u32 max_wait_count;
	u32 value;
	u32 gst_len_mpistate;
	u16 deviceid;
	pci_read_config_word(pm8001_ha->pdev, PCI_DEVICE_ID, &deviceid);
	if (deviceid == 0x8081) {
		if (-1 == pm8001_bar4_shift(pm8001_ha, GSM_SM_BASE)) {
			PM8001_FAIL_DBG(pm8001_ha,
				pm8001_printk("Shift Bar4 to 0x%x failed\n",
					GSM_SM_BASE));
			return -1;
		}
	}
	init_pci_device_addresses(pm8001_ha);
	/* Write bit1=1 to Inbound DoorBell Register to tell the SPC FW the
	table is stop */
	pm8001_cw32(pm8001_ha, 0, MSGU_IBDB_SET, SPC_MSGU_CFG_TABLE_RESET);

	/* wait until Inbound DoorBell Clear Register toggled */
	max_wait_count = 1 * 1000 * 1000;/* 1 sec */
	do {
		udelay(1);
		value = pm8001_cr32(pm8001_ha, 0, MSGU_IBDB_SET);
		value &= SPC_MSGU_CFG_TABLE_RESET;
	} while ((value != 0) && (--max_wait_count));

	if (!max_wait_count) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("TIMEOUT:IBDB value/=0x%x\n", value));
		return -1;
	}

	/* check the MPI-State for termination in progress */
	/* wait until Inbound DoorBell Clear Register toggled */
	max_wait_count = 1 * 1000 * 1000;  /* 1 sec */
	do {
		udelay(1);
		gst_len_mpistate =
			pm8001_mr32(pm8001_ha->general_stat_tbl_addr,
			GST_GSTLEN_MPIS_OFFSET);
		if (GST_MPI_STATE_UNINIT ==
			(gst_len_mpistate & GST_MPI_STATE_MASK))
			break;
	} while (--max_wait_count);
	if (!max_wait_count) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk(" TIME OUT MPI State = 0x%x\n",
				gst_len_mpistate & GST_MPI_STATE_MASK));
		return -1;
	}
	return 0;
}