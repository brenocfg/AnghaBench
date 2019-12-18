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
typedef  int u8 ;
struct pm8001_hba_info {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
#define  OPC_OUB_DEREG_DEV 160 
#define  OPC_OUB_DEVICE_HANDLE_REMOVAL 159 
#define  OPC_OUB_DEV_HANDLE_ARRIV 158 
#define  OPC_OUB_DEV_INFO 157 
#define  OPC_OUB_DEV_REGIST 156 
#define  OPC_OUB_ECHO 155 
#define  OPC_OUB_FW_FLASH_UPDATE 154 
#define  OPC_OUB_GENERAL_EVENT 153 
#define  OPC_OUB_GET_DEVICE_STATE 152 
#define  OPC_OUB_GET_DEV_HANDLE 151 
#define  OPC_OUB_GET_NVMD_DATA 150 
#define  OPC_OUB_GET_TIME_STAMP 149 
#define  OPC_OUB_GPIO_EVENT 148 
#define  OPC_OUB_GPIO_RESPONSE 147 
#define  OPC_OUB_HW_EVENT 146 
#define  OPC_OUB_LOCAL_PHY_CNTRL 145 
#define  OPC_OUB_PORT_CONTROL 144 
#define  OPC_OUB_SAS_DIAG_EXECUTE 143 
#define  OPC_OUB_SAS_DIAG_MODE_START_END 142 
#define  OPC_OUB_SAS_HW_EVENT_ACK 141 
#define  OPC_OUB_SAS_RE_INITIALIZE 140 
#define  OPC_OUB_SATA_ABORT_RSP 139 
#define  OPC_OUB_SATA_COMP 138 
#define  OPC_OUB_SATA_EVENT 137 
#define  OPC_OUB_SET_DEVICE_STATE 136 
#define  OPC_OUB_SET_DEV_INFO 135 
#define  OPC_OUB_SET_NVMD_DATA 134 
#define  OPC_OUB_SMP_ABORT_RSP 133 
#define  OPC_OUB_SMP_COMP 132 
#define  OPC_OUB_SSP_ABORT_RSP 131 
#define  OPC_OUB_SSP_COMP 130 
#define  OPC_OUB_SSP_EVENT 129 
#define  OPC_OUB_SSP_RECV_EVENT 128 
 int /*<<< orphan*/  PM8001_MSG_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpi_hw_event (struct pm8001_hba_info*,void*) ; 
 int /*<<< orphan*/  mpi_sata_completion (struct pm8001_hba_info*,void*) ; 
 int /*<<< orphan*/  mpi_sata_event (struct pm8001_hba_info*,void*) ; 
 int /*<<< orphan*/  mpi_smp_completion (struct pm8001_hba_info*,void*) ; 
 int /*<<< orphan*/  mpi_ssp_completion (struct pm8001_hba_info*,void*) ; 
 int /*<<< orphan*/  mpi_ssp_event (struct pm8001_hba_info*,void*) ; 
 int /*<<< orphan*/  pm8001_mpi_dereg_resp (struct pm8001_hba_info*,void*) ; 
 int /*<<< orphan*/  pm8001_mpi_fw_flash_update_resp (struct pm8001_hba_info*,void*) ; 
 int /*<<< orphan*/  pm8001_mpi_general_event (struct pm8001_hba_info*,void*) ; 
 int /*<<< orphan*/  pm8001_mpi_get_nvmd_resp (struct pm8001_hba_info*,void*) ; 
 int /*<<< orphan*/  pm8001_mpi_local_phy_ctl (struct pm8001_hba_info*,void*) ; 
 int /*<<< orphan*/  pm8001_mpi_reg_resp (struct pm8001_hba_info*,void*) ; 
 int /*<<< orphan*/  pm8001_mpi_set_dev_state_resp (struct pm8001_hba_info*,void*) ; 
 int /*<<< orphan*/  pm8001_mpi_set_nvmd_resp (struct pm8001_hba_info*,void*) ; 
 int /*<<< orphan*/  pm8001_mpi_task_abort_resp (struct pm8001_hba_info*,void*) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 

__attribute__((used)) static void process_one_iomb(struct pm8001_hba_info *pm8001_ha, void *piomb)
{
	__le32 pHeader = *(__le32 *)piomb;
	u8 opc = (u8)((le32_to_cpu(pHeader)) & 0xFFF);

	PM8001_MSG_DBG(pm8001_ha, pm8001_printk("process_one_iomb:"));

	switch (opc) {
	case OPC_OUB_ECHO:
		PM8001_MSG_DBG(pm8001_ha, pm8001_printk("OPC_OUB_ECHO\n"));
		break;
	case OPC_OUB_HW_EVENT:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_HW_EVENT\n"));
		mpi_hw_event(pm8001_ha, piomb);
		break;
	case OPC_OUB_SSP_COMP:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_SSP_COMP\n"));
		mpi_ssp_completion(pm8001_ha, piomb);
		break;
	case OPC_OUB_SMP_COMP:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_SMP_COMP\n"));
		mpi_smp_completion(pm8001_ha, piomb);
		break;
	case OPC_OUB_LOCAL_PHY_CNTRL:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_LOCAL_PHY_CNTRL\n"));
		pm8001_mpi_local_phy_ctl(pm8001_ha, piomb);
		break;
	case OPC_OUB_DEV_REGIST:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_DEV_REGIST\n"));
		pm8001_mpi_reg_resp(pm8001_ha, piomb);
		break;
	case OPC_OUB_DEREG_DEV:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("unregister the device\n"));
		pm8001_mpi_dereg_resp(pm8001_ha, piomb);
		break;
	case OPC_OUB_GET_DEV_HANDLE:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_GET_DEV_HANDLE\n"));
		break;
	case OPC_OUB_SATA_COMP:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_SATA_COMP\n"));
		mpi_sata_completion(pm8001_ha, piomb);
		break;
	case OPC_OUB_SATA_EVENT:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_SATA_EVENT\n"));
		mpi_sata_event(pm8001_ha, piomb);
		break;
	case OPC_OUB_SSP_EVENT:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_SSP_EVENT\n"));
		mpi_ssp_event(pm8001_ha, piomb);
		break;
	case OPC_OUB_DEV_HANDLE_ARRIV:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_DEV_HANDLE_ARRIV\n"));
		/*This is for target*/
		break;
	case OPC_OUB_SSP_RECV_EVENT:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_SSP_RECV_EVENT\n"));
		/*This is for target*/
		break;
	case OPC_OUB_DEV_INFO:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_DEV_INFO\n"));
		break;
	case OPC_OUB_FW_FLASH_UPDATE:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_FW_FLASH_UPDATE\n"));
		pm8001_mpi_fw_flash_update_resp(pm8001_ha, piomb);
		break;
	case OPC_OUB_GPIO_RESPONSE:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_GPIO_RESPONSE\n"));
		break;
	case OPC_OUB_GPIO_EVENT:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_GPIO_EVENT\n"));
		break;
	case OPC_OUB_GENERAL_EVENT:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_GENERAL_EVENT\n"));
		pm8001_mpi_general_event(pm8001_ha, piomb);
		break;
	case OPC_OUB_SSP_ABORT_RSP:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_SSP_ABORT_RSP\n"));
		pm8001_mpi_task_abort_resp(pm8001_ha, piomb);
		break;
	case OPC_OUB_SATA_ABORT_RSP:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_SATA_ABORT_RSP\n"));
		pm8001_mpi_task_abort_resp(pm8001_ha, piomb);
		break;
	case OPC_OUB_SAS_DIAG_MODE_START_END:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_SAS_DIAG_MODE_START_END\n"));
		break;
	case OPC_OUB_SAS_DIAG_EXECUTE:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_SAS_DIAG_EXECUTE\n"));
		break;
	case OPC_OUB_GET_TIME_STAMP:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_GET_TIME_STAMP\n"));
		break;
	case OPC_OUB_SAS_HW_EVENT_ACK:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_SAS_HW_EVENT_ACK\n"));
		break;
	case OPC_OUB_PORT_CONTROL:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_PORT_CONTROL\n"));
		break;
	case OPC_OUB_SMP_ABORT_RSP:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_SMP_ABORT_RSP\n"));
		pm8001_mpi_task_abort_resp(pm8001_ha, piomb);
		break;
	case OPC_OUB_GET_NVMD_DATA:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_GET_NVMD_DATA\n"));
		pm8001_mpi_get_nvmd_resp(pm8001_ha, piomb);
		break;
	case OPC_OUB_SET_NVMD_DATA:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_SET_NVMD_DATA\n"));
		pm8001_mpi_set_nvmd_resp(pm8001_ha, piomb);
		break;
	case OPC_OUB_DEVICE_HANDLE_REMOVAL:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_DEVICE_HANDLE_REMOVAL\n"));
		break;
	case OPC_OUB_SET_DEVICE_STATE:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_SET_DEVICE_STATE\n"));
		pm8001_mpi_set_dev_state_resp(pm8001_ha, piomb);
		break;
	case OPC_OUB_GET_DEVICE_STATE:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_GET_DEVICE_STATE\n"));
		break;
	case OPC_OUB_SET_DEV_INFO:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_SET_DEV_INFO\n"));
		break;
	case OPC_OUB_SAS_RE_INITIALIZE:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("OPC_OUB_SAS_RE_INITIALIZE\n"));
		break;
	default:
		PM8001_MSG_DBG(pm8001_ha,
			pm8001_printk("Unknown outbound Queue IOMB OPC = %x\n",
			opc));
		break;
	}
}