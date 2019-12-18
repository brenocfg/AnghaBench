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
typedef  int uint32_t ;
struct scsi_qla_host {int func_num; TYPE_1__* isp_ops; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* idc_unlock ) (struct scsi_qla_host*) ;int /*<<< orphan*/  (* idc_lock ) (struct scsi_qla_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INIT_DONE ; 
 int /*<<< orphan*/  QLA8XXX_CRB_DRV_ACTIVE ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 scalar_t__ is_qla8022 (struct scsi_qla_host*) ; 
 scalar_t__ is_qla8032 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  ql4xdontresethba ; 
 int /*<<< orphan*/  qla4_82xx_set_idc_ver (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_83xx_clear_idc_dontreset (struct scsi_qla_host*) ; 
 int qla4_83xx_set_idc_ver (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_8xxx_clear_drv_active (struct scsi_qla_host*) ; 
 int qla4_8xxx_rd_direct (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla4_8xxx_set_drv_active (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub2 (struct scsi_qla_host*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int qla4_8xxx_update_idc_reg(struct scsi_qla_host *ha)
{
	uint32_t drv_active;
	int rval = QLA_SUCCESS;

	if (test_bit(AF_INIT_DONE, &ha->flags))
		goto exit_update_idc_reg;

	ha->isp_ops->idc_lock(ha);
	qla4_8xxx_set_drv_active(ha);

	/*
	 * If we are the first driver to load and
	 * ql4xdontresethba is not set, clear IDC_CTRL BIT0.
	 */
	if (is_qla8032(ha)) {
		drv_active = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DRV_ACTIVE);
		if ((drv_active == (1 << ha->func_num)) && !ql4xdontresethba)
			qla4_83xx_clear_idc_dontreset(ha);
	}

	if (is_qla8022(ha)) {
		qla4_82xx_set_idc_ver(ha);
	} else if (is_qla8032(ha)) {
		rval = qla4_83xx_set_idc_ver(ha);
		if (rval == QLA_ERROR)
			qla4_8xxx_clear_drv_active(ha);
	}

	ha->isp_ops->idc_unlock(ha);

exit_update_idc_reg:
	return rval;
}