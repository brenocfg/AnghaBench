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
struct request_queue {int /*<<< orphan*/  queue_lock; } ;
struct request {int errors; struct fc_bsg_job* special; } ;
struct fc_rport {scalar_t__ port_state; int flags; } ;
struct fc_bsg_job {int request_len; int reply_len; TYPE_1__* reply; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  enum fc_dispatch_result { ____Placeholder_fc_dispatch_result } fc_dispatch_result ;
struct TYPE_2__ {int /*<<< orphan*/  result; scalar_t__ reply_payload_rcv_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ENOMSG ; 
 int ENXIO ; 
 int FC_DISPATCH_BREAK ; 
 int FC_DISPATCH_UNLOCKED ; 
 scalar_t__ FC_PORTSTATE_BLOCKED ; 
 scalar_t__ FC_PORTSTATE_ONLINE ; 
 int FC_RPORT_FAST_FAIL_TIMEDOUT ; 
 int /*<<< orphan*/  blk_end_request_all (struct request*,int) ; 
 struct request* blk_fetch_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_plugged (struct request_queue*) ; 
 int fc_bsg_host_dispatch (struct request_queue*,struct Scsi_Host*,struct fc_bsg_job*) ; 
 int /*<<< orphan*/  fc_bsg_jobdone (struct fc_bsg_job*) ; 
 int fc_bsg_rport_dispatch (struct request_queue*,struct Scsi_Host*,struct fc_rport*,struct fc_bsg_job*) ; 
 int fc_req_to_bsgjob (struct Scsi_Host*,struct fc_rport*,struct request*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fc_bsg_request_handler(struct request_queue *q, struct Scsi_Host *shost,
		       struct fc_rport *rport, struct device *dev)
{
	struct request *req;
	struct fc_bsg_job *job;
	enum fc_dispatch_result ret;

	if (!get_device(dev))
		return;

	while (!blk_queue_plugged(q)) {
		if (rport && (rport->port_state == FC_PORTSTATE_BLOCKED) &&
		    !(rport->flags & FC_RPORT_FAST_FAIL_TIMEDOUT))
			break;

		req = blk_fetch_request(q);
		if (!req)
			break;

		if (rport && (rport->port_state != FC_PORTSTATE_ONLINE)) {
			req->errors = -ENXIO;
			spin_unlock_irq(q->queue_lock);
			blk_end_request_all(req, -ENXIO);
			spin_lock_irq(q->queue_lock);
			continue;
		}

		spin_unlock_irq(q->queue_lock);

		ret = fc_req_to_bsgjob(shost, rport, req);
		if (ret) {
			req->errors = ret;
			blk_end_request_all(req, ret);
			spin_lock_irq(q->queue_lock);
			continue;
		}

		job = req->special;

		/* check if we have the msgcode value at least */
		if (job->request_len < sizeof(uint32_t)) {
			BUG_ON(job->reply_len < sizeof(uint32_t));
			job->reply->reply_payload_rcv_len = 0;
			job->reply->result = -ENOMSG;
			job->reply_len = sizeof(uint32_t);
			fc_bsg_jobdone(job);
			spin_lock_irq(q->queue_lock);
			continue;
		}

		/* the dispatch routines will unlock the queue_lock */
		if (rport)
			ret = fc_bsg_rport_dispatch(q, shost, rport, job);
		else
			ret = fc_bsg_host_dispatch(q, shost, job);

		/* did dispatcher hit state that can't process any more */
		if (ret == FC_DISPATCH_BREAK)
			break;

		/* did dispatcher had released the lock */
		if (ret == FC_DISPATCH_UNLOCKED)
			spin_lock_irq(q->queue_lock);
	}

	spin_unlock_irq(q->queue_lock);
	put_device(dev);
	spin_lock_irq(q->queue_lock);
}