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
typedef  scalar_t__ uint32_t ;
struct scsi_qla_host {TYPE_1__* isp_ops; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int (* need_reset ) (struct scsi_qla_host*) ;int (* restart_firmware ) (struct scsi_qla_host*) ;int /*<<< orphan*/  (* idc_lock ) (struct scsi_qla_host*) ;int /*<<< orphan*/  (* idc_unlock ) (struct scsi_qla_host*) ;int /*<<< orphan*/  (* rom_lock_recovery ) (struct scsi_qla_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AF_83XX_NO_FW_DUMP ; 
 scalar_t__ GRACEFUL_RESET_BIT1 ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  QLA83XX_IDC_DRV_CTRL ; 
 int /*<<< orphan*/  QLA8XXX_CRB_DEV_STATE ; 
 int /*<<< orphan*/  QLA8XXX_DEV_FAILED ; 
 int /*<<< orphan*/  QLA8XXX_DEV_INITIALIZING ; 
 int /*<<< orphan*/  QLA8XXX_DEV_READY ; 
 int /*<<< orphan*/  QLA8XXX_PEG_ALIVE_COUNTER ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 scalar_t__ is_qla8022 (struct scsi_qla_host*) ; 
 scalar_t__ is_qla8032 (struct scsi_qla_host*) ; 
 int msleep_interruptible (int) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*) ; 
 scalar_t__ qla4_83xx_rd_reg (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla4_83xx_wr_reg (struct scsi_qla_host*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qla4_8xxx_clear_drv_active (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_8xxx_get_minidump (struct scsi_qla_host*) ; 
 scalar_t__ qla4_8xxx_rd_direct (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla4_8xxx_wr_direct (struct scsi_qla_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub2 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub3 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub4 (struct scsi_qla_host*) ; 
 int stub5 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  stub6 (struct scsi_qla_host*) ; 

int qla4_8xxx_device_bootstrap(struct scsi_qla_host *ha)
{
	int rval = QLA_ERROR;
	int i, timeout;
	uint32_t old_count, count, idc_ctrl;
	int need_reset = 0, peg_stuck = 1;

	need_reset = ha->isp_ops->need_reset(ha);
	old_count = qla4_8xxx_rd_direct(ha, QLA8XXX_PEG_ALIVE_COUNTER);

	for (i = 0; i < 10; i++) {
		timeout = msleep_interruptible(200);
		if (timeout) {
			qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DEV_STATE,
					    QLA8XXX_DEV_FAILED);
			return rval;
		}

		count = qla4_8xxx_rd_direct(ha, QLA8XXX_PEG_ALIVE_COUNTER);
		if (count != old_count)
			peg_stuck = 0;
	}

	if (need_reset) {
		/* We are trying to perform a recovery here. */
		if (peg_stuck)
			ha->isp_ops->rom_lock_recovery(ha);
		goto dev_initialize;
	} else  {
		/* Start of day for this ha context. */
		if (peg_stuck) {
			/* Either we are the first or recovery in progress. */
			ha->isp_ops->rom_lock_recovery(ha);
			goto dev_initialize;
		} else {
			/* Firmware already running. */
			rval = QLA_SUCCESS;
			goto dev_ready;
		}
	}

dev_initialize:
	/* set to DEV_INITIALIZING */
	ql4_printk(KERN_INFO, ha, "HW State: INITIALIZING\n");
	qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DEV_STATE,
			    QLA8XXX_DEV_INITIALIZING);

	/*
	 * For ISP8324, if IDC_CTRL GRACEFUL_RESET_BIT1 is set, reset it after
	 * device goes to INIT state.
	 */
	if (is_qla8032(ha)) {
		idc_ctrl = qla4_83xx_rd_reg(ha, QLA83XX_IDC_DRV_CTRL);
		if (idc_ctrl & GRACEFUL_RESET_BIT1) {
			qla4_83xx_wr_reg(ha, QLA83XX_IDC_DRV_CTRL,
					 (idc_ctrl & ~GRACEFUL_RESET_BIT1));
			set_bit(AF_83XX_NO_FW_DUMP, &ha->flags);
		}
	}

	ha->isp_ops->idc_unlock(ha);

	if (is_qla8022(ha))
		qla4_8xxx_get_minidump(ha);

	rval = ha->isp_ops->restart_firmware(ha);
	ha->isp_ops->idc_lock(ha);

	if (rval != QLA_SUCCESS) {
		ql4_printk(KERN_INFO, ha, "HW State: FAILED\n");
		qla4_8xxx_clear_drv_active(ha);
		qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DEV_STATE,
				    QLA8XXX_DEV_FAILED);
		return rval;
	}

dev_ready:
	ql4_printk(KERN_INFO, ha, "HW State: READY\n");
	qla4_8xxx_wr_direct(ha, QLA8XXX_CRB_DEV_STATE, QLA8XXX_DEV_READY);

	return rval;
}