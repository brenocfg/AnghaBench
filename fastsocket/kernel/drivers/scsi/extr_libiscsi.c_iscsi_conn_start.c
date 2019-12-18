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
struct iscsi_session {scalar_t__ first_burst; scalar_t__ max_burst; int age; int /*<<< orphan*/  cls_session; int /*<<< orphan*/  lock; int /*<<< orphan*/  cmdsn; int /*<<< orphan*/  queued_cmdsn; int /*<<< orphan*/  state; int /*<<< orphan*/  initial_r2t_en; scalar_t__ imm_data_en; } ;
struct iscsi_conn {int ping_timeout; int recv_timeout; int stop_stage; int /*<<< orphan*/  ehwait; int /*<<< orphan*/  tmf_state; int /*<<< orphan*/  transport_timer; void* last_ping; void* last_recv; int /*<<< orphan*/  c_stage; struct iscsi_session* session; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int HZ ; 
 int /*<<< orphan*/  ISCSI_CONN_STARTED ; 
 int /*<<< orphan*/  ISCSI_STATE_LOGGED_IN ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
#define  STOP_CONN_RECOVER 129 
#define  STOP_CONN_TERM 128 
 int /*<<< orphan*/  TMF_INITIAL ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,struct iscsi_conn*,char*,...) ; 
 int /*<<< orphan*/  iscsi_unblock_session (int /*<<< orphan*/ ) ; 
 void* jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int iscsi_conn_start(struct iscsi_cls_conn *cls_conn)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct iscsi_session *session = conn->session;

	if (!session) {
		iscsi_conn_printk(KERN_ERR, conn,
				  "can't start unbound connection\n");
		return -EPERM;
	}

	if ((session->imm_data_en || !session->initial_r2t_en) &&
	     session->first_burst > session->max_burst) {
		iscsi_conn_printk(KERN_INFO, conn, "invalid burst lengths: "
				  "first_burst %d max_burst %d\n",
				  session->first_burst, session->max_burst);
		return -EINVAL;
	}

	if (conn->ping_timeout && !conn->recv_timeout) {
		iscsi_conn_printk(KERN_ERR, conn, "invalid recv timeout of "
				  "zero. Using 5 seconds\n.");
		conn->recv_timeout = 5;
	}

	if (conn->recv_timeout && !conn->ping_timeout) {
		iscsi_conn_printk(KERN_ERR, conn, "invalid ping timeout of "
				  "zero. Using 5 seconds.\n");
		conn->ping_timeout = 5;
	}

	spin_lock_bh(&session->lock);
	conn->c_stage = ISCSI_CONN_STARTED;
	session->state = ISCSI_STATE_LOGGED_IN;
	session->queued_cmdsn = session->cmdsn;

	conn->last_recv = jiffies;
	conn->last_ping = jiffies;
	if (conn->recv_timeout && conn->ping_timeout)
		mod_timer(&conn->transport_timer,
			  jiffies + (conn->recv_timeout * HZ));

	switch(conn->stop_stage) {
	case STOP_CONN_RECOVER:
		/*
		 * unblock eh_abort() if it is blocked. re-try all
		 * commands after successful recovery
		 */
		conn->stop_stage = 0;
		conn->tmf_state = TMF_INITIAL;
		session->age++;
		if (session->age == 16)
			session->age = 0;
		break;
	case STOP_CONN_TERM:
		conn->stop_stage = 0;
		break;
	default:
		break;
	}
	spin_unlock_bh(&session->lock);

	iscsi_unblock_session(session->cls_session);
	wake_up(&conn->ehwait);
	return 0;
}