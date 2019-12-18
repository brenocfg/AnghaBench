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
struct TYPE_2__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct scsi_data_buffer {TYPE_1__ table; } ;
struct iscsi_task {int /*<<< orphan*/  sc; int /*<<< orphan*/  data; int /*<<< orphan*/  hdr_len; int /*<<< orphan*/  hdr; struct iscsi_conn* conn; } ;
struct iscsi_conn {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int iscsi_sw_tcp_send_data_prep (struct iscsi_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  iscsi_sw_tcp_send_hdr_prep (struct iscsi_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_sw_tcp_send_linear_data_prep (struct iscsi_conn*,int /*<<< orphan*/ ,unsigned int) ; 
 struct scsi_data_buffer* scsi_out (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsi_sw_tcp_pdu_init(struct iscsi_task *task,
				 unsigned int offset, unsigned int count)
{
	struct iscsi_conn *conn = task->conn;
	int err = 0;

	iscsi_sw_tcp_send_hdr_prep(conn, task->hdr, task->hdr_len);

	if (!count)
		return 0;

	if (!task->sc)
		iscsi_sw_tcp_send_linear_data_prep(conn, task->data, count);
	else {
		struct scsi_data_buffer *sdb = scsi_out(task->sc);

		err = iscsi_sw_tcp_send_data_prep(conn, sdb->table.sgl,
						  sdb->table.nents, offset,
						  count);
	}

	if (err) {
		/* got invalid offset/len */
		return -EIO;
	}
	return 0;
}