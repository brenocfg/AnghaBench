#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;
struct TYPE_13__ {int flags; scalar_t__ login_retry; TYPE_1__* vha; } ;
typedef  TYPE_2__ fc_port_t ;

/* Variables and functions */
 int FCF_ASYNC_SENT ; 
 int FCF_LOGIN_NEEDED ; 
 int /*<<< orphan*/  FCS_ONLINE ; 
 scalar_t__ IS_QLAFX00 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla24xx_update_fcport_fcp_prio (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  qla2x00_iidma_fcport (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  qla2x00_reg_remote_port (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  qla2x00_set_fcport_state (TYPE_2__*,int /*<<< orphan*/ ) ; 

void
qla2x00_update_fcport(scsi_qla_host_t *vha, fc_port_t *fcport)
{
	fcport->vha = vha;

	if (IS_QLAFX00(vha->hw)) {
		qla2x00_set_fcport_state(fcport, FCS_ONLINE);
		qla2x00_reg_remote_port(vha, fcport);
		return;
	}
	fcport->login_retry = 0;
	fcport->flags &= ~(FCF_LOGIN_NEEDED | FCF_ASYNC_SENT);

	qla2x00_set_fcport_state(fcport, FCS_ONLINE);
	qla2x00_iidma_fcport(vha, fcport);
	qla24xx_update_fcport_fcp_prio(vha, fcport);
	qla2x00_reg_remote_port(vha, fcport);
}