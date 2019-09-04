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
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  int /*<<< orphan*/  task_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int /*<<< orphan*/  TH_OPTION_NONE ; 
 int /*<<< orphan*/  kThreadWaitNone ; 
 int /*<<< orphan*/  thread_create_waiting_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
thread_create_waiting(
	task_t                  task,
	thread_continue_t       continuation,
	event_t                 event,
	thread_t                *new_thread)
{
	return thread_create_waiting_internal(task, continuation, event,
			kThreadWaitNone, TH_OPTION_NONE, new_thread);
}