#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int nic_core_reset_hdlr_active; scalar_t__ isp82xx_fw_hung; } ;
struct qla_hw_data {scalar_t__ isp_abort_cnt; TYPE_2__* isp_ops; TYPE_1__ flags; } ;
struct TYPE_14__ {int online; } ;
struct TYPE_15__ {int device_flags; int /*<<< orphan*/  dpc_flags; TYPE_3__ flags; struct qla_hw_data* hw; } ;
typedef  TYPE_4__ scsi_qla_host_t ;
struct TYPE_13__ {int /*<<< orphan*/  (* reset_adapter ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int DFLG_DEV_FAILED ; 
 int /*<<< orphan*/  ISP_ABORT_RETRY ; 
 scalar_t__ MAX_RETRIES_OF_ISP_ABORT ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_4__*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ql_dbg_taskm ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_4__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla82xx_clear_rst_ready (struct qla_hw_data*) ; 
 int qla82xx_device_state_handler (TYPE_4__*) ; 
 int /*<<< orphan*/  qla82xx_idc_lock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_idc_unlock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_restart_isp (TYPE_4__*) ; 
 int /*<<< orphan*/  qla82xx_set_reset_owner (TYPE_4__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
qla82xx_abort_isp(scsi_qla_host_t *vha)
{
	int rval;
	struct qla_hw_data *ha = vha->hw;

	if (vha->device_flags & DFLG_DEV_FAILED) {
		ql_log(ql_log_warn, vha, 0x8024,
		    "Device in failed state, exiting.\n");
		return QLA_SUCCESS;
	}
	ha->flags.nic_core_reset_hdlr_active = 1;

	qla82xx_idc_lock(ha);
	qla82xx_set_reset_owner(vha);
	qla82xx_idc_unlock(ha);

	rval = qla82xx_device_state_handler(vha);

	qla82xx_idc_lock(ha);
	qla82xx_clear_rst_ready(ha);
	qla82xx_idc_unlock(ha);

	if (rval == QLA_SUCCESS) {
		ha->flags.isp82xx_fw_hung = 0;
		ha->flags.nic_core_reset_hdlr_active = 0;
		qla82xx_restart_isp(vha);
	}

	if (rval) {
		vha->flags.online = 1;
		if (test_bit(ISP_ABORT_RETRY, &vha->dpc_flags)) {
			if (ha->isp_abort_cnt == 0) {
				ql_log(ql_log_warn, vha, 0x8027,
				    "ISP error recover failed - board "
				    "disabled.\n");
				/*
				 * The next call disables the board
				 * completely.
				 */
				ha->isp_ops->reset_adapter(vha);
				vha->flags.online = 0;
				clear_bit(ISP_ABORT_RETRY,
				    &vha->dpc_flags);
				rval = QLA_SUCCESS;
			} else { /* schedule another ISP abort */
				ha->isp_abort_cnt--;
				ql_log(ql_log_warn, vha, 0x8036,
				    "ISP abort - retry remaining %d.\n",
				    ha->isp_abort_cnt);
				rval = QLA_FUNCTION_FAILED;
			}
		} else {
			ha->isp_abort_cnt = MAX_RETRIES_OF_ISP_ABORT;
			ql_dbg(ql_dbg_taskm, vha, 0x8029,
			    "ISP error recovery - retrying (%d) more times.\n",
			    ha->isp_abort_cnt);
			set_bit(ISP_ABORT_RETRY, &vha->dpc_flags);
			rval = QLA_FUNCTION_FAILED;
		}
	}
	return rval;
}