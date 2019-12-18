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
struct pool_c {struct pool* pool; } ;
struct pool {int /*<<< orphan*/  wq; int /*<<< orphan*/  waker; } ;
struct dm_target {struct pool_c* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  commit (struct pool*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pool_postsuspend(struct dm_target *ti)
{
	struct pool_c *pt = ti->private;
	struct pool *pool = pt->pool;

	cancel_delayed_work(&pool->waker);
	flush_workqueue(pool->wq);
	(void) commit(pool);
}