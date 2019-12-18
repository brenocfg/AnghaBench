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
struct request_list {int /*<<< orphan*/  rq_pool; int /*<<< orphan*/ * wait; scalar_t__ elvpriv; scalar_t__* starved; scalar_t__* count; } ;
struct request_queue {int /*<<< orphan*/  node; struct request_list rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKDEV_MIN_RQ ; 
 size_t BLK_RW_ASYNC ; 
 size_t BLK_RW_SYNC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_alloc_slab ; 
 int /*<<< orphan*/  mempool_create_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free_slab ; 
 int /*<<< orphan*/  request_cachep ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int blk_init_free_list(struct request_queue *q)
{
	struct request_list *rl = &q->rq;

	if (unlikely(rl->rq_pool))
		return 0;

	rl->count[BLK_RW_SYNC] = rl->count[BLK_RW_ASYNC] = 0;
	rl->starved[BLK_RW_SYNC] = rl->starved[BLK_RW_ASYNC] = 0;
	rl->elvpriv = 0;
	init_waitqueue_head(&rl->wait[BLK_RW_SYNC]);
	init_waitqueue_head(&rl->wait[BLK_RW_ASYNC]);

	rl->rq_pool = mempool_create_node(BLKDEV_MIN_RQ, mempool_alloc_slab,
				mempool_free_slab, request_cachep, q->node);

	if (!rl->rq_pool)
		return -ENOMEM;

	return 0;
}