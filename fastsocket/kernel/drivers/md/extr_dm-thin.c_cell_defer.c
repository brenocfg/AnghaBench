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
struct thin_c {int /*<<< orphan*/  lock; int /*<<< orphan*/  deferred_bio_list; struct pool* pool; } ;
struct pool {int dummy; } ;
struct dm_bio_prison_cell {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cell_release (struct pool*,struct dm_bio_prison_cell*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_worker (struct pool*) ; 

__attribute__((used)) static void cell_defer(struct thin_c *tc, struct dm_bio_prison_cell *cell)
{
	struct pool *pool = tc->pool;
	unsigned long flags;

	spin_lock_irqsave(&tc->lock, flags);
	cell_release(pool, cell, &tc->deferred_bio_list);
	spin_unlock_irqrestore(&tc->lock, flags);

	wake_worker(pool);
}