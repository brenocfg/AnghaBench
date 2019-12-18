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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_11__ {int flags; int /*<<< orphan*/ * data; } ;
struct TYPE_12__ {TYPE_2__ logio; } ;
struct srb_iocb {TYPE_3__ u; } ;
struct req_que {int dummy; } ;
struct logio_entry_24xx {scalar_t__* io_parameter; int /*<<< orphan*/  comp_status; int /*<<< orphan*/  entry_status; } ;
struct TYPE_10__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_15__ {char* name; scalar_t__ type; int /*<<< orphan*/  (* done ) (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  handle; TYPE_7__* fcport; TYPE_1__ u; } ;
typedef  TYPE_6__ srb_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
struct TYPE_13__ {int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_14__ {TYPE_4__ b; } ;
struct TYPE_16__ {TYPE_5__ d_id; int /*<<< orphan*/  vha; int /*<<< orphan*/  supported_classes; int /*<<< orphan*/  port_type; int /*<<< orphan*/  flags; } ;
typedef  TYPE_7__ fc_port_t ;

/* Variables and functions */
 int BIT_4 ; 
 int BIT_5 ; 
 int BIT_8 ; 
 scalar_t__ CS_COMPLETE ; 
 int /*<<< orphan*/  FCF_FCP2_DEVICE ; 
 int /*<<< orphan*/  FCT_INITIATOR ; 
 int /*<<< orphan*/  FCT_TARGET ; 
 int /*<<< orphan*/  FC_COS_CLASS2 ; 
 int /*<<< orphan*/  FC_COS_CLASS3 ; 
#define  LSC_SCODE_NPORT_USED 129 
#define  LSC_SCODE_PORTID_USED 128 
 int /*<<< orphan*/  LSW (int) ; 
 int /*<<< orphan*/  MBS_COMMAND_COMPLETE ; 
 int /*<<< orphan*/  MBS_COMMAND_ERROR ; 
 int /*<<< orphan*/  MBS_LOOP_ID_USED ; 
 int /*<<< orphan*/  MBS_PORT_ID_USED ; 
 int /*<<< orphan*/  QLA_LOGIO_LOGIN_RETRIED ; 
 scalar_t__ SRB_LOGIN_CMD ; 
 int SRB_LOGIN_RETRIED ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  ql_dbg (scalar_t__,int /*<<< orphan*/ ,int,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,...) ; 
 scalar_t__ ql_dbg_async ; 
 scalar_t__ ql_dbg_buffer ; 
 int /*<<< orphan*/  ql_dump_buffer (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 TYPE_6__* qla2x00_get_sp_from_handle (int /*<<< orphan*/ *,char const*,struct req_que*,struct logio_entry_24xx*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qla24xx_logio_entry(scsi_qla_host_t *vha, struct req_que *req,
    struct logio_entry_24xx *logio)
{
	const char func[] = "LOGIO-IOCB";
	const char *type;
	fc_port_t *fcport;
	srb_t *sp;
	struct srb_iocb *lio;
	uint16_t *data;
	uint32_t iop[2];

	sp = qla2x00_get_sp_from_handle(vha, func, req, logio);
	if (!sp)
		return;
	lio = &sp->u.iocb_cmd;
	type = sp->name;

	fcport = sp->fcport;
	data = lio->u.logio.data;

	data[0] = MBS_COMMAND_ERROR;
	data[1] = lio->u.logio.flags & SRB_LOGIN_RETRIED ?
	    QLA_LOGIO_LOGIN_RETRIED: 0;
	if (logio->entry_status) {
		ql_log(ql_log_warn, fcport->vha, 0x5034,
		    "Async-%s error entry - hdl=%x"
		    "portid=%02x%02x%02x entry-status=%x.\n",
		    type, sp->handle, fcport->d_id.b.domain,
		    fcport->d_id.b.area, fcport->d_id.b.al_pa,
		    logio->entry_status);
		ql_dump_buffer(ql_dbg_async + ql_dbg_buffer, vha, 0x504d,
		    (uint8_t *)logio, sizeof(*logio));

		goto logio_done;
	}

	if (le16_to_cpu(logio->comp_status) == CS_COMPLETE) {
		ql_dbg(ql_dbg_async, fcport->vha, 0x5036,
		    "Async-%s complete - hdl=%x portid=%02x%02x%02x "
		    "iop0=%x.\n", type, sp->handle, fcport->d_id.b.domain,
		    fcport->d_id.b.area, fcport->d_id.b.al_pa,
		    le32_to_cpu(logio->io_parameter[0]));

		data[0] = MBS_COMMAND_COMPLETE;
		if (sp->type != SRB_LOGIN_CMD)
			goto logio_done;

		iop[0] = le32_to_cpu(logio->io_parameter[0]);
		if (iop[0] & BIT_4) {
			fcport->port_type = FCT_TARGET;
			if (iop[0] & BIT_8)
				fcport->flags |= FCF_FCP2_DEVICE;
		} else if (iop[0] & BIT_5)
			fcport->port_type = FCT_INITIATOR;

		if (logio->io_parameter[7] || logio->io_parameter[8])
			fcport->supported_classes |= FC_COS_CLASS2;
		if (logio->io_parameter[9] || logio->io_parameter[10])
			fcport->supported_classes |= FC_COS_CLASS3;

		goto logio_done;
	}

	iop[0] = le32_to_cpu(logio->io_parameter[0]);
	iop[1] = le32_to_cpu(logio->io_parameter[1]);
	switch (iop[0]) {
	case LSC_SCODE_PORTID_USED:
		data[0] = MBS_PORT_ID_USED;
		data[1] = LSW(iop[1]);
		break;
	case LSC_SCODE_NPORT_USED:
		data[0] = MBS_LOOP_ID_USED;
		break;
	default:
		data[0] = MBS_COMMAND_ERROR;
		break;
	}

	ql_dbg(ql_dbg_async, fcport->vha, 0x5037,
	    "Async-%s failed - hdl=%x portid=%02x%02x%02x comp=%x "
	    "iop0=%x iop1=%x.\n", type, sp->handle, fcport->d_id.b.domain,
	    fcport->d_id.b.area, fcport->d_id.b.al_pa,
	    le16_to_cpu(logio->comp_status),
	    le32_to_cpu(logio->io_parameter[0]),
	    le32_to_cpu(logio->io_parameter[1]));

logio_done:
	sp->done(vha, sp, 0);
}