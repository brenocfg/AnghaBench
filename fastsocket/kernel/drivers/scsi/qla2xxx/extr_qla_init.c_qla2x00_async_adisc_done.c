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
typedef  int uint16_t ;
struct scsi_qla_host {int /*<<< orphan*/  dpc_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  FCF_ASYNC_SENT ; 
 int MBS_COMMAND_COMPLETE ; 
 int QLA_LOGIO_LOGIN_RETRIED ; 
 int /*<<< orphan*/  RELOGIN_NEEDED ; 
 int /*<<< orphan*/  qla2x00_mark_device_lost (struct scsi_qla_host*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_update_fcport (struct scsi_qla_host*,TYPE_1__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
qla2x00_async_adisc_done(struct scsi_qla_host *vha, fc_port_t *fcport,
    uint16_t *data)
{
	if (data[0] == MBS_COMMAND_COMPLETE) {
		qla2x00_update_fcport(vha, fcport);

		return;
	}

	/* Retry login. */
	fcport->flags &= ~FCF_ASYNC_SENT;
	if (data[1] & QLA_LOGIO_LOGIN_RETRIED)
		set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
	else
		qla2x00_mark_device_lost(vha, fcport, 1, 0);

	return;
}