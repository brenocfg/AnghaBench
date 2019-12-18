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
struct TYPE_2__ {scalar_t__ max_maps; } ;
struct rds_ib_mr_pool {int max_free_pinned; int max_items; int /*<<< orphan*/  flush_worker; int /*<<< orphan*/  dirty_count; int /*<<< orphan*/  free_pinned; int /*<<< orphan*/  free_list; int /*<<< orphan*/  drop_list; TYPE_1__ fmr_attr; } ;
struct rds_ib_mr {scalar_t__ remap_count; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  llnode; struct rds_ib_device* device; } ;
struct rds_ib_device {struct rds_ib_mr_pool* mr_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_ib_dev_put (struct rds_ib_device*) ; 
 int /*<<< orphan*/  rds_ib_flush_mr_pool (struct rds_ib_mr_pool*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdsdebug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

void rds_ib_free_mr(void *trans_private, int invalidate)
{
	struct rds_ib_mr *ibmr = trans_private;
	struct rds_ib_device *rds_ibdev = ibmr->device;
	struct rds_ib_mr_pool *pool = rds_ibdev->mr_pool;

	rdsdebug("RDS/IB: free_mr nents %u\n", ibmr->sg_len);

	/* Return it to the pool's free list */
	if (ibmr->remap_count >= pool->fmr_attr.max_maps)
		llist_add(&ibmr->llnode, &pool->drop_list);
	else
		llist_add(&ibmr->llnode, &pool->free_list);

	atomic_add(ibmr->sg_len, &pool->free_pinned);
	atomic_inc(&pool->dirty_count);

	/* If we've pinned too many pages, request a flush */
	if (atomic_read(&pool->free_pinned) >= pool->max_free_pinned ||
	    atomic_read(&pool->dirty_count) >= pool->max_items / 10)
		schedule_delayed_work(&pool->flush_worker, 10);

	if (invalidate) {
		if (likely(!in_interrupt())) {
			rds_ib_flush_mr_pool(pool, 0, NULL);
		} else {
			/* We get here if the user created a MR marked
			 * as use_once and invalidate at the same time. */
			schedule_delayed_work(&pool->flush_worker, 10);
		}
	}

	rds_ib_dev_put(rds_ibdev);
}