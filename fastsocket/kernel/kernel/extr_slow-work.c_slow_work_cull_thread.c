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

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int slow_work_cull ; 
 scalar_t__ slow_work_min_threads ; 
 int /*<<< orphan*/  slow_work_queue ; 
 int /*<<< orphan*/  slow_work_queue_lock ; 
 int /*<<< orphan*/  slow_work_schedule_cull () ; 
 int /*<<< orphan*/  slow_work_thread_count ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vslow_work_queue ; 

__attribute__((used)) static bool slow_work_cull_thread(void)
{
	unsigned long flags;
	bool do_cull = false;

	spin_lock_irqsave(&slow_work_queue_lock, flags);

	if (slow_work_cull) {
		slow_work_cull = false;

		if (list_empty(&slow_work_queue) &&
		    list_empty(&vslow_work_queue) &&
		    atomic_read(&slow_work_thread_count) >
		    slow_work_min_threads) {
			slow_work_schedule_cull();
			do_cull = true;
		}
	}

	spin_unlock_irqrestore(&slow_work_queue_lock, flags);
	return do_cull;
}