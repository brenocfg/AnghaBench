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
struct smb_request {int rq_resp_wct; int rq_rsize; int rq_iovlen; scalar_t__ rq_bytes_recvd; int /*<<< orphan*/  rq_header; scalar_t__ rq_rlen; TYPE_1__* rq_iov; int /*<<< orphan*/  rq_page; int /*<<< orphan*/  rq_buffer; scalar_t__ rq_bufsize; } ;
struct TYPE_2__ {int iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARANOIA (char*,...) ; 
 int SMB_HEADER_LEN ; 
 int SMB_READX_MAX_PAD ; 
 int WVAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ smb_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_vwv6 ; 

__attribute__((used)) static void
smb_proc_readX_data(struct smb_request *req)
{
	/* header length, excluding the netbios length (-4) */
	int hdrlen = SMB_HEADER_LEN + req->rq_resp_wct*2 - 2;
	int data_off = WVAL(req->rq_header, smb_vwv6);

	/*
	 * Some genius made the padding to the data bytes arbitrary.
	 * So we must first calculate the amount of padding used by the server.
	 */
	data_off -= hdrlen;
	if (data_off > SMB_READX_MAX_PAD || data_off < 0) {
		PARANOIA("offset is larger than SMB_READX_MAX_PAD or negative!\n");
		PARANOIA("%d > %d || %d < 0\n", data_off, SMB_READX_MAX_PAD, data_off);
		req->rq_rlen = req->rq_bufsize + 1;
		return;
	}
	req->rq_iov[0].iov_base = req->rq_buffer;
	req->rq_iov[0].iov_len  = data_off;

	req->rq_iov[1].iov_base = req->rq_page;
	req->rq_iov[1].iov_len  = req->rq_rsize;
	req->rq_iovlen = 2;

	req->rq_rlen = smb_len(req->rq_header) + 4 - req->rq_bytes_recvd;
}