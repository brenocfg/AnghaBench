#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smb_sb_info {int /*<<< orphan*/  header; int /*<<< orphan*/  rstate; } ;
struct smb_request {int* rq_header; int rq_resp_wct; int rq_bytes_recvd; int rq_rlen; int rq_iovlen; TYPE_1__* rq_iov; } ;
struct TYPE_2__ {int* iov_base; int iov_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARANOIA (char*,int) ; 
 int SMB_HEADER_LEN ; 
 int /*<<< orphan*/  SMB_RECV_DROP ; 
 int /*<<< orphan*/  SMB_RECV_PARAM ; 
 int /*<<< orphan*/  VERBOSE (char*,int,int) ; 
 int /*<<< orphan*/  add_recv_stats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smb_len (int /*<<< orphan*/ ) ; 
 int smb_wct ; 

__attribute__((used)) static int smb_init_request(struct smb_sb_info *server, struct smb_request *req)
{
	int hdrlen, wct;

	memcpy(req->rq_header, server->header, SMB_HEADER_LEN);

	wct = *(req->rq_header + smb_wct);
	if (wct > 20) {	
		PARANOIA("wct too large, %d > 20\n", wct);
		server->rstate = SMB_RECV_DROP;
		return 0;
	}

	req->rq_resp_wct = wct;
	hdrlen = SMB_HEADER_LEN + wct*2 + 2;
	VERBOSE("header length: %d   smb_wct: %2d\n", hdrlen, wct);

	req->rq_bytes_recvd = SMB_HEADER_LEN;
	req->rq_rlen = hdrlen;
	req->rq_iov[0].iov_base = req->rq_header;
	req->rq_iov[0].iov_len  = hdrlen;
	req->rq_iovlen = 1;
	server->rstate = SMB_RECV_PARAM;

#ifdef SMB_DEBUG_PACKET_SIZE
	add_recv_stats(smb_len(server->header));
#endif
	return 0;
}