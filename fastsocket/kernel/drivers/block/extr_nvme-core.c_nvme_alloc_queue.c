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
struct nvme_queue {int cq_phase; int q_depth; int cq_vector; int q_suspended; int /*<<< orphan*/  cq_dma_addr; void* cqes; int /*<<< orphan*/ * q_db; int /*<<< orphan*/  sq_cong; int /*<<< orphan*/  sq_cong_wait; int /*<<< orphan*/  sq_full; scalar_t__ cq_head; int /*<<< orphan*/  q_lock; struct nvme_dev* dev; struct device* q_dmadev; void* sq_cmds; int /*<<< orphan*/  sq_dma_addr; } ;
struct nvme_dev {int db_stride; int /*<<< orphan*/  queue_count; int /*<<< orphan*/ * dbs; TYPE_1__* pci_dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQ_SIZE (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SQ_SIZE (int) ; 
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 void* dma_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nvme_queue*) ; 
 struct nvme_queue* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int nvme_queue_extra (int) ; 
 int /*<<< orphan*/  nvme_thread ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nvme_queue *nvme_alloc_queue(struct nvme_dev *dev, int qid,
							int depth, int vector)
{
	struct device *dmadev = &dev->pci_dev->dev;
	unsigned extra = nvme_queue_extra(depth);
	struct nvme_queue *nvmeq = kzalloc(sizeof(*nvmeq) + extra, GFP_KERNEL);
	if (!nvmeq)
		return NULL;

	nvmeq->cqes = dma_alloc_coherent(dmadev, CQ_SIZE(depth),
					&nvmeq->cq_dma_addr, GFP_KERNEL);
	if (!nvmeq->cqes)
		goto free_nvmeq;
	memset((void *)nvmeq->cqes, 0, CQ_SIZE(depth));

	nvmeq->sq_cmds = dma_alloc_coherent(dmadev, SQ_SIZE(depth),
					&nvmeq->sq_dma_addr, GFP_KERNEL);
	if (!nvmeq->sq_cmds)
		goto free_cqdma;

	nvmeq->q_dmadev = dmadev;
	nvmeq->dev = dev;
	spin_lock_init(&nvmeq->q_lock);
	nvmeq->cq_head = 0;
	nvmeq->cq_phase = 1;
	init_waitqueue_head(&nvmeq->sq_full);
	init_waitqueue_entry(&nvmeq->sq_cong_wait, nvme_thread);
	bio_list_init(&nvmeq->sq_cong);
	nvmeq->q_db = &dev->dbs[qid << (dev->db_stride + 1)];
	nvmeq->q_depth = depth;
	nvmeq->cq_vector = vector;
	nvmeq->q_suspended = 1;
	dev->queue_count++;

	return nvmeq;

 free_cqdma:
	dma_free_coherent(dmadev, CQ_SIZE(depth), (void *)nvmeq->cqes,
							nvmeq->cq_dma_addr);
 free_nvmeq:
	kfree(nvmeq);
	return NULL;
}