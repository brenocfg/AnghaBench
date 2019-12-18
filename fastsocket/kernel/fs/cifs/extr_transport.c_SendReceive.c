#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct smb_hdr {int /*<<< orphan*/  smb_buf_length; } ;
struct mid_q_entry {scalar_t__ mid_state; int /*<<< orphan*/  resp_buf; int /*<<< orphan*/  callback; int /*<<< orphan*/  sequence_number; } ;
struct cifs_ses {TYPE_1__* server; } ;
struct TYPE_11__ {scalar_t__ tcpStatus; int sequence_number; int /*<<< orphan*/  srv_mutex; } ;

/* Variables and functions */
 int CIFSMaxBufSize ; 
 int const CIFS_ASYNC_OP ; 
 scalar_t__ CifsExiting ; 
 int /*<<< orphan*/  DeleteMidQEntry ; 
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  GlobalMid_Lock ; 
 int MAX_CIFS_HDR_SIZE ; 
 scalar_t__ MID_REQUEST_SUBMITTED ; 
 scalar_t__ MID_RESPONSE_RECEIVED ; 
 int allocate_mid (struct cifs_ses*,struct smb_hdr*,struct mid_q_entry**) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cERROR (int,char*,...) ; 
 int /*<<< orphan*/  cifs_add_credits (TYPE_1__*,int) ; 
 int cifs_check_receive (struct mid_q_entry*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_in_send_dec (TYPE_1__*) ; 
 int /*<<< orphan*/  cifs_in_send_inc (TYPE_1__*) ; 
 int /*<<< orphan*/  cifs_save_when_sent (struct mid_q_entry*) ; 
 int cifs_sign_smb (struct smb_hdr*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int cifs_sync_mid_result (struct mid_q_entry*,TYPE_1__*) ; 
 int /*<<< orphan*/  delete_mid (struct mid_q_entry*) ; 
 int get_rfc1002_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct smb_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_nt_cancel (TYPE_1__*,struct smb_hdr*,struct mid_q_entry*) ; 
 int smb_send (TYPE_1__*,struct smb_hdr*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_free_request (TYPE_1__*,int const) ; 
 int wait_for_response (TYPE_1__*,struct mid_q_entry*) ; 

int
SendReceive(const unsigned int xid, struct cifs_ses *ses,
	    struct smb_hdr *in_buf, struct smb_hdr *out_buf,
	    int *pbytes_returned, const int long_op)
{
	int rc = 0;
	struct mid_q_entry *midQ;

	if (ses == NULL) {
		cERROR(1, "Null smb session");
		return -EIO;
	}
	if (ses->server == NULL) {
		cERROR(1, "Null tcp session");
		return -EIO;
	}

	if (ses->server->tcpStatus == CifsExiting)
		return -ENOENT;

	/* Ensure that we do not send more than 50 overlapping requests
	   to the same server. We may make this configurable later or
	   use ses->maxReq */

	if (be32_to_cpu(in_buf->smb_buf_length) > CIFSMaxBufSize +
			MAX_CIFS_HDR_SIZE - 4) {
		cERROR(1, "Illegal length, greater than maximum frame, %d",
			   be32_to_cpu(in_buf->smb_buf_length));
		return -EIO;
	}

	rc = wait_for_free_request(ses->server, long_op);
	if (rc)
		return rc;

	/* make sure that we sign in the same order that we send on this socket
	   and avoid races inside tcp sendmsg code that could cause corruption
	   of smb data */

	mutex_lock(&ses->server->srv_mutex);

	rc = allocate_mid(ses, in_buf, &midQ);
	if (rc) {
		mutex_unlock(&ses->server->srv_mutex);
		/* Update # of requests on wire to server */
		cifs_add_credits(ses->server, 1);
		return rc;
	}

	rc = cifs_sign_smb(in_buf, ses->server, &midQ->sequence_number);
	if (rc) {
		mutex_unlock(&ses->server->srv_mutex);
		goto out;
	}

	midQ->mid_state = MID_REQUEST_SUBMITTED;

	cifs_in_send_inc(ses->server);
	rc = smb_send(ses->server, in_buf, be32_to_cpu(in_buf->smb_buf_length));
	cifs_in_send_dec(ses->server);
	cifs_save_when_sent(midQ);

	if (rc < 0)
		ses->server->sequence_number -= 2;

	mutex_unlock(&ses->server->srv_mutex);

	if (rc < 0)
		goto out;

	if (long_op == CIFS_ASYNC_OP)
		goto out;

	rc = wait_for_response(ses->server, midQ);
	if (rc != 0) {
		send_nt_cancel(ses->server, in_buf, midQ);
		spin_lock(&GlobalMid_Lock);
		if (midQ->mid_state == MID_REQUEST_SUBMITTED) {
			/* no longer considered to be "in-flight" */
			midQ->callback = DeleteMidQEntry;
			spin_unlock(&GlobalMid_Lock);
			cifs_add_credits(ses->server, 1);
			return rc;
		}
		spin_unlock(&GlobalMid_Lock);
	}

	rc = cifs_sync_mid_result(midQ, ses->server);
	if (rc != 0) {
		cifs_add_credits(ses->server, 1);
		return rc;
	}

	if (!midQ->resp_buf || !out_buf ||
	    midQ->mid_state != MID_RESPONSE_RECEIVED) {
		rc = -EIO;
		cERROR(1, "Bad MID state?");
		goto out;
	}

	*pbytes_returned = get_rfc1002_length(midQ->resp_buf);
	memcpy(out_buf, midQ->resp_buf, *pbytes_returned + 4);
	rc = cifs_check_receive(midQ, ses->server, 0);
out:
	delete_mid(midQ);
	cifs_add_credits(ses->server, 1);

	return rc;
}