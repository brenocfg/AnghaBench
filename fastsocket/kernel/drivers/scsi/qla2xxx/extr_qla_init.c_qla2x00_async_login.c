#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_15__ {int /*<<< orphan*/  flags; } ;
struct TYPE_16__ {TYPE_2__ logio; } ;
struct srb_iocb {TYPE_3__ u; int /*<<< orphan*/  timeout; } ;
struct scsi_qla_host {int dummy; } ;
struct TYPE_14__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_19__ {char* name; int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ ,TYPE_6__*) ;int /*<<< orphan*/  handle; int /*<<< orphan*/  done; TYPE_1__ u; int /*<<< orphan*/  type; } ;
typedef  TYPE_6__ srb_t ;
struct TYPE_17__ {int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_18__ {TYPE_4__ b; } ;
struct TYPE_20__ {int /*<<< orphan*/  vha; int /*<<< orphan*/  login_retry; TYPE_5__ d_id; int /*<<< orphan*/  loop_id; } ;
typedef  TYPE_7__ fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_LOGIO_LOGIN_RETRIED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  SRB_LOGIN_CMD ; 
 int /*<<< orphan*/  SRB_LOGIN_COND_PLOGI ; 
 int /*<<< orphan*/  SRB_LOGIN_RETRIED ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  qla2x00_async_iocb_timeout ; 
 int /*<<< orphan*/  qla2x00_async_login_sp_done ; 
 scalar_t__ qla2x00_get_async_timeout (struct scsi_qla_host*) ; 
 TYPE_6__* qla2x00_get_sp (struct scsi_qla_host*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_init_timer (TYPE_6__*,scalar_t__) ; 
 int qla2x00_start_sp (TYPE_6__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_6__*) ; 

int
qla2x00_async_login(struct scsi_qla_host *vha, fc_port_t *fcport,
    uint16_t *data)
{
	srb_t *sp;
	struct srb_iocb *lio;
	int rval;

	rval = QLA_FUNCTION_FAILED;
	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	if (!sp)
		goto done;

	sp->type = SRB_LOGIN_CMD;
	sp->name = "login";
	qla2x00_init_timer(sp, qla2x00_get_async_timeout(vha) + 2);
	lio = &sp->u.iocb_cmd;
	lio->timeout = qla2x00_async_iocb_timeout;
	sp->done = qla2x00_async_login_sp_done;
	lio->u.logio.flags |= SRB_LOGIN_COND_PLOGI;
	if (data[1] & QLA_LOGIO_LOGIN_RETRIED)
		lio->u.logio.flags |= SRB_LOGIN_RETRIED;
	rval = qla2x00_start_sp(sp);
	if (rval != QLA_SUCCESS)
		goto done_free_sp;

	ql_dbg(ql_dbg_disc, vha, 0x2072,
	    "Async-login - hdl=%x, loopid=%x portid=%02x%02x%02x "
	    "retries=%d.\n", sp->handle, fcport->loop_id,
	    fcport->d_id.b.domain, fcport->d_id.b.area, fcport->d_id.b.al_pa,
	    fcport->login_retry);
	return rval;

done_free_sp:
	sp->free(fcport->vha, sp);
done:
	return rval;
}