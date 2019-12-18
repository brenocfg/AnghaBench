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
struct rds_ib_refill_cache {int /*<<< orphan*/  xfer; int /*<<< orphan*/  percpu; } ;
struct rds_ib_cache_head {scalar_t__ count; struct list_head* first; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 scalar_t__ RDS_IB_RECYCLE_BATCH_COUNT ; 
 struct list_head* cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_add_tail (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  list_splice_entire_tail (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct rds_ib_cache_head* per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 struct list_head* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rds_ib_recv_cache_put(struct list_head *new_item,
				 struct rds_ib_refill_cache *cache)
{
	unsigned long flags;
	struct rds_ib_cache_head *chp;
	struct list_head *old;

	local_irq_save(flags);

	chp = per_cpu_ptr(cache->percpu, smp_processor_id());
	if (!chp->first)
		INIT_LIST_HEAD(new_item);
	else /* put on front */
		list_add_tail(new_item, chp->first);
	chp->first = new_item;
	chp->count++;

	if (chp->count < RDS_IB_RECYCLE_BATCH_COUNT)
		goto end;

	/*
	 * Return our per-cpu first list to the cache's xfer by atomically
	 * grabbing the current xfer list, appending it to our per-cpu list,
	 * and then atomically returning that entire list back to the
	 * cache's xfer list as long as it's still empty.
	 */
	do {
		old = xchg(&cache->xfer, NULL);
		if (old)
			list_splice_entire_tail(old, chp->first);
		old = cmpxchg(&cache->xfer, NULL, chp->first);
	} while (old);

	chp->first = NULL;
	chp->count = 0;
end:
	local_irq_restore(flags);
}