#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct iscsi_r2t_info {scalar_t__ sent; scalar_t__ data_length; scalar_t__ data_count; int /*<<< orphan*/  datasn; } ;
struct iscsi_task {struct iscsi_r2t_info unsol_r2t; } ;
struct iscsi_data {int /*<<< orphan*/  itt; } ;
struct iscsi_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsi_prep_data_out_pdu (struct iscsi_task*,struct iscsi_r2t_info*,struct iscsi_data*) ; 
 scalar_t__ iscsi_task_has_unsol_data (struct iscsi_task*) ; 
 int /*<<< orphan*/  iser_dbg (char*,scalar_t__,...) ; 
 int iser_send_data_out (struct iscsi_conn*,struct iscsi_task*,struct iscsi_data*) ; 

__attribute__((used)) static int
iscsi_iser_task_xmit_unsol_data(struct iscsi_conn *conn,
				 struct iscsi_task *task)
{
	struct iscsi_r2t_info *r2t = &task->unsol_r2t;
	struct iscsi_data hdr;
	int error = 0;

	/* Send data-out PDUs while there's still unsolicited data to send */
	while (iscsi_task_has_unsol_data(task)) {
		iscsi_prep_data_out_pdu(task, r2t, &hdr);
		iser_dbg("Sending data-out: itt 0x%x, data count %d\n",
			   hdr.itt, r2t->data_count);

		/* the buffer description has been passed with the command */
		/* Send the command */
		error = iser_send_data_out(conn, task, &hdr);
		if (error) {
			r2t->datasn--;
			goto iscsi_iser_task_xmit_unsol_data_exit;
		}
		r2t->sent += r2t->data_count;
		iser_dbg("Need to send %d more as data-out PDUs\n",
			   r2t->data_length - r2t->sent);
	}

iscsi_iser_task_xmit_unsol_data_exit:
	return error;
}