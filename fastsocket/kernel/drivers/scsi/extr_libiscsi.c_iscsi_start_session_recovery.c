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
struct iscsi_session {scalar_t__ state; int /*<<< orphan*/  eh_mutex; int /*<<< orphan*/  lock; int /*<<< orphan*/  cls_session; } ;
struct iscsi_conn {int stop_stage; int /*<<< orphan*/  tmhdr; scalar_t__ datadgst_en; scalar_t__ hdrdgst_en; int /*<<< orphan*/  c_stage; int /*<<< orphan*/  transport_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DID_TRANSPORT_DISRUPTED ; 
 int /*<<< orphan*/  ISCSI_CONN_STOPPED ; 
 int /*<<< orphan*/  ISCSI_DBG_SESSION (struct iscsi_session*,char*) ; 
 scalar_t__ ISCSI_STATE_IN_RECOVERY ; 
 scalar_t__ ISCSI_STATE_TERMINATE ; 
 int STOP_CONN_RECOVER ; 
 int STOP_CONN_TERM ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fail_mgmt_tasks (struct iscsi_session*,struct iscsi_conn*) ; 
 int /*<<< orphan*/  fail_scsi_tasks (struct iscsi_conn*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_block_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_suspend_tx (struct iscsi_conn*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iscsi_start_session_recovery(struct iscsi_session *session,
					 struct iscsi_conn *conn, int flag)
{
	int old_stop_stage;

	mutex_lock(&session->eh_mutex);
	spin_lock_bh(&session->lock);
	if (conn->stop_stage == STOP_CONN_TERM) {
		spin_unlock_bh(&session->lock);
		mutex_unlock(&session->eh_mutex);
		return;
	}

	/*
	 * When this is called for the in_login state, we only want to clean
	 * up the login task and connection. We do not need to block and set
	 * the recovery state again
	 */
	if (flag == STOP_CONN_TERM)
		session->state = ISCSI_STATE_TERMINATE;
	else if (conn->stop_stage != STOP_CONN_RECOVER)
		session->state = ISCSI_STATE_IN_RECOVERY;

	old_stop_stage = conn->stop_stage;
	conn->stop_stage = flag;
	spin_unlock_bh(&session->lock);

	del_timer_sync(&conn->transport_timer);
	iscsi_suspend_tx(conn);

	spin_lock_bh(&session->lock);
	conn->c_stage = ISCSI_CONN_STOPPED;
	spin_unlock_bh(&session->lock);

	/*
	 * for connection level recovery we should not calculate
	 * header digest. conn->hdr_size used for optimization
	 * in hdr_extract() and will be re-negotiated at
	 * set_param() time.
	 */
	if (flag == STOP_CONN_RECOVER) {
		conn->hdrdgst_en = 0;
		conn->datadgst_en = 0;
		if (session->state == ISCSI_STATE_IN_RECOVERY &&
		    old_stop_stage != STOP_CONN_RECOVER) {
			ISCSI_DBG_SESSION(session, "blocking session\n");
			iscsi_block_session(session->cls_session);
		}
	}

	/*
	 * flush queues.
	 */
	spin_lock_bh(&session->lock);
	fail_scsi_tasks(conn, -1, DID_TRANSPORT_DISRUPTED);
	fail_mgmt_tasks(session, conn);
	memset(&conn->tmhdr, 0, sizeof(conn->tmhdr));
	spin_unlock_bh(&session->lock);
	mutex_unlock(&session->eh_mutex);
}