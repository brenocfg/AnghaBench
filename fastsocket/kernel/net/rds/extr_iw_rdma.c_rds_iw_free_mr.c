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
struct rds_iw_mr_pool {int max_free_pinned; int max_items; int /*<<< orphan*/  flush_worker; int /*<<< orphan*/  dirty_count; int /*<<< orphan*/  free_pinned; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct TYPE_5__ {TYPE_1__ m_sg; } ;
struct rds_iw_mr {TYPE_2__ mapping; TYPE_3__* device; } ;
struct TYPE_6__ {struct rds_iw_mr_pool* mr_pool; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rds_iw_flush_mr_pool (struct rds_iw_mr_pool*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_iw_free_fastreg (struct rds_iw_mr_pool*,struct rds_iw_mr*) ; 
 int /*<<< orphan*/  rds_wq ; 
 int /*<<< orphan*/  rdsdebug (char*,int /*<<< orphan*/ ) ; 

void rds_iw_free_mr(void *trans_private, int invalidate)
{
	struct rds_iw_mr *ibmr = trans_private;
	struct rds_iw_mr_pool *pool = ibmr->device->mr_pool;

	rdsdebug("RDS/IW: free_mr nents %u\n", ibmr->mapping.m_sg.len);
	if (!pool)
		return;

	/* Return it to the pool's free list */
	rds_iw_free_fastreg(pool, ibmr);

	/* If we've pinned too many pages, request a flush */
	if (atomic_read(&pool->free_pinned) >= pool->max_free_pinned
	 || atomic_read(&pool->dirty_count) >= pool->max_items / 10)
		queue_work(rds_wq, &pool->flush_worker);

	if (invalidate) {
		if (likely(!in_interrupt())) {
			rds_iw_flush_mr_pool(pool, 0);
		} else {
			/* We get here if the user created a MR marked
			 * as use_once and invalidate at the same time. */
			queue_work(rds_wq, &pool->flush_worker);
		}
	}
}