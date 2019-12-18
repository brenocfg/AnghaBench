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
typedef  unsigned int uint32_t ;
struct iscsi_task {void* last_xfer; } ;
struct iscsi_session {int dummy; } ;
struct iscsi_nopin {int dummy; } ;
struct iscsi_hdr {int opcode; scalar_t__ itt; int /*<<< orphan*/  statsn; int /*<<< orphan*/  ttt; } ;
struct iscsi_conn {int /*<<< orphan*/  cls_conn; int /*<<< orphan*/  exp_statsn; int /*<<< orphan*/  id; void* last_recv; struct iscsi_session* session; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DBG_SESSION (struct iscsi_session*,char*,int,int /*<<< orphan*/ ,unsigned int,int) ; 
 int ISCSI_ERR_BAD_ITT ; 
 int ISCSI_ERR_BAD_OPCODE ; 
 int ISCSI_ERR_CONN_FAILED ; 
 int ISCSI_ERR_PROTO ; 
 int ISCSI_OPCODE_MASK ; 
#define  ISCSI_OP_ASYNC_EVENT 137 
#define  ISCSI_OP_LOGIN_RSP 136 
#define  ISCSI_OP_LOGOUT_RSP 135 
#define  ISCSI_OP_NOOP_IN 134 
#define  ISCSI_OP_R2T 133 
#define  ISCSI_OP_REJECT 132 
#define  ISCSI_OP_SCSI_CMD_RSP 131 
#define  ISCSI_OP_SCSI_DATA_IN 130 
#define  ISCSI_OP_SCSI_TMFUNC_RSP 129 
#define  ISCSI_OP_TEXT_RSP 128 
 int /*<<< orphan*/  ISCSI_RESERVED_TAG ; 
 int /*<<< orphan*/  ISCSI_TASK_COMPLETED ; 
 scalar_t__ RESERVED_ITT ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 unsigned int get_itt (scalar_t__) ; 
 int /*<<< orphan*/  iscsi_complete_task (struct iscsi_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_data_in_rsp (struct iscsi_conn*,struct iscsi_hdr*,struct iscsi_task*) ; 
 int iscsi_handle_reject (struct iscsi_conn*,struct iscsi_hdr*,char*,int) ; 
 struct iscsi_task* iscsi_itt_to_ctask (struct iscsi_conn*,scalar_t__) ; 
 struct iscsi_task* iscsi_itt_to_task (struct iscsi_conn*,scalar_t__) ; 
 int iscsi_nop_out_rsp (struct iscsi_task*,struct iscsi_nopin*,char*,int) ; 
 scalar_t__ iscsi_recv_pdu (int /*<<< orphan*/ ,struct iscsi_hdr*,char*,int) ; 
 int /*<<< orphan*/  iscsi_scsi_cmd_rsp (struct iscsi_conn*,struct iscsi_hdr*,struct iscsi_task*,char*,int) ; 
 int /*<<< orphan*/  iscsi_send_nopout (struct iscsi_conn*,struct iscsi_nopin*) ; 
 int /*<<< orphan*/  iscsi_tmf_rsp (struct iscsi_conn*,struct iscsi_hdr*) ; 
 int /*<<< orphan*/  iscsi_update_cmdsn (struct iscsi_session*,struct iscsi_nopin*) ; 
 int iscsi_verify_itt (struct iscsi_conn*,scalar_t__) ; 
 void* jiffies ; 

int __iscsi_complete_pdu(struct iscsi_conn *conn, struct iscsi_hdr *hdr,
			 char *data, int datalen)
{
	struct iscsi_session *session = conn->session;
	int opcode = hdr->opcode & ISCSI_OPCODE_MASK, rc = 0;
	struct iscsi_task *task;
	uint32_t itt;

	conn->last_recv = jiffies;
	rc = iscsi_verify_itt(conn, hdr->itt);
	if (rc)
		return rc;

	if (hdr->itt != RESERVED_ITT)
		itt = get_itt(hdr->itt);
	else
		itt = ~0U;

	ISCSI_DBG_SESSION(session, "[op 0x%x cid %d itt 0x%x len %d]\n",
			  opcode, conn->id, itt, datalen);

	if (itt == ~0U) {
		iscsi_update_cmdsn(session, (struct iscsi_nopin*)hdr);

		switch(opcode) {
		case ISCSI_OP_NOOP_IN:
			if (datalen) {
				rc = ISCSI_ERR_PROTO;
				break;
			}

			if (hdr->ttt == cpu_to_be32(ISCSI_RESERVED_TAG))
				break;

			iscsi_send_nopout(conn, (struct iscsi_nopin*)hdr);
			break;
		case ISCSI_OP_REJECT:
			rc = iscsi_handle_reject(conn, hdr, data, datalen);
			break;
		case ISCSI_OP_ASYNC_EVENT:
			conn->exp_statsn = be32_to_cpu(hdr->statsn) + 1;
			if (iscsi_recv_pdu(conn->cls_conn, hdr, data, datalen))
				rc = ISCSI_ERR_CONN_FAILED;
			break;
		default:
			rc = ISCSI_ERR_BAD_OPCODE;
			break;
		}
		goto out;
	}

	switch(opcode) {
	case ISCSI_OP_SCSI_CMD_RSP:
	case ISCSI_OP_SCSI_DATA_IN:
		task = iscsi_itt_to_ctask(conn, hdr->itt);
		if (!task)
			return ISCSI_ERR_BAD_ITT;
		task->last_xfer = jiffies;
		break;
	case ISCSI_OP_R2T:
		/*
		 * LLD handles R2Ts if they need to.
		 */
		return 0;
	case ISCSI_OP_LOGOUT_RSP:
	case ISCSI_OP_LOGIN_RSP:
	case ISCSI_OP_TEXT_RSP:
	case ISCSI_OP_SCSI_TMFUNC_RSP:
	case ISCSI_OP_NOOP_IN:
		task = iscsi_itt_to_task(conn, hdr->itt);
		if (!task)
			return ISCSI_ERR_BAD_ITT;
		break;
	default:
		return ISCSI_ERR_BAD_OPCODE;
	}

	switch(opcode) {
	case ISCSI_OP_SCSI_CMD_RSP:
		iscsi_scsi_cmd_rsp(conn, hdr, task, data, datalen);
		break;
	case ISCSI_OP_SCSI_DATA_IN:
		iscsi_data_in_rsp(conn, hdr, task);
		break;
	case ISCSI_OP_LOGOUT_RSP:
		iscsi_update_cmdsn(session, (struct iscsi_nopin*)hdr);
		if (datalen) {
			rc = ISCSI_ERR_PROTO;
			break;
		}
		conn->exp_statsn = be32_to_cpu(hdr->statsn) + 1;
		goto recv_pdu;
	case ISCSI_OP_LOGIN_RSP:
	case ISCSI_OP_TEXT_RSP:
		iscsi_update_cmdsn(session, (struct iscsi_nopin*)hdr);
		/*
		 * login related PDU's exp_statsn is handled in
		 * userspace
		 */
		goto recv_pdu;
	case ISCSI_OP_SCSI_TMFUNC_RSP:
		iscsi_update_cmdsn(session, (struct iscsi_nopin*)hdr);
		if (datalen) {
			rc = ISCSI_ERR_PROTO;
			break;
		}

		iscsi_tmf_rsp(conn, hdr);
		iscsi_complete_task(task, ISCSI_TASK_COMPLETED);
		break;
	case ISCSI_OP_NOOP_IN:
		iscsi_update_cmdsn(session, (struct iscsi_nopin*)hdr);
		if (hdr->ttt != cpu_to_be32(ISCSI_RESERVED_TAG) || datalen) {
			rc = ISCSI_ERR_PROTO;
			break;
		}
		conn->exp_statsn = be32_to_cpu(hdr->statsn) + 1;

		rc = iscsi_nop_out_rsp(task, (struct iscsi_nopin*)hdr,
				       data, datalen);
		break;
	default:
		rc = ISCSI_ERR_BAD_OPCODE;
		break;
	}

out:
	return rc;
recv_pdu:
	if (iscsi_recv_pdu(conn->cls_conn, hdr, data, datalen))
		rc = ISCSI_ERR_CONN_FAILED;
	iscsi_complete_task(task, ISCSI_TASK_COMPLETED);
	return rc;
}