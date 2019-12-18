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
struct cmtp_session {int /*<<< orphan*/  terminate; int /*<<< orphan*/  transmit; } ;
struct cmtp_conndel_req {int /*<<< orphan*/  bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int ENOENT ; 
 struct cmtp_session* __cmtp_get_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmtp_schedule (struct cmtp_session*) ; 
 int /*<<< orphan*/  cmtp_session_sem ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int cmtp_del_connection(struct cmtp_conndel_req *req)
{
	struct cmtp_session *session;
	int err = 0;

	BT_DBG("");

	down_read(&cmtp_session_sem);

	session = __cmtp_get_session(&req->bdaddr);
	if (session) {
		/* Flush the transmit queue */
		skb_queue_purge(&session->transmit);

		/* Kill session thread */
		atomic_inc(&session->terminate);
		cmtp_schedule(session);
	} else
		err = -ENOENT;

	up_read(&cmtp_session_sem);
	return err;
}