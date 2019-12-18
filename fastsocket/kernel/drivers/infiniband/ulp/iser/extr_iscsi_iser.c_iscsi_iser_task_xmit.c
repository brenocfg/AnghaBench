#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  data_length; } ;
struct iscsi_task {int /*<<< orphan*/  itt; TYPE_1__ unsol_r2t; int /*<<< orphan*/  imm_count; TYPE_2__* sc; struct iscsi_iser_task* dd_data; struct iscsi_conn* conn; } ;
struct iscsi_iser_task {int command_sent; } ;
struct iscsi_conn {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {scalar_t__ sc_data_direction; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int iscsi_iser_mtask_xmit (struct iscsi_conn*,struct iscsi_task*) ; 
 int iscsi_iser_task_xmit_unsol_data (struct iscsi_conn*,struct iscsi_task*) ; 
 scalar_t__ iscsi_task_has_unsol_data (struct iscsi_task*) ; 
 int /*<<< orphan*/  iser_dbg (char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int iser_send_command (struct iscsi_conn*,struct iscsi_task*) ; 
 scalar_t__ scsi_bufflen (TYPE_2__*) ; 

__attribute__((used)) static int
iscsi_iser_task_xmit(struct iscsi_task *task)
{
	struct iscsi_conn *conn = task->conn;
	struct iscsi_iser_task *iser_task = task->dd_data;
	int error = 0;

	if (!task->sc)
		return iscsi_iser_mtask_xmit(conn, task);

	if (task->sc->sc_data_direction == DMA_TO_DEVICE) {
		BUG_ON(scsi_bufflen(task->sc) == 0);

		iser_dbg("cmd [itt %x total %d imm %d unsol_data %d\n",
			   task->itt, scsi_bufflen(task->sc),
			   task->imm_count, task->unsol_r2t.data_length);
	}

	iser_dbg("ctask xmit [cid %d itt 0x%x]\n",
		   conn->id, task->itt);

	/* Send the cmd PDU */
	if (!iser_task->command_sent) {
		error = iser_send_command(conn, task);
		if (error)
			goto iscsi_iser_task_xmit_exit;
		iser_task->command_sent = 1;
	}

	/* Send unsolicited data-out PDU(s) if necessary */
	if (iscsi_task_has_unsol_data(task))
		error = iscsi_iser_task_xmit_unsol_data(conn, task);

 iscsi_iser_task_xmit_exit:
	return error;
}