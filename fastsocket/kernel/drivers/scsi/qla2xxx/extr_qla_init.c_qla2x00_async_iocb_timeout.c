#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int flags; int /*<<< orphan*/ * data; } ;
struct TYPE_14__ {TYPE_4__ logio; } ;
struct srb_iocb {TYPE_5__ u; } ;
struct TYPE_12__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_15__ {scalar_t__ type; TYPE_3__ u; int /*<<< orphan*/  handle; int /*<<< orphan*/  name; TYPE_7__* fcport; } ;
typedef  TYPE_6__ srb_t ;
struct TYPE_10__ {int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_11__ {TYPE_1__ b; } ;
struct TYPE_16__ {int /*<<< orphan*/  vha; int /*<<< orphan*/  flags; TYPE_2__ d_id; } ;
typedef  TYPE_7__ fc_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  FCF_ASYNC_SENT ; 
 int /*<<< orphan*/  MBS_COMMAND_ERROR ; 
 int /*<<< orphan*/  QLA_LOGIO_LOGIN_RETRIED ; 
 scalar_t__ SRB_LOGIN_CMD ; 
 int SRB_LOGIN_RETRIED ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  qla2x00_post_async_login_done_work (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla2x00_post_async_logout_work (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qla2x00_async_iocb_timeout(void *data)
{
	srb_t *sp = (srb_t *)data;
	fc_port_t *fcport = sp->fcport;

	ql_dbg(ql_dbg_disc, fcport->vha, 0x2071,
	    "Async-%s timeout - hdl=%x portid=%02x%02x%02x.\n",
	    sp->name, sp->handle, fcport->d_id.b.domain, fcport->d_id.b.area,
	    fcport->d_id.b.al_pa);

	fcport->flags &= ~FCF_ASYNC_SENT;
	if (sp->type == SRB_LOGIN_CMD) {
		struct srb_iocb *lio = &sp->u.iocb_cmd;
		qla2x00_post_async_logout_work(fcport->vha, fcport, NULL);
		/* Retry as needed. */
		lio->u.logio.data[0] = MBS_COMMAND_ERROR;
		lio->u.logio.data[1] = lio->u.logio.flags & SRB_LOGIN_RETRIED ?
		    QLA_LOGIO_LOGIN_RETRIED : 0;
		qla2x00_post_async_login_done_work(fcport->vha, fcport,
		    lio->u.logio.data);
	}
}