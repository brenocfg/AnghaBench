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
struct smb_rqst {int dummy; } ;
struct mid_q_entry {int /*<<< orphan*/  qhead; int /*<<< orphan*/  mid_state; void* callback_data; int /*<<< orphan*/ * callback; int /*<<< orphan*/ * receive; } ;
struct TCP_Server_Info {int sequence_number; int /*<<< orphan*/  request_q; int /*<<< orphan*/  srv_mutex; int /*<<< orphan*/  pending_mid_q; } ;
typedef  int /*<<< orphan*/  mid_receive_t ;
typedef  int /*<<< orphan*/  mid_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_ASYNC_OP ; 
 int /*<<< orphan*/  GlobalMid_Lock ; 
 scalar_t__ IS_ERR (struct mid_q_entry*) ; 
 int /*<<< orphan*/  MID_REQUEST_SUBMITTED ; 
 int PTR_ERR (struct mid_q_entry*) ; 
 int /*<<< orphan*/  cifs_add_credits (struct TCP_Server_Info*,int) ; 
 int /*<<< orphan*/  cifs_in_send_dec (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  cifs_in_send_inc (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  cifs_save_when_sent (struct mid_q_entry*) ; 
 struct mid_q_entry* cifs_setup_async_request (struct TCP_Server_Info*,struct smb_rqst*) ; 
 int /*<<< orphan*/  delete_mid (struct mid_q_entry*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int smb_send_rqst (struct TCP_Server_Info*,struct smb_rqst*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_free_request (struct TCP_Server_Info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int
cifs_call_async(struct TCP_Server_Info *server, struct smb_rqst *rqst,
		mid_receive_t *receive, mid_callback_t *callback,
		void *cbdata, bool ignore_pend)
{
	int rc;
	struct mid_q_entry *mid;

	rc = wait_for_free_request(server, ignore_pend ? CIFS_ASYNC_OP : 0);
	if (rc)
		return rc;

	mutex_lock(&server->srv_mutex);
	mid = cifs_setup_async_request(server, rqst);
	if (IS_ERR(mid)) {
		mutex_unlock(&server->srv_mutex);
		cifs_add_credits(server, 1);
		wake_up(&server->request_q);
		return PTR_ERR(mid);
	}

	mid->receive = receive;
	mid->callback = callback;
	mid->callback_data = cbdata;
	mid->mid_state = MID_REQUEST_SUBMITTED;

	/* put it on the pending_mid_q */
	spin_lock(&GlobalMid_Lock);
	list_add_tail(&mid->qhead, &server->pending_mid_q);
	spin_unlock(&GlobalMid_Lock);

	cifs_in_send_inc(server);
	rc = smb_send_rqst(server, rqst);
	cifs_in_send_dec(server);
	cifs_save_when_sent(mid);

	if (rc < 0)
		server->sequence_number -= 2;
	mutex_unlock(&server->srv_mutex);

	if (rc == 0)
		return 0;

	delete_mid(mid);
	cifs_add_credits(server, 1);
	wake_up(&server->request_q);
	return rc;
}