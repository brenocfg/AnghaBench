#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct qla_hw_data {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  ref_count; TYPE_1__* fcport; } ;
typedef  TYPE_2__ srb_t ;
struct TYPE_6__ {int /*<<< orphan*/  vha; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 struct scsi_cmnd* GET_CMD_SP (TYPE_2__*) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int ql2xextended_error_logging ; 
 int /*<<< orphan*/  ql_dbg (int,int /*<<< orphan*/ ,int,char*,TYPE_2__*,struct scsi_cmnd*) ; 
 int ql_dbg_io ; 
 int /*<<< orphan*/  qla2x00_sp_free_dma (struct qla_hw_data*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

void
qla2x00_sp_compl(void *data, void *ptr, int res)
{
	struct qla_hw_data *ha = (struct qla_hw_data *)data;
	srb_t *sp = (srb_t*)ptr;
	struct scsi_cmnd *cmd = GET_CMD_SP(sp);

	cmd->result = res;

	if (atomic_read(&sp->ref_count) == 0) {
		ql_dbg(ql_dbg_io, sp->fcport->vha, 0x3015,
		    "SP reference-count to ZERO -- sp=%p cmd=%p.\n",
		    sp, GET_CMD_SP(sp));
		if (ql2xextended_error_logging & ql_dbg_io)
			BUG();
		return;
	}
	if (!atomic_dec_and_test(&sp->ref_count))
		return;

	qla2x00_sp_free_dma(ha, sp);
	cmd->scsi_done(cmd);
}