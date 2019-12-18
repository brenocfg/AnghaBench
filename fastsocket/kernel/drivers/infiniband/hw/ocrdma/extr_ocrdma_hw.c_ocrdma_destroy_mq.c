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
struct ocrdma_queue_info {scalar_t__ created; } ;
struct TYPE_4__ {struct ocrdma_queue_info cq; struct ocrdma_queue_info sq; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct ocrdma_dev {TYPE_2__ mq; TYPE_1__ mqe_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  QTYPE_CQ ; 
 int /*<<< orphan*/  QTYPE_MCCQ ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocrdma_free_q (struct ocrdma_dev*,struct ocrdma_queue_info*) ; 
 int /*<<< orphan*/  ocrdma_mbx_delete_q (struct ocrdma_dev*,struct ocrdma_queue_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocrdma_destroy_mq(struct ocrdma_dev *dev)
{
	struct ocrdma_queue_info *mbxq, *cq;

	/* mqe_ctx lock synchronizes with any other pending cmds. */
	mutex_lock(&dev->mqe_ctx.lock);
	mbxq = &dev->mq.sq;
	if (mbxq->created) {
		ocrdma_mbx_delete_q(dev, mbxq, QTYPE_MCCQ);
		ocrdma_free_q(dev, mbxq);
	}
	mutex_unlock(&dev->mqe_ctx.lock);

	cq = &dev->mq.cq;
	if (cq->created) {
		ocrdma_mbx_delete_q(dev, cq, QTYPE_CQ);
		ocrdma_free_q(dev, cq);
	}
}