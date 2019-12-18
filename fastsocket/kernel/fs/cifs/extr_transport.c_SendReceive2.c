#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct smb_rqst {int rq_nvec; struct kvec* rq_iov; } ;
struct smb_hdr {int dummy; } ;
struct mid_q_entry {scalar_t__ mid_state; int /*<<< orphan*/ * resp_buf; scalar_t__ large_buf; int /*<<< orphan*/  callback; } ;
struct kvec {char* iov_base; scalar_t__ iov_len; } ;
struct cifs_ses {TYPE_1__* server; } ;
struct TYPE_10__ {scalar_t__ tcpStatus; int sequence_number; int /*<<< orphan*/  srv_mutex; } ;

/* Variables and functions */
 int CIFS_ASYNC_OP ; 
 int CIFS_LARGE_BUFFER ; 
 int const CIFS_LOG_ERROR ; 
 int CIFS_NO_BUFFER ; 
 int const CIFS_NO_RESP ; 
 int CIFS_SMALL_BUFFER ; 
 int const CIFS_TIMEOUT_MASK ; 
 scalar_t__ CifsExiting ; 
 int /*<<< orphan*/  DeleteMidQEntry ; 
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  GlobalMid_Lock ; 
 scalar_t__ IS_ERR (struct mid_q_entry*) ; 
 scalar_t__ MID_REQUEST_SUBMITTED ; 
 scalar_t__ MID_RESPONSE_RECEIVED ; 
 int PTR_ERR (struct mid_q_entry*) ; 
 int /*<<< orphan*/  cERROR (int,char*) ; 
 int /*<<< orphan*/  cFYI (int,char*) ; 
 int /*<<< orphan*/  cifs_add_credits (TYPE_1__*,int) ; 
 int cifs_check_receive (struct mid_q_entry*,TYPE_1__*,int const) ; 
 int /*<<< orphan*/  cifs_in_send_dec (TYPE_1__*) ; 
 int /*<<< orphan*/  cifs_in_send_inc (TYPE_1__*) ; 
 int /*<<< orphan*/  cifs_save_when_sent (struct mid_q_entry*) ; 
 struct mid_q_entry* cifs_setup_request (struct cifs_ses*,struct smb_rqst*) ; 
 int /*<<< orphan*/  cifs_small_buf_release (char*) ; 
 int cifs_sync_mid_result (struct mid_q_entry*,TYPE_1__*) ; 
 int /*<<< orphan*/  delete_mid (struct mid_q_entry*) ; 
 scalar_t__ get_rfc1002_length (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_nt_cancel (TYPE_1__*,struct smb_hdr*,struct mid_q_entry*) ; 
 int smb_sendv (TYPE_1__*,struct kvec*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_free_request (TYPE_1__*,int) ; 
 int wait_for_response (TYPE_1__*,struct mid_q_entry*) ; 

int
SendReceive2(const unsigned int xid, struct cifs_ses *ses,
	     struct kvec *iov, int n_vec, int *pRespBufType /* ret */,
	     const int flags)
{
	int rc = 0;
	int long_op;
	struct mid_q_entry *midQ;
	char *buf = iov[0].iov_base;
	struct smb_rqst rqst = { .rq_iov = iov,
				 .rq_nvec = n_vec };

	long_op = flags & CIFS_TIMEOUT_MASK;

	*pRespBufType = CIFS_NO_BUFFER;  /* no response buf yet */

	if ((ses == NULL) || (ses->server == NULL)) {
		cifs_small_buf_release(buf);
		cERROR(1, "Null session");
		return -EIO;
	}

	if (ses->server->tcpStatus == CifsExiting) {
		cifs_small_buf_release(buf);
		return -ENOENT;
	}

	/*
	 * Ensure that we do not send more than 50 overlapping requests
	 * to the same server. We may make this configurable later or
	 * use ses->maxReq.
	 */

	rc = wait_for_free_request(ses->server, long_op);
	if (rc) {
		cifs_small_buf_release(buf);
		return rc;
	}

	/*
	 * Make sure that we sign in the same order that we send on this socket
	 * and avoid races inside tcp sendmsg code that could cause corruption
	 * of smb data.
	 */

	mutex_lock(&ses->server->srv_mutex);

	midQ = cifs_setup_request(ses, &rqst);
	if (IS_ERR(midQ)) {
		mutex_unlock(&ses->server->srv_mutex);
		cifs_small_buf_release(buf);
		/* Update # of requests on wire to server */
		cifs_add_credits(ses->server, 1);
		return PTR_ERR(midQ);
	}

	midQ->mid_state = MID_REQUEST_SUBMITTED;
	cifs_in_send_inc(ses->server);
	rc = smb_sendv(ses->server, iov, n_vec);
	cifs_in_send_dec(ses->server);
	cifs_save_when_sent(midQ);

	if (rc < 0)
		ses->server->sequence_number -= 2;
	mutex_unlock(&ses->server->srv_mutex);

	if (rc < 0) {
		cifs_small_buf_release(buf);
		goto out;
	}

	if (long_op == CIFS_ASYNC_OP) {
		cifs_small_buf_release(buf);
		goto out;
	}

	rc = wait_for_response(ses->server, midQ);
	if (rc != 0) {
		send_nt_cancel(ses->server, (struct smb_hdr *)buf, midQ);
		spin_lock(&GlobalMid_Lock);
		if (midQ->mid_state == MID_REQUEST_SUBMITTED) {
			midQ->callback = DeleteMidQEntry;
			spin_unlock(&GlobalMid_Lock);
			cifs_small_buf_release(buf);
			cifs_add_credits(ses->server, 1);
			return rc;
		}
		spin_unlock(&GlobalMid_Lock);
	}

	cifs_small_buf_release(buf);

	rc = cifs_sync_mid_result(midQ, ses->server);
	if (rc != 0) {
		cifs_add_credits(ses->server, 1);
		return rc;
	}

	if (!midQ->resp_buf || midQ->mid_state != MID_RESPONSE_RECEIVED) {
		rc = -EIO;
		cFYI(1, "Bad MID state?");
		goto out;
	}

	buf = (char *)midQ->resp_buf;
	iov[0].iov_base = buf;
	iov[0].iov_len = get_rfc1002_length(buf) + 4;
	if (midQ->large_buf)
		*pRespBufType = CIFS_LARGE_BUFFER;
	else
		*pRespBufType = CIFS_SMALL_BUFFER;

	rc = cifs_check_receive(midQ, ses->server, flags & CIFS_LOG_ERROR);

	/* mark it so buf will not be freed by delete_mid */
	if ((flags & CIFS_NO_RESP) == 0)
		midQ->resp_buf = NULL;
out:
	delete_mid(midQ);
	cifs_add_credits(ses->server, 1);

	return rc;
}