#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request {scalar_t__ bio; int /*<<< orphan*/  sense; int /*<<< orphan*/  cmd_len; scalar_t__ cmd; struct fc_bsg_job* special; struct request* next_rq; } ;
struct fc_rport {int /*<<< orphan*/  dev; } ;
struct fc_internal {TYPE_1__* f; } ;
struct fc_bsg_request {int dummy; } ;
struct TYPE_4__ {struct fc_bsg_job* sg_list; } ;
struct fc_bsg_job {int ref_cnt; TYPE_2__ request_payload; int /*<<< orphan*/ * dev; int /*<<< orphan*/  job_done; TYPE_2__ reply_payload; int /*<<< orphan*/  reply_len; int /*<<< orphan*/  reply; int /*<<< orphan*/  request_len; struct fc_bsg_request* request; int /*<<< orphan*/  job_lock; void* dd_data; struct request* req; struct fc_rport* rport; struct Scsi_Host* shost; } ;
struct Scsi_Host {int /*<<< orphan*/  shost_gendev; int /*<<< orphan*/  transportt; } ;
struct TYPE_3__ {scalar_t__ dd_bsg_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct fc_bsg_job*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  fc_bsg_jobdone ; 
 int fc_bsg_map_buffer (TYPE_2__*,struct request*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct fc_bsg_job*) ; 
 struct fc_bsg_job* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct fc_internal* to_fc_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fc_req_to_bsgjob(struct Scsi_Host *shost, struct fc_rport *rport,
	struct request *req)
{
	struct fc_internal *i = to_fc_internal(shost->transportt);
	struct request *rsp = req->next_rq;
	struct fc_bsg_job *job;
	int ret;

	BUG_ON(req->special);

	job = kzalloc(sizeof(struct fc_bsg_job) + i->f->dd_bsg_size,
			GFP_KERNEL);
	if (!job)
		return -ENOMEM;

	/*
	 * Note: this is a bit silly.
	 * The request gets formatted as a SGIO v4 ioctl request, which
	 * then gets reformatted as a blk request, which then gets
	 * reformatted as a fc bsg request. And on completion, we have
	 * to wrap return results such that SGIO v4 thinks it was a scsi
	 * status.  I hope this was all worth it.
	 */

	req->special = job;
	job->shost = shost;
	job->rport = rport;
	job->req = req;
	if (i->f->dd_bsg_size)
		job->dd_data = (void *)&job[1];
	spin_lock_init(&job->job_lock);
	job->request = (struct fc_bsg_request *)req->cmd;
	job->request_len = req->cmd_len;
	job->reply = req->sense;
	job->reply_len = SCSI_SENSE_BUFFERSIZE;	/* Size of sense buffer
						 * allocated */
	if (req->bio) {
		ret = fc_bsg_map_buffer(&job->request_payload, req);
		if (ret)
			goto failjob_rls_job;
	}
	if (rsp && rsp->bio) {
		ret = fc_bsg_map_buffer(&job->reply_payload, rsp);
		if (ret)
			goto failjob_rls_rqst_payload;
	}
	job->job_done = fc_bsg_jobdone;
	if (rport)
		job->dev = &rport->dev;
	else
		job->dev = &shost->shost_gendev;
	get_device(job->dev);		/* take a reference for the request */

	job->ref_cnt = 1;

	return 0;


failjob_rls_rqst_payload:
	kfree(job->request_payload.sg_list);
failjob_rls_job:
	kfree(job);
	return -ENOMEM;
}