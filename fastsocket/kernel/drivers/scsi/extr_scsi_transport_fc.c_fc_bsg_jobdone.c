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
typedef  int /*<<< orphan*/  uint32_t ;
struct request {int errors; int sense_len; scalar_t__ resid_len; struct request* next_rq; } ;
struct fc_bsg_job {int reply_len; TYPE_1__* reply; struct request* req; } ;
struct TYPE_2__ {int result; scalar_t__ reply_payload_rcv_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  blk_complete_request (struct request*) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
fc_bsg_jobdone(struct fc_bsg_job *job)
{
	struct request *req = job->req;
	struct request *rsp = req->next_rq;
	int err;

	err = job->req->errors = job->reply->result;

	if (err < 0)
		/* we're only returning the result field in the reply */
		job->req->sense_len = sizeof(uint32_t);
	else
		job->req->sense_len = job->reply_len;

	/* we assume all request payload was transferred, residual == 0 */
	req->resid_len = 0;

	if (rsp) {
		WARN_ON(job->reply->reply_payload_rcv_len > rsp->resid_len);

		/* set reply (bidi) residual */
		rsp->resid_len -= min(job->reply->reply_payload_rcv_len,
				      rsp->resid_len);
	}
	blk_complete_request(req);
}