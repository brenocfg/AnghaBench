#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int dummy; } ;
struct iser_tx_desc {int /*<<< orphan*/  type; } ;
struct iser_data_buf {int /*<<< orphan*/  data_len; scalar_t__ size; int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {scalar_t__ data_length; } ;
struct iscsi_task {int /*<<< orphan*/  itt; TYPE_1__ unsol_r2t; scalar_t__ imm_count; struct scsi_cmnd* sc; scalar_t__ hdr; struct iscsi_iser_task* dd_data; } ;
struct iscsi_iser_task {int /*<<< orphan*/  status; struct iser_data_buf* data; struct iser_tx_desc desc; } ;
struct iscsi_iser_conn {int /*<<< orphan*/  ib_conn; } ;
struct iscsi_conn {struct iscsi_iser_conn* dd_data; } ;
struct iscsi_cmd {int flags; int /*<<< orphan*/  data_length; } ;

/* Variables and functions */
 int ISCSI_FLAG_CMD_READ ; 
 int ISCSI_FLAG_CMD_WRITE ; 
 int /*<<< orphan*/  ISCSI_TX_SCSI_COMMAND ; 
 size_t ISER_DIR_IN ; 
 size_t ISER_DIR_OUT ; 
 int /*<<< orphan*/  ISER_TASK_STATUS_STARTED ; 
 int /*<<< orphan*/  iser_create_send_desc (int /*<<< orphan*/ ,struct iser_tx_desc*) ; 
 int /*<<< orphan*/  iser_err (char*,struct iscsi_conn*,int /*<<< orphan*/ ,int) ; 
 int iser_post_send (int /*<<< orphan*/ ,struct iser_tx_desc*) ; 
 int iser_prepare_read_cmd (struct iscsi_task*,unsigned long) ; 
 int iser_prepare_write_cmd (struct iscsi_task*,scalar_t__,scalar_t__,unsigned long) ; 
 unsigned long ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 scalar_t__ scsi_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 

int iser_send_command(struct iscsi_conn *conn,
		      struct iscsi_task *task)
{
	struct iscsi_iser_conn *iser_conn = conn->dd_data;
	struct iscsi_iser_task *iser_task = task->dd_data;
	unsigned long edtl;
	int err;
	struct iser_data_buf *data_buf;
	struct iscsi_cmd *hdr =  (struct iscsi_cmd *)task->hdr;
	struct scsi_cmnd *sc  =  task->sc;
	struct iser_tx_desc *tx_desc = &iser_task->desc;

	edtl = ntohl(hdr->data_length);

	/* build the tx desc regd header and add it to the tx desc dto */
	tx_desc->type = ISCSI_TX_SCSI_COMMAND;
	iser_create_send_desc(iser_conn->ib_conn, tx_desc);

	if (hdr->flags & ISCSI_FLAG_CMD_READ)
		data_buf = &iser_task->data[ISER_DIR_IN];
	else
		data_buf = &iser_task->data[ISER_DIR_OUT];

	if (scsi_sg_count(sc)) { /* using a scatter list */
		data_buf->buf  = scsi_sglist(sc);
		data_buf->size = scsi_sg_count(sc);
	}

	data_buf->data_len = scsi_bufflen(sc);

	if (hdr->flags & ISCSI_FLAG_CMD_READ) {
		err = iser_prepare_read_cmd(task, edtl);
		if (err)
			goto send_command_error;
	}
	if (hdr->flags & ISCSI_FLAG_CMD_WRITE) {
		err = iser_prepare_write_cmd(task,
					     task->imm_count,
				             task->imm_count +
					     task->unsol_r2t.data_length,
					     edtl);
		if (err)
			goto send_command_error;
	}

	iser_task->status = ISER_TASK_STATUS_STARTED;

	err = iser_post_send(iser_conn->ib_conn, tx_desc);
	if (!err)
		return 0;

send_command_error:
	iser_err("conn %p failed task->itt %d err %d\n",conn, task->itt, err);
	return err;
}