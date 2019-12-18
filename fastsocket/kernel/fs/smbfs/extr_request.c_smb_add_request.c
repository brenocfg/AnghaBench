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
struct smb_sb_info {int mid; scalar_t__ state; int conn_error; int /*<<< orphan*/  xmitq; } ;
struct smb_request {scalar_t__* rq_header; int rq_flags; scalar_t__ rq_rcls; int rq_errno; int /*<<< orphan*/  rq_err; int /*<<< orphan*/  rq_mid; int /*<<< orphan*/  rq_queue; int /*<<< orphan*/  rq_wait; int /*<<< orphan*/ * rq_buffer; scalar_t__ rq_trans2_command; struct smb_sb_info* rq_server; } ;

/* Variables and functions */
 scalar_t__ CONN_INVALID ; 
 scalar_t__ CONN_VALID ; 
 int EINTR ; 
 int EIO ; 
 int ERESTARTSYS ; 
 scalar_t__ ERRSRV ; 
 int /*<<< orphan*/  ERRtimeout ; 
 int HZ ; 
 int /*<<< orphan*/  PARANOIA (char*,...) ; 
 int SMB_REQ_RECEIVED ; 
 int /*<<< orphan*/  VERBOSE (char*,scalar_t__) ; 
 int /*<<< orphan*/  WSET (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WVAL (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_xmit_stats (struct smb_request*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int smb_com ; 
 int smb_errno (struct smb_request*) ; 
 int smb_flg ; 
 int /*<<< orphan*/  smb_lock_server (struct smb_sb_info*) ; 
 scalar_t__ smb_lock_server_interruptible (struct smb_sb_info*) ; 
 int /*<<< orphan*/  smb_mid ; 
 int /*<<< orphan*/  smb_pid ; 
 int smb_rcls ; 
 int smb_request_send_req (struct smb_request*) ; 
 int /*<<< orphan*/  smb_rget (struct smb_request*) ; 
 int /*<<< orphan*/  smb_rput (struct smb_request*) ; 
 int /*<<< orphan*/  smb_setup_request (struct smb_request*) ; 
 int smb_setup_trans2request (struct smb_request*) ; 
 int /*<<< orphan*/  smb_tid ; 
 int /*<<< orphan*/  smb_uid ; 
 int /*<<< orphan*/  smb_unlock_server (struct smb_sb_info*) ; 
 int smb_wct ; 
 int /*<<< orphan*/  smbiod_retry (struct smb_sb_info*) ; 
 int /*<<< orphan*/  smbiod_wake_up () ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

int smb_add_request(struct smb_request *req)
{
	long timeleft;
	struct smb_sb_info *server = req->rq_server;
	int result = 0;

	smb_setup_request(req);
	if (req->rq_trans2_command) {
		if (req->rq_buffer == NULL) {
			PARANOIA("trans2 attempted without response buffer!\n");
			return -EIO;
		}
		result = smb_setup_trans2request(req);
	}
	if (result < 0)
		return result;

#ifdef SMB_DEBUG_PACKET_SIZE
	add_xmit_stats(req);
#endif

	/* add 'req' to the queue of requests */
	if (smb_lock_server_interruptible(server))
		return -EINTR;

	/*
	 * Try to send the request as the process. If that fails we queue the
	 * request and let smbiod send it later.
	 */

	/* FIXME: each server has a number on the maximum number of parallel
	   requests. 10, 50 or so. We should not allow more requests to be
	   active. */
	if (server->mid > 0xf000)
		server->mid = 0;
	req->rq_mid = server->mid++;
	WSET(req->rq_header, smb_mid, req->rq_mid);

	result = 0;
	if (server->state == CONN_VALID) {
		if (list_empty(&server->xmitq))
			result = smb_request_send_req(req);
		if (result < 0) {
			/* Connection lost? */
			server->conn_error = result;
			server->state = CONN_INVALID;
		}
	}
	if (result != 1)
		list_add_tail(&req->rq_queue, &server->xmitq);
	smb_rget(req);

	if (server->state != CONN_VALID)
		smbiod_retry(server);

	smb_unlock_server(server);

	smbiod_wake_up();

	timeleft = wait_event_interruptible_timeout(req->rq_wait,
				    req->rq_flags & SMB_REQ_RECEIVED, 30*HZ);
	if (!timeleft || signal_pending(current)) {
		/*
		 * On timeout or on interrupt we want to try and remove the
		 * request from the recvq/xmitq.
		 * First check if the request is still part of a queue. (May
		 * have been removed by some error condition)
		 */
		smb_lock_server(server);
		if (!list_empty(&req->rq_queue)) {
			list_del_init(&req->rq_queue);
			smb_rput(req);
		}
		smb_unlock_server(server);
	}

	if (!timeleft) {
		PARANOIA("request [%p, mid=%d] timed out!\n",
			 req, req->rq_mid);
		VERBOSE("smb_com:  %02x\n", *(req->rq_header + smb_com));
		VERBOSE("smb_rcls: %02x\n", *(req->rq_header + smb_rcls));
		VERBOSE("smb_flg:  %02x\n", *(req->rq_header + smb_flg));
		VERBOSE("smb_tid:  %04x\n", WVAL(req->rq_header, smb_tid));
		VERBOSE("smb_pid:  %04x\n", WVAL(req->rq_header, smb_pid));
		VERBOSE("smb_uid:  %04x\n", WVAL(req->rq_header, smb_uid));
		VERBOSE("smb_mid:  %04x\n", WVAL(req->rq_header, smb_mid));
		VERBOSE("smb_wct:  %02x\n", *(req->rq_header + smb_wct));

		req->rq_rcls = ERRSRV;
		req->rq_err  = ERRtimeout;

		/* Just in case it was "stuck" */
		smbiod_wake_up();
	}
	VERBOSE("woke up, rcls=%d\n", req->rq_rcls);

	if (req->rq_rcls != 0)
		req->rq_errno = smb_errno(req);
	if (signal_pending(current))
		req->rq_errno = -ERESTARTSYS;
	return req->rq_errno;
}