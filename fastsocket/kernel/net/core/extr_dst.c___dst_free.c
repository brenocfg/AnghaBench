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
struct dst_entry {struct dst_entry* next; } ;
struct TYPE_2__ {scalar_t__ timer_inc; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer_expires; struct dst_entry* list; } ;

/* Variables and functions */
 scalar_t__ DST_GC_INC ; 
 int /*<<< orphan*/  DST_GC_MIN ; 
 int /*<<< orphan*/  ___dst_free (struct dst_entry*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 TYPE_1__ dst_garbage ; 
 int /*<<< orphan*/  dst_gc_work ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void __dst_free(struct dst_entry * dst)
{
	spin_lock_bh(&dst_garbage.lock);
	___dst_free(dst);
	dst->next = dst_garbage.list;
	dst_garbage.list = dst;
	if (dst_garbage.timer_inc > DST_GC_INC) {
		dst_garbage.timer_inc = DST_GC_INC;
		dst_garbage.timer_expires = DST_GC_MIN;
		cancel_delayed_work(&dst_gc_work);
		schedule_delayed_work(&dst_gc_work, dst_garbage.timer_expires);
	}
	spin_unlock_bh(&dst_garbage.lock);
}