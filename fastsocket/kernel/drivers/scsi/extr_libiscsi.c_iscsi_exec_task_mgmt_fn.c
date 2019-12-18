#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iscsi_tm {int dummy; } ;
struct iscsi_task {int dummy; } ;
struct iscsi_session {int age; scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  eh_mutex; } ;
struct iscsi_hdr {int dummy; } ;
struct TYPE_3__ {unsigned long data; int /*<<< orphan*/  function; scalar_t__ expires; } ;
struct iscsi_conn {scalar_t__ tmf_state; TYPE_1__ tmf_timer; int /*<<< orphan*/  ehwait; int /*<<< orphan*/  tmfcmd_pdus_cnt; struct iscsi_session* session; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int EPERM ; 
 int HZ ; 
 int /*<<< orphan*/  ISCSI_DBG_EH (struct iscsi_session*,char*) ; 
 int /*<<< orphan*/  ISCSI_ERR_CONN_FAILED ; 
 scalar_t__ ISCSI_STATE_LOGGED_IN ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ TMF_QUEUED ; 
 struct iscsi_task* __iscsi_conn_send_pdu (struct iscsi_conn*,struct iscsi_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  flush_signals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_conn_failure (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,struct iscsi_conn*,char*) ; 
 int /*<<< orphan*/  iscsi_tmf_timedout ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iscsi_exec_task_mgmt_fn(struct iscsi_conn *conn,
				   struct iscsi_tm *hdr, int age,
				   int timeout)
{
	struct iscsi_session *session = conn->session;
	struct iscsi_task *task;

	task = __iscsi_conn_send_pdu(conn, (struct iscsi_hdr *)hdr,
				      NULL, 0);
	if (!task) {
		spin_unlock_bh(&session->lock);
		iscsi_conn_printk(KERN_ERR, conn, "Could not send TMF.\n");
		iscsi_conn_failure(conn, ISCSI_ERR_CONN_FAILED);
		spin_lock_bh(&session->lock);
		return -EPERM;
	}
	conn->tmfcmd_pdus_cnt++;
	conn->tmf_timer.expires = timeout * HZ + jiffies;
	conn->tmf_timer.function = iscsi_tmf_timedout;
	conn->tmf_timer.data = (unsigned long)conn;
	add_timer(&conn->tmf_timer);
	ISCSI_DBG_EH(session, "tmf set timeout\n");

	spin_unlock_bh(&session->lock);
	mutex_unlock(&session->eh_mutex);

	/*
	 * block eh thread until:
	 *
	 * 1) tmf response
	 * 2) tmf timeout
	 * 3) session is terminated or restarted or userspace has
	 * given up on recovery
	 */
	wait_event_interruptible(conn->ehwait, age != session->age ||
				 session->state != ISCSI_STATE_LOGGED_IN ||
				 conn->tmf_state != TMF_QUEUED);
	if (signal_pending(current))
		flush_signals(current);
	del_timer_sync(&conn->tmf_timer);

	mutex_lock(&session->eh_mutex);
	spin_lock_bh(&session->lock);
	/* if the session drops it will clean up the task */
	if (age != session->age ||
	    session->state != ISCSI_STATE_LOGGED_IN)
		return -ENOTCONN;
	return 0;
}