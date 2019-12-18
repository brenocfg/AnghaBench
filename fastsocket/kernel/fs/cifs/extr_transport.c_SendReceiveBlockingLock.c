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
struct smb_hdr {scalar_t__ Command; int /*<<< orphan*/  smb_buf_length; } ;
struct mid_q_entry {scalar_t__ mid_state; int /*<<< orphan*/  resp_buf; int /*<<< orphan*/  callback; int /*<<< orphan*/  sequence_number; } ;
struct cifs_tcon {struct cifs_ses* ses; } ;
struct cifs_ses {TYPE_1__* server; } ;
struct TYPE_10__ {scalar_t__ tcpStatus; int /*<<< orphan*/  response_q; int /*<<< orphan*/  srv_mutex; } ;

/* Variables and functions */
 int CIFSMaxBufSize ; 
 int /*<<< orphan*/  CIFS_BLOCKING_OP ; 
 scalar_t__ CifsExiting ; 
 scalar_t__ CifsGood ; 
 scalar_t__ CifsNew ; 
 int /*<<< orphan*/  DeleteMidQEntry ; 
 int EACCES ; 
 int EIO ; 
 int ENOENT ; 
 int ENOLCK ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GlobalMid_Lock ; 
 int MAX_CIFS_HDR_SIZE ; 
 scalar_t__ MID_REQUEST_SUBMITTED ; 
 scalar_t__ MID_RESPONSE_RECEIVED ; 
 scalar_t__ SMB_COM_TRANSACTION2 ; 
 int allocate_mid (struct cifs_ses*,struct smb_hdr*,struct mid_q_entry**) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cERROR (int,char*,...) ; 
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
 int send_lock_cancel (unsigned int const,struct cifs_tcon*,struct smb_hdr*,struct smb_hdr*) ; 
 int send_nt_cancel (TYPE_1__*,struct smb_hdr*,struct mid_q_entry*) ; 
 int smb_send (TYPE_1__*,struct smb_hdr*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int wait_for_free_request (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int wait_for_response (TYPE_1__*,struct mid_q_entry*) ; 

int
SendReceiveBlockingLock(const unsigned int xid, struct cifs_tcon *tcon,
	    struct smb_hdr *in_buf, struct smb_hdr *out_buf,
	    int *pbytes_returned)
{
	int rc = 0;
	int rstart = 0;
	struct mid_q_entry *midQ;
	struct cifs_ses *ses;

	if (tcon == NULL || tcon->ses == NULL) {
		cERROR(1, "Null smb session");
		return -EIO;
	}
	ses = tcon->ses;

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

	rc = wait_for_free_request(ses->server, CIFS_BLOCKING_OP);
	if (rc)
		return rc;

	/* make sure that we sign in the same order that we send on this socket
	   and avoid races inside tcp sendmsg code that could cause corruption
	   of smb data */

	mutex_lock(&ses->server->srv_mutex);

	rc = allocate_mid(ses, in_buf, &midQ);
	if (rc) {
		mutex_unlock(&ses->server->srv_mutex);
		return rc;
	}

	rc = cifs_sign_smb(in_buf, ses->server, &midQ->sequence_number);
	if (rc) {
		delete_mid(midQ);
		mutex_unlock(&ses->server->srv_mutex);
		return rc;
	}

	midQ->mid_state = MID_REQUEST_SUBMITTED;
	cifs_in_send_inc(ses->server);
	rc = smb_send(ses->server, in_buf, be32_to_cpu(in_buf->smb_buf_length));
	cifs_in_send_dec(ses->server);
	cifs_save_when_sent(midQ);
	mutex_unlock(&ses->server->srv_mutex);

	if (rc < 0) {
		delete_mid(midQ);
		return rc;
	}

	/* Wait for a reply - allow signals to interrupt. */
	rc = wait_event_interruptible(ses->server->response_q,
		(!(midQ->mid_state == MID_REQUEST_SUBMITTED)) ||
		((ses->server->tcpStatus != CifsGood) &&
		 (ses->server->tcpStatus != CifsNew)));

	/* Were we interrupted by a signal ? */
	if ((rc == -ERESTARTSYS) &&
		(midQ->mid_state == MID_REQUEST_SUBMITTED) &&
		((ses->server->tcpStatus == CifsGood) ||
		 (ses->server->tcpStatus == CifsNew))) {

		if (in_buf->Command == SMB_COM_TRANSACTION2) {
			/* POSIX lock. We send a NT_CANCEL SMB to cause the
			   blocking lock to return. */
			rc = send_nt_cancel(ses->server, in_buf, midQ);
			if (rc) {
				delete_mid(midQ);
				return rc;
			}
		} else {
			/* Windows lock. We send a LOCKINGX_CANCEL_LOCK
			   to cause the blocking lock to return. */

			rc = send_lock_cancel(xid, tcon, in_buf, out_buf);

			/* If we get -ENOLCK back the lock may have
			   already been removed. Don't exit in this case. */
			if (rc && rc != -ENOLCK) {
				delete_mid(midQ);
				return rc;
			}
		}

		rc = wait_for_response(ses->server, midQ);
		if (rc) {
			send_nt_cancel(ses->server, in_buf, midQ);
			spin_lock(&GlobalMid_Lock);
			if (midQ->mid_state == MID_REQUEST_SUBMITTED) {
				/* no longer considered to be "in-flight" */
				midQ->callback = DeleteMidQEntry;
				spin_unlock(&GlobalMid_Lock);
				return rc;
			}
			spin_unlock(&GlobalMid_Lock);
		}

		/* We got the response - restart system call. */
		rstart = 1;
	}

	rc = cifs_sync_mid_result(midQ, ses->server);
	if (rc != 0)
		return rc;

	/* rcvd frame is ok */
	if (out_buf == NULL || midQ->mid_state != MID_RESPONSE_RECEIVED) {
		rc = -EIO;
		cERROR(1, "Bad MID state?");
		goto out;
	}

	*pbytes_returned = get_rfc1002_length(midQ->resp_buf);
	memcpy(out_buf, midQ->resp_buf, *pbytes_returned + 4);
	rc = cifs_check_receive(midQ, ses->server, 0);
out:
	delete_mid(midQ);
	if (rstart && rc == -EACCES)
		return -ERESTARTSYS;
	return rc;
}