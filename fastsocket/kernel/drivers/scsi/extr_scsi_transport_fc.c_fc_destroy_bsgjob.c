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
struct TYPE_4__ {struct fc_bsg_job* sg_list; } ;
struct TYPE_3__ {struct fc_bsg_job* sg_list; } ;
struct fc_bsg_job {TYPE_2__ reply_payload; TYPE_1__ request_payload; int /*<<< orphan*/  dev; int /*<<< orphan*/  job_lock; scalar_t__ ref_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct fc_bsg_job*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
fc_destroy_bsgjob(struct fc_bsg_job *job)
{
	unsigned long flags;

	spin_lock_irqsave(&job->job_lock, flags);
	if (job->ref_cnt) {
		spin_unlock_irqrestore(&job->job_lock, flags);
		return;
	}
	spin_unlock_irqrestore(&job->job_lock, flags);

	put_device(job->dev);	/* release reference for the request */

	kfree(job->request_payload.sg_list);
	kfree(job->reply_payload.sg_list);
	kfree(job);
}