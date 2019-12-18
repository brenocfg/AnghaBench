#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct req_que {int num_outstanding_cmds; TYPE_3__** outstanding_cmds; } ;
struct TYPE_13__ {scalar_t__ eeh_busy; } ;
struct qla_hw_data {int beacon_blink_led; int /*<<< orphan*/  hardware_lock; struct req_que** req_q_map; int /*<<< orphan*/  pdev; TYPE_1__ flags; } ;
struct TYPE_15__ {scalar_t__ type; TYPE_5__* fcport; } ;
typedef  TYPE_3__ srb_t ;
struct TYPE_14__ {scalar_t__ online; } ;
struct TYPE_16__ {scalar_t__ loop_down_abort_time; int device_flags; int /*<<< orphan*/  dpc_flags; int /*<<< orphan*/  work_list; int /*<<< orphan*/  vp_idx; int /*<<< orphan*/  loop_down_timer; int /*<<< orphan*/  loop_state; scalar_t__ link_down_timeout; TYPE_2__ flags; struct qla_hw_data* hw; } ;
typedef  TYPE_4__ scsi_qla_host_t ;
struct TYPE_17__ {int flags; } ;
typedef  TYPE_5__ fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_ISP_ACTIVE ; 
 int /*<<< orphan*/  BEACON_BLINK_NEEDED ; 
 int DFLG_NO_CABLE ; 
 int FCF_FCP2_DEVICE ; 
 int /*<<< orphan*/  FCOE_CTX_RESET_NEEDED ; 
 int /*<<< orphan*/  FCPORT_UPDATE_NEEDED ; 
 int /*<<< orphan*/  ISP_ABORT_NEEDED ; 
 int /*<<< orphan*/  ISP_QUIESCE_NEEDED ; 
 int /*<<< orphan*/  ISP_UNRECOVERABLE ; 
 int /*<<< orphan*/  IS_QLA2100 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA82XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLAFX00 (struct qla_hw_data*) ; 
 int /*<<< orphan*/  LOOP_DEAD ; 
 int /*<<< orphan*/  LOOP_RESYNC_NEEDED ; 
 int /*<<< orphan*/  PCI_VENDOR_ID ; 
 int /*<<< orphan*/  RELOGIN_NEEDED ; 
 int /*<<< orphan*/  RESET_MARKER_NEEDED ; 
 scalar_t__ SRB_SCSI_CMD ; 
 int /*<<< orphan*/  VP_DPC_NEEDED ; 
 int /*<<< orphan*/  WATCH_INTERVAL ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_channel_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_4__*,int,char*,int,...) ; 
 int /*<<< orphan*/  ql_dbg_timer ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_4__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla2x00_restart_timer (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2xxx_wake_dpc (TYPE_4__*) ; 
 int /*<<< orphan*/  qla82xx_watchdog (TYPE_4__*) ; 
 int /*<<< orphan*/  qlafx00_timer_routine (TYPE_4__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
qla2x00_timer(scsi_qla_host_t *vha)
{
	unsigned long	cpu_flags = 0;
	int		start_dpc = 0;
	int		index;
	srb_t		*sp;
	uint16_t        w;
	struct qla_hw_data *ha = vha->hw;
	struct req_que *req;

	if (ha->flags.eeh_busy) {
		ql_dbg(ql_dbg_timer, vha, 0x6000,
		    "EEH = %d, restarting timer.\n",
		    ha->flags.eeh_busy);
		qla2x00_restart_timer(vha, WATCH_INTERVAL);
		return;
	}

	/* Hardware read to raise pending EEH errors during mailbox waits. */
	if (!pci_channel_offline(ha->pdev))
		pci_read_config_word(ha->pdev, PCI_VENDOR_ID, &w);

	/* Make sure qla82xx_watchdog is run only for physical port */
	if (!vha->vp_idx && IS_QLA82XX(ha)) {
		if (test_bit(ISP_QUIESCE_NEEDED, &vha->dpc_flags))
			start_dpc++;
		qla82xx_watchdog(vha);
	}

	if (!vha->vp_idx && IS_QLAFX00(ha))
		qlafx00_timer_routine(vha);

	/* Loop down handler. */
	if (atomic_read(&vha->loop_down_timer) > 0 &&
	    !(test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags)) &&
	    !(test_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags))
		&& vha->flags.online) {

		if (atomic_read(&vha->loop_down_timer) ==
		    vha->loop_down_abort_time) {

			ql_log(ql_log_info, vha, 0x6008,
			    "Loop down - aborting the queues before time expires.\n");

			if (!IS_QLA2100(ha) && vha->link_down_timeout)
				atomic_set(&vha->loop_state, LOOP_DEAD);

			/*
			 * Schedule an ISP abort to return any FCP2-device
			 * commands.
			 */
			/* NPIV - scan physical port only */
			if (!vha->vp_idx) {
				spin_lock_irqsave(&ha->hardware_lock,
				    cpu_flags);
				req = ha->req_q_map[0];
				for (index = 1;
				    index < req->num_outstanding_cmds;
				    index++) {
					fc_port_t *sfcp;

					sp = req->outstanding_cmds[index];
					if (!sp)
						continue;
					if (sp->type != SRB_SCSI_CMD)
						continue;
					sfcp = sp->fcport;
					if (!(sfcp->flags & FCF_FCP2_DEVICE))
						continue;

					if (IS_QLA82XX(ha))
						set_bit(FCOE_CTX_RESET_NEEDED,
							&vha->dpc_flags);
					else
						set_bit(ISP_ABORT_NEEDED,
							&vha->dpc_flags);
					break;
				}
				spin_unlock_irqrestore(&ha->hardware_lock,
								cpu_flags);
			}
			start_dpc++;
		}

		/* if the loop has been down for 4 minutes, reinit adapter */
		if (atomic_dec_and_test(&vha->loop_down_timer) != 0) {
			if (!(vha->device_flags & DFLG_NO_CABLE)) {
				ql_log(ql_log_warn, vha, 0x6009,
				    "Loop down - aborting ISP.\n");

				if (IS_QLA82XX(ha))
					set_bit(FCOE_CTX_RESET_NEEDED,
						&vha->dpc_flags);
				else
					set_bit(ISP_ABORT_NEEDED,
						&vha->dpc_flags);
			}
		}
		ql_dbg(ql_dbg_timer, vha, 0x600a,
		    "Loop down - seconds remaining %d.\n",
		    atomic_read(&vha->loop_down_timer));
	}
	/* Check if beacon LED needs to be blinked for physical host only */
	if (!vha->vp_idx && (ha->beacon_blink_led == 1)) {
		/* There is no beacon_blink function for ISP82xx */
		if (!IS_QLA82XX(ha)) {
			set_bit(BEACON_BLINK_NEEDED, &vha->dpc_flags);
			start_dpc++;
		}
	}

	/* Process any deferred work. */
	if (!list_empty(&vha->work_list))
		start_dpc++;

	/* Schedule the DPC routine if needed */
	if ((test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags) ||
	    test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags) ||
	    test_bit(FCPORT_UPDATE_NEEDED, &vha->dpc_flags) ||
	    start_dpc ||
	    test_bit(RESET_MARKER_NEEDED, &vha->dpc_flags) ||
	    test_bit(BEACON_BLINK_NEEDED, &vha->dpc_flags) ||
	    test_bit(ISP_UNRECOVERABLE, &vha->dpc_flags) ||
	    test_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags) ||
	    test_bit(VP_DPC_NEEDED, &vha->dpc_flags) ||
	    test_bit(RELOGIN_NEEDED, &vha->dpc_flags))) {
		ql_dbg(ql_dbg_timer, vha, 0x600b,
		    "isp_abort_needed=%d loop_resync_needed=%d "
		    "fcport_update_needed=%d start_dpc=%d "
		    "reset_marker_needed=%d",
		    test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags),
		    test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags),
		    test_bit(FCPORT_UPDATE_NEEDED, &vha->dpc_flags),
		    start_dpc,
		    test_bit(RESET_MARKER_NEEDED, &vha->dpc_flags));
		ql_dbg(ql_dbg_timer, vha, 0x600c,
		    "beacon_blink_needed=%d isp_unrecoverable=%d "
		    "fcoe_ctx_reset_needed=%d vp_dpc_needed=%d "
		    "relogin_needed=%d.\n",
		    test_bit(BEACON_BLINK_NEEDED, &vha->dpc_flags),
		    test_bit(ISP_UNRECOVERABLE, &vha->dpc_flags),
		    test_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags),
		    test_bit(VP_DPC_NEEDED, &vha->dpc_flags),
		    test_bit(RELOGIN_NEEDED, &vha->dpc_flags));
		qla2xxx_wake_dpc(vha);
	}

	qla2x00_restart_timer(vha, WATCH_INTERVAL);
}