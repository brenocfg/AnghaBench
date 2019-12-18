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
struct thread_info {struct task_struct* task; } ;
struct task_struct {int dummy; } ;
struct mutex {struct thread_info* owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_is_locked (struct mutex*) ; 

__attribute__((used)) static bool mutex_is_locked_by(struct mutex *mutex, struct task_struct *task)
{
	if (!mutex_is_locked(mutex))
		return false;
#if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_MUTEXES)
	else {
		struct thread_info *owner = mutex->owner;
		if (owner)
			return owner->task == task;
	}
#endif
	/* Since UP may be pre-empted, we cannot assume that we own the lock */
	return false;
}