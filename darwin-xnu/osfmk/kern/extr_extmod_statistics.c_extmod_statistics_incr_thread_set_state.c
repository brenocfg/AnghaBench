#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ thread_t ;
typedef  TYPE_2__* task_t ;
struct TYPE_10__ {int /*<<< orphan*/  thread_set_state_count; } ;
struct TYPE_8__ {int /*<<< orphan*/  thread_set_state_count; int /*<<< orphan*/  thread_set_state_caller_count; } ;
struct TYPE_9__ {TYPE_1__ extmod_statistics; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSIncrementAtomic64 (int /*<<< orphan*/ *) ; 
 TYPE_2__* TASK_NULL ; 
 scalar_t__ THREAD_NULL ; 
 TYPE_2__* current_task () ; 
 TYPE_2__* get_threadtask (scalar_t__) ; 
 TYPE_4__ host_extmod_statistics ; 
 TYPE_2__* kernel_task ; 

void
extmod_statistics_incr_thread_set_state(thread_t target)
{
	task_t ctask = current_task();
	task_t ttask;

	if ((ctask == kernel_task) || (target == THREAD_NULL))
		return;

	ttask = get_threadtask(target);

	if (ttask == TASK_NULL)
		return;

	if (ttask != ctask) {
		ctask->extmod_statistics.thread_set_state_caller_count++;
		ttask->extmod_statistics.thread_set_state_count++;
		OSIncrementAtomic64(&host_extmod_statistics.thread_set_state_count);
	}
}