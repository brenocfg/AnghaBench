#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * ptr; } ;
struct scsi_cmnd {void (* scsi_done ) (struct scsi_cmnd*) ;int result; int /*<<< orphan*/ * cmnd; TYPE_3__* device; TYPE_1__ SCp; } ;
struct iscsi_task {int /*<<< orphan*/  running; } ;
struct iscsi_session {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  queued_cmdsn; int /*<<< orphan*/  cmdsn; TYPE_2__* tt; struct iscsi_conn* leadconn; } ;
struct iscsi_host {int /*<<< orphan*/  workq; } ;
struct iscsi_conn {int /*<<< orphan*/  cmdqueue; int /*<<< orphan*/  suspend_tx; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
struct Scsi_Host {int /*<<< orphan*/ * host_lock; } ;
struct TYPE_10__ {int /*<<< orphan*/  length; int /*<<< orphan*/  resid; } ;
struct TYPE_9__ {int /*<<< orphan*/  length; int /*<<< orphan*/  resid; } ;
struct TYPE_8__ {struct Scsi_Host* host; } ;
struct TYPE_7__ {scalar_t__ (* xmit_task ) (struct iscsi_task*) ;} ;

/* Variables and functions */
 int DID_ABORT ; 
 int DID_IMM_RETRY ; 
 int DID_NO_CONNECT ; 
 int DID_REQUEUE ; 
 int DID_TRANSPORT_FAILFAST ; 
 int EACCES ; 
 int ENOMEM ; 
 int FAILURE_OOM ; 
 int FAILURE_SESSION_FREED ; 
 int FAILURE_SESSION_IN_RECOVERY ; 
 int FAILURE_SESSION_LOGGING_OUT ; 
 int FAILURE_SESSION_NOT_READY ; 
 int FAILURE_SESSION_RECOVERY_TIMEOUT ; 
 int FAILURE_SESSION_TERMINATE ; 
 int FAILURE_WINDOW_CLOSED ; 
 int /*<<< orphan*/  ISCSI_DBG_SESSION (struct iscsi_session*,char*,int /*<<< orphan*/ ,int) ; 
#define  ISCSI_STATE_FAILED 132 
#define  ISCSI_STATE_IN_RECOVERY 131 
 int ISCSI_STATE_LOGGED_IN ; 
#define  ISCSI_STATE_LOGGING_OUT 130 
#define  ISCSI_STATE_RECOVERY_FAILED 129 
#define  ISCSI_STATE_TERMINATE 128 
 int /*<<< orphan*/  ISCSI_SUSPEND_BIT ; 
 int /*<<< orphan*/  ISCSI_TASK_COMPLETED ; 
 int SCSI_MLQUEUE_TARGET_BUSY ; 
 struct iscsi_task* iscsi_alloc_task (struct iscsi_conn*,struct scsi_cmnd*) ; 
 scalar_t__ iscsi_check_cmdsn_window_closed (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsi_complete_task (struct iscsi_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_conn_queue_work (struct iscsi_conn*) ; 
 int iscsi_prep_scsi_cmd_pdu (struct iscsi_task*) ; 
 int iscsi_session_chkready (struct iscsi_cls_session*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_bidi_cmnd (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 TYPE_5__* scsi_in (struct scsi_cmnd*) ; 
 TYPE_4__* scsi_out (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_target (TYPE_3__*) ; 
 struct iscsi_host* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct iscsi_cls_session* starget_to_session (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct iscsi_task*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iscsi_queuecommand(struct scsi_cmnd *sc, void (*done)(struct scsi_cmnd *))
{
	struct iscsi_cls_session *cls_session;
	struct Scsi_Host *host;
	struct iscsi_host *ihost;
	int reason = 0;
	struct iscsi_session *session;
	struct iscsi_conn *conn;
	struct iscsi_task *task = NULL;

	sc->scsi_done = done;
	sc->result = 0;
	sc->SCp.ptr = NULL;

	host = sc->device->host;
	ihost = shost_priv(host);
	spin_unlock(host->host_lock);

	cls_session = starget_to_session(scsi_target(sc->device));
	session = cls_session->dd_data;
	spin_lock(&session->lock);

	reason = iscsi_session_chkready(cls_session);
	if (reason) {
		sc->result = reason;
		goto fault;
	}

	if (session->state != ISCSI_STATE_LOGGED_IN) {
		/*
		 * to handle the race between when we set the recovery state
		 * and block the session we requeue here (commands could
		 * be entering our queuecommand while a block is starting
		 * up because the block code is not locked)
		 */
		switch (session->state) {
		case ISCSI_STATE_FAILED:
		case ISCSI_STATE_IN_RECOVERY:
			reason = FAILURE_SESSION_IN_RECOVERY;
			sc->result = DID_IMM_RETRY << 16;
			break;
		case ISCSI_STATE_LOGGING_OUT:
			reason = FAILURE_SESSION_LOGGING_OUT;
			sc->result = DID_IMM_RETRY << 16;
			break;
		case ISCSI_STATE_RECOVERY_FAILED:
			reason = FAILURE_SESSION_RECOVERY_TIMEOUT;
			sc->result = DID_TRANSPORT_FAILFAST << 16;
			break;
		case ISCSI_STATE_TERMINATE:
			reason = FAILURE_SESSION_TERMINATE;
			sc->result = DID_NO_CONNECT << 16;
			break;
		default:
			reason = FAILURE_SESSION_FREED;
			sc->result = DID_NO_CONNECT << 16;
		}
		goto fault;
	}

	conn = session->leadconn;
	if (!conn) {
		reason = FAILURE_SESSION_FREED;
		sc->result = DID_NO_CONNECT << 16;
		goto fault;
	}

	if (test_bit(ISCSI_SUSPEND_BIT, &conn->suspend_tx)) {
		reason = FAILURE_SESSION_IN_RECOVERY;
		sc->result = DID_REQUEUE;
		goto fault;
	}

	if (iscsi_check_cmdsn_window_closed(conn)) {
		reason = FAILURE_WINDOW_CLOSED;
		goto reject;
	}

	task = iscsi_alloc_task(conn, sc);
	if (!task) {
		reason = FAILURE_OOM;
		goto reject;
	}

	if (!ihost->workq) {
		reason = iscsi_prep_scsi_cmd_pdu(task);
		if (reason) {
			if (reason == -ENOMEM ||  reason == -EACCES) {
				reason = FAILURE_OOM;
				goto prepd_reject;
			} else {
				sc->result = DID_ABORT << 16;
				goto prepd_fault;
			}
		}
		if (session->tt->xmit_task(task)) {
			session->cmdsn--;
			reason = FAILURE_SESSION_NOT_READY;
			goto prepd_reject;
		}
	} else {
		list_add_tail(&task->running, &conn->cmdqueue);
		iscsi_conn_queue_work(conn);
	}

	session->queued_cmdsn++;
	spin_unlock(&session->lock);
	spin_lock(host->host_lock);
	return 0;

prepd_reject:
	sc->scsi_done = NULL;
	iscsi_complete_task(task, ISCSI_TASK_COMPLETED);
reject:
	spin_unlock(&session->lock);
	ISCSI_DBG_SESSION(session, "cmd 0x%x rejected (%d)\n",
			  sc->cmnd[0], reason);
	spin_lock(host->host_lock);
	return SCSI_MLQUEUE_TARGET_BUSY;

prepd_fault:
	sc->scsi_done = NULL;
	iscsi_complete_task(task, ISCSI_TASK_COMPLETED);
fault:
	spin_unlock(&session->lock);
	ISCSI_DBG_SESSION(session, "iscsi: cmd 0x%x is not queued (%d)\n",
			  sc->cmnd[0], reason);
	if (!scsi_bidi_cmnd(sc))
		scsi_set_resid(sc, scsi_bufflen(sc));
	else {
		scsi_out(sc)->resid = scsi_out(sc)->length;
		scsi_in(sc)->resid = scsi_in(sc)->length;
	}
	done(sc);
	spin_lock(host->host_lock);
	return 0;
}