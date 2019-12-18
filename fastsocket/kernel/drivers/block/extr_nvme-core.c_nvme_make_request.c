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
struct request_queue {struct nvme_ns* queuedata; } ;
struct nvme_queue {int /*<<< orphan*/  q_lock; int /*<<< orphan*/  sq_cong; int /*<<< orphan*/  sq_cong_wait; int /*<<< orphan*/  sq_full; int /*<<< orphan*/  q_suspended; } ;
struct nvme_ns {int /*<<< orphan*/  dev; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 scalar_t__ bio_list_empty (int /*<<< orphan*/ *) ; 
 struct nvme_queue* get_nvmeq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_process_cq (struct nvme_queue*) ; 
 int nvme_submit_bio_queue (struct nvme_queue*,struct nvme_ns*,struct bio*) ; 
 int /*<<< orphan*/  put_nvmeq (struct nvme_queue*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nvme_make_request(struct request_queue *q, struct bio *bio)
{
	struct nvme_ns *ns = q->queuedata;
	struct nvme_queue *nvmeq = get_nvmeq(ns->dev);
	int result = -EBUSY;

	if (!nvmeq) {
		put_nvmeq(NULL);
		bio_endio(bio, -EIO);
		return 0;
	}

	spin_lock_irq(&nvmeq->q_lock);
	if (!nvmeq->q_suspended && bio_list_empty(&nvmeq->sq_cong))
		result = nvme_submit_bio_queue(nvmeq, ns, bio);
	if (unlikely(result)) {
		if (bio_list_empty(&nvmeq->sq_cong))
			add_wait_queue(&nvmeq->sq_full, &nvmeq->sq_cong_wait);
		bio_list_add(&nvmeq->sq_cong, bio);
	}

	nvme_process_cq(nvmeq);
	spin_unlock_irq(&nvmeq->q_lock);
	put_nvmeq(nvmeq);
	return 0;
}