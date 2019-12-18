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
struct nvme_queue {void* sq_cmds; int /*<<< orphan*/  sq_dma_addr; int /*<<< orphan*/  q_depth; int /*<<< orphan*/  q_dmadev; int /*<<< orphan*/  cq_dma_addr; scalar_t__ cqes; int /*<<< orphan*/  q_lock; int /*<<< orphan*/  sq_cong; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQ_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  SQ_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_endio (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_list_peek (int /*<<< orphan*/ *) ; 
 struct bio* bio_list_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvme_queue*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_free_queue(struct nvme_queue *nvmeq)
{
	spin_lock_irq(&nvmeq->q_lock);
	while (bio_list_peek(&nvmeq->sq_cong)) {
		struct bio *bio = bio_list_pop(&nvmeq->sq_cong);
		bio_endio(bio, -EIO);
	}
	spin_unlock_irq(&nvmeq->q_lock);

	dma_free_coherent(nvmeq->q_dmadev, CQ_SIZE(nvmeq->q_depth),
				(void *)nvmeq->cqes, nvmeq->cq_dma_addr);
	dma_free_coherent(nvmeq->q_dmadev, SQ_SIZE(nvmeq->q_depth),
					nvmeq->sq_cmds, nvmeq->sq_dma_addr);
	kfree(nvmeq);
}