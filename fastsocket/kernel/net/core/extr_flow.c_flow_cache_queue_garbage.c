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
struct list_head {int dummy; } ;
struct flow_cache_percpu {int hash_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  flow_cache_gc_list ; 
 int /*<<< orphan*/  flow_cache_gc_lock ; 
 int /*<<< orphan*/  flow_cache_gc_work ; 
 int /*<<< orphan*/  list_splice_tail (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flow_cache_queue_garbage(struct flow_cache_percpu *fcp,
				     int deleted, struct list_head *gc_list)
{
	if (deleted) {
		fcp->hash_count -= deleted;
		spin_lock_bh(&flow_cache_gc_lock);
		list_splice_tail(gc_list, &flow_cache_gc_list);
		spin_unlock_bh(&flow_cache_gc_lock);
		schedule_work(&flow_cache_gc_work);
	}
}