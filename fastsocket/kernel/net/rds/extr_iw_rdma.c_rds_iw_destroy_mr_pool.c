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
struct rds_iw_mr_pool {int /*<<< orphan*/  free_pinned; int /*<<< orphan*/  item_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rds_iw_mr_pool*) ; 
 int /*<<< orphan*/  rds_iw_flush_mr_pool (struct rds_iw_mr_pool*,int) ; 
 int /*<<< orphan*/  rds_wq ; 

void rds_iw_destroy_mr_pool(struct rds_iw_mr_pool *pool)
{
	flush_workqueue(rds_wq);
	rds_iw_flush_mr_pool(pool, 1);
	BUG_ON(atomic_read(&pool->item_count));
	BUG_ON(atomic_read(&pool->free_pinned));
	kfree(pool);
}