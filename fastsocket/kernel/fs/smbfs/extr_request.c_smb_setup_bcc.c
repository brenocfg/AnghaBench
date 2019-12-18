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
struct smb_request {scalar_t__ rq_rlen; scalar_t__ rq_bytes_recvd; scalar_t__ rq_bufsize; int rq_iovlen; TYPE_1__* rq_iov; int /*<<< orphan*/  rq_buffer; int /*<<< orphan*/  rq_header; } ;
struct TYPE_2__ {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  PARANOIA (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ smb_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smb_setup_bcc(struct smb_request *req)
{
	int result = 0;
	req->rq_rlen = smb_len(req->rq_header) + 4 - req->rq_bytes_recvd;

	if (req->rq_rlen > req->rq_bufsize) {
		PARANOIA("Packet too large %d > %d\n",
			 req->rq_rlen, req->rq_bufsize);
		return -ENOBUFS;
	}

	req->rq_iov[0].iov_base = req->rq_buffer;
	req->rq_iov[0].iov_len  = req->rq_rlen;
	req->rq_iovlen = 1;

	return result;
}