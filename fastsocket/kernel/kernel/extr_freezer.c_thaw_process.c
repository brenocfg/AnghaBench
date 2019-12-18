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

/* Variables and functions */
 int __thaw_process (struct task_struct*) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

int thaw_process(struct task_struct *p)
{
	task_lock(p);
	if (__thaw_process(p) == 1) {
		task_unlock(p);
		wake_up_process(p);
		return 1;
	}
	task_unlock(p);
	return 0;
}