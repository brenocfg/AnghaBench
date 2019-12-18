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
struct task_struct {int pi_blocked_on; int /*<<< orphan*/  pi_waiters; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  plist_head_empty (int /*<<< orphan*/ *) ; 

void rt_mutex_debug_task_free(struct task_struct *task)
{
	WARN_ON(!plist_head_empty(&task->pi_waiters));
	WARN_ON(task->pi_blocked_on);
}