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
typedef  union map_info {int dummy; } map_info ;
struct pool_c {TYPE_1__* data_dev; struct pool* pool; } ;
struct pool {int /*<<< orphan*/  lock; } ;
struct dm_target {struct pool_c* private; } ;
struct bio {int /*<<< orphan*/  bi_bdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int DM_MAPIO_REMAPPED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pool_map(struct dm_target *ti, struct bio *bio,
		    union map_info *map_context)
{
	int r;
	struct pool_c *pt = ti->private;
	struct pool *pool = pt->pool;
	unsigned long flags;

	/*
	 * As this is a singleton target, ti->begin is always zero.
	 */
	spin_lock_irqsave(&pool->lock, flags);
	bio->bi_bdev = pt->data_dev->bdev;
	r = DM_MAPIO_REMAPPED;
	spin_unlock_irqrestore(&pool->lock, flags);

	return r;
}