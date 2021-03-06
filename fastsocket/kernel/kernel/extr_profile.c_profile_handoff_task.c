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
 int NOTIFY_OK ; 
 int atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct task_struct*) ; 
 int /*<<< orphan*/  task_free_notifier ; 

int profile_handoff_task(struct task_struct *task)
{
	int ret;
	ret = atomic_notifier_call_chain(&task_free_notifier, 0, task);
	return (ret == NOTIFY_OK) ? 1 : 0;
}