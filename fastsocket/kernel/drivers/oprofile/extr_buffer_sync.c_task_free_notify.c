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
struct task_struct {int /*<<< orphan*/  tasks; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_OK ; 
 int /*<<< orphan*/  dying_tasks ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  task_mortuary ; 

__attribute__((used)) static int
task_free_notify(struct notifier_block *self, unsigned long val, void *data)
{
	unsigned long flags;
	struct task_struct *task = data;
	spin_lock_irqsave(&task_mortuary, flags);
	list_add(&task->tasks, &dying_tasks);
	spin_unlock_irqrestore(&task_mortuary, flags);
	return NOTIFY_OK;
}