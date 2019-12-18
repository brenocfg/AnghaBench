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
struct task_struct {int dummy; } ;
struct o2hb_region {int /*<<< orphan*/  hr_steady_iterations; struct task_struct* hr_task; } ;
struct config_item {int dummy; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_item_put (struct config_item*) ; 
 int /*<<< orphan*/  kthread_stop (struct task_struct*) ; 
 int /*<<< orphan*/  o2hb_live_lock ; 
 int /*<<< orphan*/  o2hb_steady_queue ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct o2hb_region* to_o2hb_region (struct config_item*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void o2hb_heartbeat_group_drop_item(struct config_group *group,
					   struct config_item *item)
{
	struct task_struct *hb_task;
	struct o2hb_region *reg = to_o2hb_region(item);

	/* stop the thread when the user removes the region dir */
	spin_lock(&o2hb_live_lock);
	hb_task = reg->hr_task;
	reg->hr_task = NULL;
	spin_unlock(&o2hb_live_lock);

	if (hb_task)
		kthread_stop(hb_task);

	/*
	 * If we're racing a dev_write(), we need to wake them.  They will
	 * check reg->hr_task
	 */
	if (atomic_read(&reg->hr_steady_iterations) != 0) {
		atomic_set(&reg->hr_steady_iterations, 0);
		wake_up(&o2hb_steady_queue);
	}

	config_item_put(item);
}