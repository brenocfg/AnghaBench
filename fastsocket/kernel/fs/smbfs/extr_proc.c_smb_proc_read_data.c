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
struct smb_request {int rq_rsize; int rq_iovlen; scalar_t__ rq_bytes_recvd; int /*<<< orphan*/  rq_header; scalar_t__ rq_rlen; TYPE_1__* rq_iov; int /*<<< orphan*/  rq_page; int /*<<< orphan*/  rq_buffer; } ;
struct TYPE_2__ {int iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 scalar_t__ smb_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
smb_proc_read_data(struct smb_request *req)
{
	req->rq_iov[0].iov_base = req->rq_buffer;
	req->rq_iov[0].iov_len  = 3;

	req->rq_iov[1].iov_base = req->rq_page;
	req->rq_iov[1].iov_len  = req->rq_rsize;
	req->rq_iovlen = 2;

	req->rq_rlen = smb_len(req->rq_header) + 4 - req->rq_bytes_recvd;
}