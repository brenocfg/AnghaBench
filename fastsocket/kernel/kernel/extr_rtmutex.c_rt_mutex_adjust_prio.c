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
struct task_struct {int /*<<< orphan*/  pi_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rt_mutex_adjust_prio (struct task_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rt_mutex_adjust_prio(struct task_struct *task)
{
	unsigned long flags;

	spin_lock_irqsave(&task->pi_lock, flags);
	__rt_mutex_adjust_prio(task);
	spin_unlock_irqrestore(&task->pi_lock, flags);
}