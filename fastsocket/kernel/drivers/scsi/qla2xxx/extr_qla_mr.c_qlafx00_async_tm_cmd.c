#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_13__ {scalar_t__ comp_status; int /*<<< orphan*/  comp; void* data; void* lun; void* flags; } ;
struct TYPE_14__ {TYPE_2__ tmf; } ;
struct srb_iocb {TYPE_3__ u; int /*<<< orphan*/  timeout; } ;
struct TYPE_12__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_15__ {char* name; int /*<<< orphan*/  (* free ) (int /*<<< orphan*/ *,TYPE_4__*) ;int /*<<< orphan*/  done; int /*<<< orphan*/  type; TYPE_1__ u; } ;
typedef  TYPE_4__ srb_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
struct TYPE_16__ {int /*<<< orphan*/  tgt_id; int /*<<< orphan*/ * vha; } ;
typedef  TYPE_5__ fc_port_t ;

/* Variables and functions */
 scalar_t__ CS_COMPLETE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  SRB_TM_CMD ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_async ; 
 int /*<<< orphan*/  qla2x00_get_async_timeout (int /*<<< orphan*/ *) ; 
 TYPE_4__* qla2x00_get_sp (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_init_timer (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int qla2x00_start_sp (TYPE_4__*) ; 
 int /*<<< orphan*/  qlafx00_tmf_iocb_timeout ; 
 int /*<<< orphan*/  qlafx00_tmf_sp_done ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qlafx00_async_tm_cmd(fc_port_t *fcport, uint32_t flags,
		     uint32_t lun, uint32_t tag)
{
	scsi_qla_host_t *vha = fcport->vha;
	struct srb_iocb *tm_iocb;
	srb_t *sp;
	int rval = QLA_FUNCTION_FAILED;

	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	if (!sp)
		goto done;

	tm_iocb = &sp->u.iocb_cmd;
	sp->type = SRB_TM_CMD;
	sp->name = "tmf";
	qla2x00_init_timer(sp, qla2x00_get_async_timeout(vha));
	tm_iocb->u.tmf.flags = flags;
	tm_iocb->u.tmf.lun = lun;
	tm_iocb->u.tmf.data = tag;
	sp->done = qlafx00_tmf_sp_done;
	tm_iocb->timeout = qlafx00_tmf_iocb_timeout;
	init_completion(&tm_iocb->u.tmf.comp);

	rval = qla2x00_start_sp(sp);
	if (rval != QLA_SUCCESS)
		goto done_free_sp;

	ql_dbg(ql_dbg_async, vha, 0x507b,
	    "Task management command issued target_id=%x\n",
	    fcport->tgt_id);

	wait_for_completion(&tm_iocb->u.tmf.comp);

	rval = tm_iocb->u.tmf.comp_status == CS_COMPLETE ?
	    QLA_SUCCESS : QLA_FUNCTION_FAILED;

done_free_sp:
	sp->free(vha, sp);
done:
	return rval;
}