#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_13__ {int /*<<< orphan*/  cpu_affinity_enabled; } ;
struct qla_hw_data {TYPE_2__ flags; int /*<<< orphan*/  vport_lock; int /*<<< orphan*/  vp_idx_map; int /*<<< orphan*/  cur_vport_count; } ;
struct fc_vport {TYPE_3__* dd_data; } ;
struct TYPE_12__ {int delete_progress; } ;
struct TYPE_14__ {int /*<<< orphan*/  host; TYPE_7__* req; int /*<<< orphan*/  vp_idx; int /*<<< orphan*/  vref_count; scalar_t__ timer_active; TYPE_1__ flags; int /*<<< orphan*/  dpc_flags; struct qla_hw_data* hw; } ;
typedef  TYPE_3__ scsi_qla_host_t ;
struct TYPE_15__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FCPORT_UPDATE_NEEDED ; 
 int /*<<< orphan*/  LOOP_RESYNC_ACTIVE ; 
 scalar_t__ QLA_SUCCESS ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ql2xextended_error_logging ; 
 int /*<<< orphan*/  ql_dbg (int,TYPE_3__*,int,char*,int /*<<< orphan*/ ) ; 
 int ql_dbg_user ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_3__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla24xx_deallocate_vp_id (TYPE_3__*) ; 
 int /*<<< orphan*/  qla24xx_disable_vp (TYPE_3__*) ; 
 scalar_t__ qla25xx_delete_req_que (TYPE_3__*,TYPE_7__*) ; 
 int /*<<< orphan*/  qla2x00_free_fcports (TYPE_3__*) ; 
 int /*<<< orphan*/  qla2x00_vp_stop_timer (TYPE_3__*) ; 
 int random32 () ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qla24xx_vport_delete(struct fc_vport *fc_vport)
{
	scsi_qla_host_t *vha = fc_vport->dd_data;
	struct qla_hw_data *ha = vha->hw;
	uint16_t id = vha->vp_idx;

	while (test_bit(LOOP_RESYNC_ACTIVE, &vha->dpc_flags) ||
	    test_bit(FCPORT_UPDATE_NEEDED, &vha->dpc_flags))
		msleep(1000);

	qla24xx_disable_vp(vha);

	vha->flags.delete_progress = 1;

	fc_remove_host(vha->host);

	scsi_remove_host(vha->host);

	/* Allow timer to run to drain queued items, when removing vp */
	qla24xx_deallocate_vp_id(vha);

	if (vha->timer_active) {
		qla2x00_vp_stop_timer(vha);
		ql_dbg(ql_dbg_user, vha, 0x7086,
		    "Timer for the VP[%d] has stopped\n", vha->vp_idx);
	}

	/* No pending activities shall be there on the vha now */
	if (ql2xextended_error_logging & ql_dbg_user)
		msleep(random32()%10);  /* Just to see if something falls on
					* the net we have placed below */

	BUG_ON(atomic_read(&vha->vref_count));

	qla2x00_free_fcports(vha);

	mutex_lock(&ha->vport_lock);
	ha->cur_vport_count--;
	clear_bit(vha->vp_idx, ha->vp_idx_map);
	mutex_unlock(&ha->vport_lock);

	if (vha->req->id && !ha->flags.cpu_affinity_enabled) {
		if (qla25xx_delete_req_que(vha, vha->req) != QLA_SUCCESS)
			ql_log(ql_log_warn, vha, 0x7087,
			    "Queue delete failed.\n");
	}

	ql_log(ql_log_info, vha, 0x7088, "VP[%d] deleted.\n", id);
	scsi_host_put(vha->host);
	return 0;
}