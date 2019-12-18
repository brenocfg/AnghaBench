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
struct iscsi_session {int /*<<< orphan*/  lock; } ;
struct iscsi_conn {scalar_t__ tmf_state; int /*<<< orphan*/  ehwait; struct iscsi_session* session; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DBG_EH (struct iscsi_session*,char*) ; 
 scalar_t__ TMF_QUEUED ; 
 scalar_t__ TMF_TIMEDOUT ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iscsi_tmf_timedout(unsigned long data)
{
	struct iscsi_conn *conn = (struct iscsi_conn *)data;
	struct iscsi_session *session = conn->session;

	spin_lock(&session->lock);
	if (conn->tmf_state == TMF_QUEUED) {
		conn->tmf_state = TMF_TIMEDOUT;
		ISCSI_DBG_EH(session, "tmf timedout\n");
		/* unblock eh_abort() */
		wake_up(&conn->ehwait);
	}
	spin_unlock(&session->lock);
}