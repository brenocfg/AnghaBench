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
typedef  int uint32_t ;
struct req_que {int /*<<< orphan*/  ring; } ;
struct TYPE_14__ {scalar_t__ nic_core_reset_owner; } ;
struct qla_hw_data {int portnum; unsigned long fcoe_reset_timeout; TYPE_3__ flags; TYPE_2__* isp_ops; struct req_que** req_q_map; } ;
struct TYPE_12__ {scalar_t__ online; } ;
struct TYPE_15__ {TYPE_1__ flags; struct qla_hw_data* hw; } ;
typedef  TYPE_4__ scsi_qla_host_t ;
struct TYPE_13__ {int /*<<< orphan*/  (* nvram_config ) (TYPE_4__*) ;int /*<<< orphan*/  (* get_flash_version ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 unsigned long HZ ; 
 int MAX_STATES ; 
 int /*<<< orphan*/  QLA82XX_CRB_DEV_STATE ; 
 int /*<<< orphan*/  QLA82XX_CRB_DRV_ACTIVE ; 
 int /*<<< orphan*/  QLA82XX_CRB_DRV_STATE ; 
 int QLA82XX_DRV_ACTIVE ; 
 int QLA8XXX_DEV_COLD ; 
 int QLA8XXX_DEV_INITIALIZING ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 char* qdev_state (int) ; 
 scalar_t__ ql2xmdenable ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_4__*,int,char*,int,...) ; 
 int /*<<< orphan*/  ql_dbg_p3p ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_4__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla2x00_abort_isp_cleanup (TYPE_4__*) ; 
 int /*<<< orphan*/  qla82xx_idc_lock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_idc_unlock (struct qla_hw_data*) ; 
 scalar_t__ qla82xx_md_collect (TYPE_4__*) ; 
 int qla82xx_rd_32 (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla82xx_set_rst_ready (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static void
qla82xx_need_reset_handler(scsi_qla_host_t *vha)
{
	uint32_t dev_state, drv_state, drv_active;
	uint32_t active_mask = 0;
	unsigned long reset_timeout;
	struct qla_hw_data *ha = vha->hw;
	struct req_que *req = ha->req_q_map[0];

	if (vha->flags.online) {
		qla82xx_idc_unlock(ha);
		qla2x00_abort_isp_cleanup(vha);
		ha->isp_ops->get_flash_version(vha, req->ring);
		ha->isp_ops->nvram_config(vha);
		qla82xx_idc_lock(ha);
	}

	drv_active = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);
	if (!ha->flags.nic_core_reset_owner) {
		ql_dbg(ql_dbg_p3p, vha, 0xb028,
		    "reset_acknowledged by 0x%x\n", ha->portnum);
		qla82xx_set_rst_ready(ha);
	} else {
		active_mask = ~(QLA82XX_DRV_ACTIVE << (ha->portnum * 4));
		drv_active &= active_mask;
		ql_dbg(ql_dbg_p3p, vha, 0xb029,
		    "active_mask: 0x%08x\n", active_mask);
	}

	/* wait for 10 seconds for reset ack from all functions */
	reset_timeout = jiffies + (ha->fcoe_reset_timeout * HZ);

	drv_state = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
	drv_active = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);
	dev_state = qla82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);

	ql_dbg(ql_dbg_p3p, vha, 0xb02a,
	    "drv_state: 0x%08x, drv_active: 0x%08x, "
	    "dev_state: 0x%08x, active_mask: 0x%08x\n",
	    drv_state, drv_active, dev_state, active_mask);

	while (drv_state != drv_active &&
		dev_state != QLA8XXX_DEV_INITIALIZING) {
		if (time_after_eq(jiffies, reset_timeout)) {
			ql_log(ql_log_warn, vha, 0x00b5,
			    "Reset timeout.\n");
			break;
		}
		qla82xx_idc_unlock(ha);
		msleep(1000);
		qla82xx_idc_lock(ha);
		drv_state = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_STATE);
		drv_active = qla82xx_rd_32(ha, QLA82XX_CRB_DRV_ACTIVE);
		if (ha->flags.nic_core_reset_owner)
			drv_active &= active_mask;
		dev_state = qla82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);
	}

	ql_dbg(ql_dbg_p3p, vha, 0xb02b,
	    "drv_state: 0x%08x, drv_active: 0x%08x, "
	    "dev_state: 0x%08x, active_mask: 0x%08x\n",
	    drv_state, drv_active, dev_state, active_mask);

	ql_log(ql_log_info, vha, 0x00b6,
	    "Device state is 0x%x = %s.\n",
	    dev_state,
	    dev_state < MAX_STATES ? qdev_state(dev_state) : "Unknown");

	/* Force to DEV_COLD unless someone else is starting a reset */
	if (dev_state != QLA8XXX_DEV_INITIALIZING &&
	    dev_state != QLA8XXX_DEV_COLD) {
		ql_log(ql_log_info, vha, 0x00b7,
		    "HW State: COLD/RE-INIT.\n");
		qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE, QLA8XXX_DEV_COLD);
		qla82xx_set_rst_ready(ha);
		if (ql2xmdenable) {
			if (qla82xx_md_collect(vha))
				ql_log(ql_log_warn, vha, 0xb02c,
				    "Minidump not collected.\n");
		} else
			ql_log(ql_log_warn, vha, 0xb04f,
			    "Minidump disabled.\n");
	}
}