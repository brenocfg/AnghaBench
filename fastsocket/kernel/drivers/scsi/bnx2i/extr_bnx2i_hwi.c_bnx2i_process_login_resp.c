#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iscsi_task {TYPE_2__* hdr; } ;
struct iscsi_session {int /*<<< orphan*/  lock; } ;
struct iscsi_login_rsp {int /*<<< orphan*/  status_detail; int /*<<< orphan*/  status_class; void* max_cmdsn; void* exp_cmdsn; void* statsn; int /*<<< orphan*/  itt; int /*<<< orphan*/  tsih; int /*<<< orphan*/  isid; int /*<<< orphan*/  dlength; scalar_t__ hlength; int /*<<< orphan*/  active_version; int /*<<< orphan*/  max_version; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;
struct iscsi_hdr {int dummy; } ;
struct iscsi_conn {int dummy; } ;
struct cqe {int dummy; } ;
struct bnx2i_login_response {int itt; int data_length; int /*<<< orphan*/  status_detail; int /*<<< orphan*/  status_class; int /*<<< orphan*/  max_cmd_sn; int /*<<< orphan*/  exp_cmd_sn; int /*<<< orphan*/  stat_sn; int /*<<< orphan*/  tsih; int /*<<< orphan*/  isid_lo; int /*<<< orphan*/  version_active; int /*<<< orphan*/  version_max; int /*<<< orphan*/  response_flags; int /*<<< orphan*/  op_code; } ;
struct TYPE_6__ {scalar_t__* resp_buf; scalar_t__* resp_wr_ptr; int /*<<< orphan*/  resp_hdr; } ;
struct bnx2i_conn {TYPE_3__ gen_pdu; TYPE_1__* cls_conn; } ;
struct TYPE_5__ {int /*<<< orphan*/  itt; } ;
struct TYPE_4__ {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int ISCSI_LOGIN_RESPONSE_INDEX ; 
 int /*<<< orphan*/  __iscsi_complete_pdu (struct iscsi_conn*,struct iscsi_hdr*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hton24 (int /*<<< orphan*/ ,int) ; 
 struct iscsi_task* iscsi_itt_to_task (struct iscsi_conn*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct iscsi_login_rsp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2i_process_login_resp(struct iscsi_session *session,
				    struct bnx2i_conn *bnx2i_conn,
				    struct cqe *cqe)
{
	struct iscsi_conn *conn = bnx2i_conn->cls_conn->dd_data;
	struct iscsi_task *task;
	struct bnx2i_login_response *login;
	struct iscsi_login_rsp *resp_hdr;
	int pld_len;
	int pad_len;

	login = (struct bnx2i_login_response *) cqe;
	spin_lock(&session->lock);
	task = iscsi_itt_to_task(conn,
				 login->itt & ISCSI_LOGIN_RESPONSE_INDEX);
	if (!task)
		goto done;

	resp_hdr = (struct iscsi_login_rsp *) &bnx2i_conn->gen_pdu.resp_hdr;
	memset(resp_hdr, 0, sizeof(struct iscsi_hdr));
	resp_hdr->opcode = login->op_code;
	resp_hdr->flags = login->response_flags;
	resp_hdr->max_version = login->version_max;
	resp_hdr->active_version = login->version_active;
	resp_hdr->hlength = 0;

	hton24(resp_hdr->dlength, login->data_length);
	memcpy(resp_hdr->isid, &login->isid_lo, 6);
	resp_hdr->tsih = cpu_to_be16(login->tsih);
	resp_hdr->itt = task->hdr->itt;
	resp_hdr->statsn = cpu_to_be32(login->stat_sn);
	resp_hdr->exp_cmdsn = cpu_to_be32(login->exp_cmd_sn);
	resp_hdr->max_cmdsn = cpu_to_be32(login->max_cmd_sn);
	resp_hdr->status_class = login->status_class;
	resp_hdr->status_detail = login->status_detail;
	pld_len = login->data_length;
	bnx2i_conn->gen_pdu.resp_wr_ptr =
					bnx2i_conn->gen_pdu.resp_buf + pld_len;

	pad_len = 0;
	if (pld_len & 0x3)
		pad_len = 4 - (pld_len % 4);

	if (pad_len) {
		int i = 0;
		for (i = 0; i < pad_len; i++) {
			bnx2i_conn->gen_pdu.resp_wr_ptr[0] = 0;
			bnx2i_conn->gen_pdu.resp_wr_ptr++;
		}
	}

	__iscsi_complete_pdu(conn, (struct iscsi_hdr *)resp_hdr,
		bnx2i_conn->gen_pdu.resp_buf,
		bnx2i_conn->gen_pdu.resp_wr_ptr - bnx2i_conn->gen_pdu.resp_buf);
done:
	spin_unlock(&session->lock);
	return 0;
}