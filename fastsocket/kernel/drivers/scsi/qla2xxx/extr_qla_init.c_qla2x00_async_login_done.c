#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct scsi_qla_host {int /*<<< orphan*/  dpc_flags; } ;
struct TYPE_10__ {int flags; int loop_id; } ;
typedef  TYPE_1__ fc_port_t ;

/* Variables and functions */
 int FCF_ASYNC_SENT ; 
 int FCF_FCP2_DEVICE ; 
 int FCF_LOGIN_NEEDED ; 
#define  MBS_COMMAND_COMPLETE 131 
#define  MBS_COMMAND_ERROR 130 
#define  MBS_LOOP_ID_USED 129 
#define  MBS_PORT_ID_USED 128 
 int QLA_LOGIO_LOGIN_RETRIED ; 
 int QLA_NOT_LOGGED_IN ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  RELOGIN_NEEDED ; 
 int qla2x00_find_new_loop_id (struct scsi_qla_host*,TYPE_1__*) ; 
 int qla2x00_get_port_database (struct scsi_qla_host*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_mark_device_lost (struct scsi_qla_host*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_post_async_adisc_work (struct scsi_qla_host*,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  qla2x00_post_async_login_work (struct scsi_qla_host*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla2x00_post_async_logout_work (struct scsi_qla_host*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla2x00_update_fcport (struct scsi_qla_host*,TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
qla2x00_async_login_done(struct scsi_qla_host *vha, fc_port_t *fcport,
    uint16_t *data)
{
	int rval;

	switch (data[0]) {
	case MBS_COMMAND_COMPLETE:
		/*
		 * Driver must validate login state - If PRLI not complete,
		 * force a relogin attempt via implicit LOGO, PLOGI, and PRLI
		 * requests.
		 */
		rval = qla2x00_get_port_database(vha, fcport, 0);
		if (rval == QLA_NOT_LOGGED_IN) {
			fcport->flags &= ~FCF_ASYNC_SENT;
			fcport->flags |= FCF_LOGIN_NEEDED;
			set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
			break;
		}

		if (rval != QLA_SUCCESS) {
			qla2x00_post_async_logout_work(vha, fcport, NULL);
			qla2x00_post_async_login_work(vha, fcport, NULL);
			break;
		}
		if (fcport->flags & FCF_FCP2_DEVICE) {
			qla2x00_post_async_adisc_work(vha, fcport, data);
			break;
		}
		qla2x00_update_fcport(vha, fcport);
		break;
	case MBS_COMMAND_ERROR:
		fcport->flags &= ~FCF_ASYNC_SENT;
		if (data[1] & QLA_LOGIO_LOGIN_RETRIED)
			set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
		else
			qla2x00_mark_device_lost(vha, fcport, 1, 0);
		break;
	case MBS_PORT_ID_USED:
		fcport->loop_id = data[1];
		qla2x00_post_async_logout_work(vha, fcport, NULL);
		qla2x00_post_async_login_work(vha, fcport, NULL);
		break;
	case MBS_LOOP_ID_USED:
		fcport->loop_id++;
		rval = qla2x00_find_new_loop_id(vha, fcport);
		if (rval != QLA_SUCCESS) {
			fcport->flags &= ~FCF_ASYNC_SENT;
			qla2x00_mark_device_lost(vha, fcport, 1, 0);
			break;
		}
		qla2x00_post_async_login_work(vha, fcport, NULL);
		break;
	}
	return;
}