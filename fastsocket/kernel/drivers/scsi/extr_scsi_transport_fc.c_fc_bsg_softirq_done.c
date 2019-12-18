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
struct request {int /*<<< orphan*/  errors; struct fc_bsg_job* special; } ;
struct fc_bsg_job {int /*<<< orphan*/  job_lock; int /*<<< orphan*/  ref_cnt; int /*<<< orphan*/  state_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_RQST_STATE_DONE ; 
 int /*<<< orphan*/  blk_end_request_all (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_destroy_bsgjob (struct fc_bsg_job*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fc_bsg_softirq_done(struct request *rq)
{
	struct fc_bsg_job *job = rq->special;
	unsigned long flags;

	spin_lock_irqsave(&job->job_lock, flags);
	job->state_flags |= FC_RQST_STATE_DONE;
	job->ref_cnt--;
	spin_unlock_irqrestore(&job->job_lock, flags);

	blk_end_request_all(rq, rq->errors);
	fc_destroy_bsgjob(job);
}