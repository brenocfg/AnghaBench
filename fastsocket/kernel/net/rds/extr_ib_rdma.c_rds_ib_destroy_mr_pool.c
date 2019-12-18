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
struct rds_ib_mr_pool {int /*<<< orphan*/  free_pinned; int /*<<< orphan*/  item_count; int /*<<< orphan*/  flush_worker; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct rds_ib_mr_pool*) ; 
 int /*<<< orphan*/  rds_ib_flush_mr_pool (struct rds_ib_mr_pool*,int,int /*<<< orphan*/ *) ; 

void rds_ib_destroy_mr_pool(struct rds_ib_mr_pool *pool)
{
	cancel_delayed_work_sync(&pool->flush_worker);
	rds_ib_flush_mr_pool(pool, 1, NULL);
	WARN_ON(atomic_read(&pool->item_count));
	WARN_ON(atomic_read(&pool->free_pinned));
	kfree(pool);
}