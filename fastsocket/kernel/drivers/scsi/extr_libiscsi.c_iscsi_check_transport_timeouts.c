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
struct iscsi_session {scalar_t__ state; int /*<<< orphan*/  lock; } ;
struct iscsi_conn {unsigned long recv_timeout; unsigned long last_recv; unsigned long ping_timeout; unsigned long last_ping; int /*<<< orphan*/  transport_timer; struct iscsi_session* session; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  ISCSI_DBG_CONN (struct iscsi_conn*,char*,...) ; 
 int /*<<< orphan*/  ISCSI_ERR_CONN_FAILED ; 
 scalar_t__ ISCSI_STATE_LOGGED_IN ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  iscsi_conn_failure (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,struct iscsi_conn*,char*,unsigned long,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ iscsi_has_ping_timed_out (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsi_send_nopout (struct iscsi_conn*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before_eq (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iscsi_check_transport_timeouts(unsigned long data)
{
	struct iscsi_conn *conn = (struct iscsi_conn *)data;
	struct iscsi_session *session = conn->session;
	unsigned long recv_timeout, next_timeout = 0, last_recv;

	spin_lock(&session->lock);
	if (session->state != ISCSI_STATE_LOGGED_IN)
		goto done;

	recv_timeout = conn->recv_timeout;
	if (!recv_timeout)
		goto done;

	recv_timeout *= HZ;
	last_recv = conn->last_recv;

	if (iscsi_has_ping_timed_out(conn)) {
		iscsi_conn_printk(KERN_ERR, conn, "ping timeout of %d secs "
				  "expired, recv timeout %d, last rx %lu, "
				  "last ping %lu, now %lu\n",
				  conn->ping_timeout, conn->recv_timeout,
				  last_recv, conn->last_ping, jiffies);
		spin_unlock(&session->lock);
		iscsi_conn_failure(conn, ISCSI_ERR_CONN_FAILED);
		return;
	}

	if (time_before_eq(last_recv + recv_timeout, jiffies)) {
		/* send a ping to try to provoke some traffic */
		ISCSI_DBG_CONN(conn, "Sending nopout as ping\n");
		iscsi_send_nopout(conn, NULL);
		next_timeout = conn->last_ping + (conn->ping_timeout * HZ);
	} else
		next_timeout = last_recv + recv_timeout;

	ISCSI_DBG_CONN(conn, "Setting next tmo %lu\n", next_timeout);
	mod_timer(&conn->transport_timer, next_timeout);
done:
	spin_unlock(&session->lock);
}