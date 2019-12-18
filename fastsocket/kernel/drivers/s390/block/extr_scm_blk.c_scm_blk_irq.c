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
struct scm_request {int error; int /*<<< orphan*/  list; struct scm_blk_dev* bdev; } ;
struct scm_device {int dummy; } ;
struct scm_blk_dev {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  lock; int /*<<< orphan*/  finished_requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  __scmrq_log_error (struct scm_request*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

void scm_blk_irq(struct scm_device *scmdev, void *data, int error)
{
	struct scm_request *scmrq = data;
	struct scm_blk_dev *bdev = scmrq->bdev;

	scmrq->error = error;
	if (error)
		__scmrq_log_error(scmrq);

	spin_lock(&bdev->lock);
	list_add_tail(&scmrq->list, &bdev->finished_requests);
	spin_unlock(&bdev->lock);
	tasklet_hi_schedule(&bdev->tasklet);
}