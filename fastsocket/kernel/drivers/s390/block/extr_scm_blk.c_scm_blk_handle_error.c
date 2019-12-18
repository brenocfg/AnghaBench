#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scm_request {TYPE_3__* aob; int /*<<< orphan*/  error; struct scm_blk_dev* bdev; } ;
struct scm_blk_dev {int /*<<< orphan*/  rq_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; TYPE_2__* scmdev; } ;
struct TYPE_4__ {int eqc; } ;
struct TYPE_6__ {TYPE_1__ response; } ;
struct TYPE_5__ {scalar_t__ address; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
#define  EQC_WR_PROHIBIT 128 
 int /*<<< orphan*/  SCM_WR_PROHIBIT ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long) ; 
 int /*<<< orphan*/  scm_request_requeue (struct scm_request*) ; 
 int /*<<< orphan*/  scm_start_aob (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void scm_blk_handle_error(struct scm_request *scmrq)
{
	struct scm_blk_dev *bdev = scmrq->bdev;
	unsigned long flags;

	if (scmrq->error != -EIO)
		goto restart;

	/* For -EIO the response block is valid. */
	switch (scmrq->aob->response.eqc) {
	case EQC_WR_PROHIBIT:
		spin_lock_irqsave(&bdev->lock, flags);
		if (bdev->state != SCM_WR_PROHIBIT)
			pr_info("%lu: Write access to the SCM increment is suspended\n",
				(unsigned long) bdev->scmdev->address);
		bdev->state = SCM_WR_PROHIBIT;
		spin_unlock_irqrestore(&bdev->lock, flags);
		goto requeue;
	default:
		break;
	}

restart:
	if (!scm_start_aob(scmrq->aob))
		return;

requeue:
	spin_lock_irqsave(&bdev->rq_lock, flags);
	scm_request_requeue(scmrq);
	spin_unlock_irqrestore(&bdev->rq_lock, flags);
}