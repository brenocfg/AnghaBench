#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  vp_idx; int /*<<< orphan*/  dpc_flags; int /*<<< orphan*/  loop_down_timer; int /*<<< orphan*/  loop_state; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_ISP_ACTIVE ; 
 scalar_t__ LOOP_DOWN ; 
 scalar_t__ LOOP_DOWN_TIME ; 
 int /*<<< orphan*/  VCE_COMMAND_DISABLE_VPS_LOGO_ALL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_1__*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_taskm ; 
 int /*<<< orphan*/  qla24xx_control_vp (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int qla24xx_enable_vp (TYPE_1__*) ; 
 int /*<<< orphan*/  qla2x00_mark_all_devices_lost (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
qla2x00_vp_abort_isp(scsi_qla_host_t *vha)
{
	/*
	 * Physical port will do most of the abort and recovery work. We can
	 * just treat it as a loop down
	 */
	if (atomic_read(&vha->loop_state) != LOOP_DOWN) {
		atomic_set(&vha->loop_state, LOOP_DOWN);
		qla2x00_mark_all_devices_lost(vha, 0);
	} else {
		if (!atomic_read(&vha->loop_down_timer))
			atomic_set(&vha->loop_down_timer, LOOP_DOWN_TIME);
	}

	/*
	 * To exclusively reset vport, we need to log it out first.  Note: this
	 * control_vp can fail if ISP reset is already issued, this is
	 * expected, as the vp would be already logged out due to ISP reset.
	 */
	if (!test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags))
		qla24xx_control_vp(vha, VCE_COMMAND_DISABLE_VPS_LOGO_ALL);

	ql_dbg(ql_dbg_taskm, vha, 0x801d,
	    "Scheduling enable of Vport %d.\n", vha->vp_idx);
	return qla24xx_enable_vp(vha);
}