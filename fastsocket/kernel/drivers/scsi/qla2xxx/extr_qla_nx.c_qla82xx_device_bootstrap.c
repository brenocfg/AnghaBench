#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct qla_hw_data {int dummy; } ;
struct TYPE_5__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA82XX_CRB_DEV_STATE ; 
 int /*<<< orphan*/  QLA82XX_PEG_ALIVE_COUNTER ; 
 int /*<<< orphan*/  QLA8XXX_DEV_FAILED ; 
 int /*<<< orphan*/  QLA8XXX_DEV_INITIALIZING ; 
 int /*<<< orphan*/  QLA8XXX_DEV_READY ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int msleep_interruptible (int) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  qla82xx_clear_drv_active (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_idc_lock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_idc_unlock (struct qla_hw_data*) ; 
 int qla82xx_need_reset (struct qla_hw_data*) ; 
 scalar_t__ qla82xx_rd_32 (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla82xx_rom_lock_recovery (struct qla_hw_data*) ; 
 int qla82xx_start_firmware (TYPE_1__*) ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla82xx_device_bootstrap(scsi_qla_host_t *vha)
{
	int rval = QLA_SUCCESS;
	int i, timeout;
	uint32_t old_count, count;
	struct qla_hw_data *ha = vha->hw;
	int need_reset = 0, peg_stuck = 1;

	need_reset = qla82xx_need_reset(ha);

	old_count = qla82xx_rd_32(ha, QLA82XX_PEG_ALIVE_COUNTER);

	for (i = 0; i < 10; i++) {
		timeout = msleep_interruptible(200);
		if (timeout) {
			qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE,
				QLA8XXX_DEV_FAILED);
			return QLA_FUNCTION_FAILED;
		}

		count = qla82xx_rd_32(ha, QLA82XX_PEG_ALIVE_COUNTER);
		if (count != old_count)
			peg_stuck = 0;
	}

	if (need_reset) {
		/* We are trying to perform a recovery here. */
		if (peg_stuck)
			qla82xx_rom_lock_recovery(ha);
		goto dev_initialize;
	} else  {
		/* Start of day for this ha context. */
		if (peg_stuck) {
			/* Either we are the first or recovery in progress. */
			qla82xx_rom_lock_recovery(ha);
			goto dev_initialize;
		} else
			/* Firmware already running. */
			goto dev_ready;
	}

	return rval;

dev_initialize:
	/* set to DEV_INITIALIZING */
	ql_log(ql_log_info, vha, 0x009e,
	    "HW State: INITIALIZING.\n");
	qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE, QLA8XXX_DEV_INITIALIZING);

	qla82xx_idc_unlock(ha);
	rval = qla82xx_start_firmware(vha);
	qla82xx_idc_lock(ha);

	if (rval != QLA_SUCCESS) {
		ql_log(ql_log_fatal, vha, 0x00ad,
		    "HW State: FAILED.\n");
		qla82xx_clear_drv_active(ha);
		qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE, QLA8XXX_DEV_FAILED);
		return rval;
	}

dev_ready:
	ql_log(ql_log_info, vha, 0x00ae,
	    "HW State: READY.\n");
	qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE, QLA8XXX_DEV_READY);

	return QLA_SUCCESS;
}