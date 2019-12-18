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
struct smb_request {int rq_slen; int /*<<< orphan*/ * rq_trans2buffer; scalar_t__ rq_fragment; scalar_t__ rq_errno; scalar_t__ rq_err; scalar_t__ rq_rcls; scalar_t__ rq_bytes_sent; int /*<<< orphan*/  rq_setup_read; scalar_t__ rq_resp_bcc; int /*<<< orphan*/  rq_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int smb_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_setup_bcc ; 

__attribute__((used)) static int smb_setup_request(struct smb_request *req)
{
	int len = smb_len(req->rq_header) + 4;
	req->rq_slen = len;

	/* if we expect a data part in the reply we set the iov's to read it */
	if (req->rq_resp_bcc)
		req->rq_setup_read = smb_setup_bcc;

	/* This tries to support re-using the same request */
	req->rq_bytes_sent = 0;
	req->rq_rcls = 0;
	req->rq_err = 0;
	req->rq_errno = 0;
	req->rq_fragment = 0;
	kfree(req->rq_trans2buffer);
	req->rq_trans2buffer = NULL;

	return 0;
}