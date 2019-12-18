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
struct nvme_queue {size_t cq_vector; int q_suspended; int /*<<< orphan*/  q_lock; } ;
struct nvme_dev {TYPE_1__* entry; struct nvme_queue** queues; } ;
struct TYPE_2__ {int vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  adapter_delete_cq (struct nvme_dev*,int) ; 
 int /*<<< orphan*/  adapter_delete_sq (struct nvme_dev*,int) ; 
 int /*<<< orphan*/  free_irq (int,struct nvme_queue*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_cancel_ios (struct nvme_queue*,int) ; 
 int /*<<< orphan*/  nvme_process_cq (struct nvme_queue*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_disable_queue(struct nvme_dev *dev, int qid)
{
	struct nvme_queue *nvmeq = dev->queues[qid];
	int vector = dev->entry[nvmeq->cq_vector].vector;

	spin_lock_irq(&nvmeq->q_lock);
	if (nvmeq->q_suspended) {
		spin_unlock_irq(&nvmeq->q_lock);
		return;
	}
	nvmeq->q_suspended = 1;
	spin_unlock_irq(&nvmeq->q_lock);

	irq_set_affinity_hint(vector, NULL);
	free_irq(vector, nvmeq);

	/* Don't tell the adapter to delete the admin queue */
	if (qid) {
		adapter_delete_sq(dev, qid);
		adapter_delete_cq(dev, qid);
	}

	spin_lock_irq(&nvmeq->q_lock);
	nvme_process_cq(nvmeq);
	nvme_cancel_ios(nvmeq, false);
	spin_unlock_irq(&nvmeq->q_lock);
}