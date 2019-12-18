#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fc_bsg_job {TYPE_3__* request; } ;
struct TYPE_4__ {int* vendor_cmd; } ;
struct TYPE_5__ {TYPE_1__ h_vendor; } ;
struct TYPE_6__ {TYPE_2__ rqst_data; } ;

/* Variables and functions */
 int ENOSYS ; 
#define  QL_VND_A84_MGMT_CMD 142 
#define  QL_VND_A84_RESET 141 
#define  QL_VND_A84_UPDATE_FW 140 
#define  QL_VND_DIAG_IO_CMD 139 
#define  QL_VND_FCP_PRIO_CFG_CMD 138 
#define  QL_VND_FX00_MGMT_CMD 137 
#define  QL_VND_IIDMA 136 
#define  QL_VND_LOOPBACK 135 
#define  QL_VND_READ_FLASH 134 
#define  QL_VND_READ_FRU_STATUS 133 
#define  QL_VND_READ_I2C 132 
#define  QL_VND_SET_FRU_VERSION 131 
#define  QL_VND_UPDATE_FLASH 130 
#define  QL_VND_WRITE_FRU_STATUS 129 
#define  QL_VND_WRITE_I2C 128 
 int qla24xx_iidma (struct fc_bsg_job*) ; 
 int qla24xx_proc_fcp_prio_cfg_cmd (struct fc_bsg_job*) ; 
 int qla24xx_process_bidir_cmd (struct fc_bsg_job*) ; 
 int qla2x00_process_loopback (struct fc_bsg_job*) ; 
 int qla2x00_read_fru_status (struct fc_bsg_job*) ; 
 int qla2x00_read_i2c (struct fc_bsg_job*) ; 
 int qla2x00_read_optrom (struct fc_bsg_job*) ; 
 int qla2x00_update_fru_versions (struct fc_bsg_job*) ; 
 int qla2x00_update_optrom (struct fc_bsg_job*) ; 
 int qla2x00_write_fru_status (struct fc_bsg_job*) ; 
 int qla2x00_write_i2c (struct fc_bsg_job*) ; 
 int qla84xx_mgmt_cmd (struct fc_bsg_job*) ; 
 int qla84xx_reset (struct fc_bsg_job*) ; 
 int qla84xx_updatefw (struct fc_bsg_job*) ; 
 int qlafx00_mgmt_cmd (struct fc_bsg_job*) ; 

__attribute__((used)) static int
qla2x00_process_vendor_specific(struct fc_bsg_job *bsg_job)
{
	switch (bsg_job->request->rqst_data.h_vendor.vendor_cmd[0]) {
	case QL_VND_LOOPBACK:
		return qla2x00_process_loopback(bsg_job);

	case QL_VND_A84_RESET:
		return qla84xx_reset(bsg_job);

	case QL_VND_A84_UPDATE_FW:
		return qla84xx_updatefw(bsg_job);

	case QL_VND_A84_MGMT_CMD:
		return qla84xx_mgmt_cmd(bsg_job);

	case QL_VND_IIDMA:
		return qla24xx_iidma(bsg_job);

	case QL_VND_FCP_PRIO_CFG_CMD:
		return qla24xx_proc_fcp_prio_cfg_cmd(bsg_job);

	case QL_VND_READ_FLASH:
		return qla2x00_read_optrom(bsg_job);

	case QL_VND_UPDATE_FLASH:
		return qla2x00_update_optrom(bsg_job);

	case QL_VND_SET_FRU_VERSION:
		return qla2x00_update_fru_versions(bsg_job);

	case QL_VND_READ_FRU_STATUS:
		return qla2x00_read_fru_status(bsg_job);

	case QL_VND_WRITE_FRU_STATUS:
		return qla2x00_write_fru_status(bsg_job);

	case QL_VND_WRITE_I2C:
		return qla2x00_write_i2c(bsg_job);

	case QL_VND_READ_I2C:
		return qla2x00_read_i2c(bsg_job);

	case QL_VND_DIAG_IO_CMD:
		return qla24xx_process_bidir_cmd(bsg_job);

	case QL_VND_FX00_MGMT_CMD:
		return qlafx00_mgmt_cmd(bsg_job);
	default:
		return -ENOSYS;
	}
}