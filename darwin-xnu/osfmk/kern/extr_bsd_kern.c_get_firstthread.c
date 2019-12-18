#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ thread_t ;
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  queue_entry_t ;
struct TYPE_3__ {int /*<<< orphan*/  active; int /*<<< orphan*/  threads; } ;

/* Variables and functions */
 scalar_t__ THREAD_NULL ; 
 scalar_t__ queue_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_first (int /*<<< orphan*/ *) ; 

thread_t get_firstthread(task_t task)
{
	thread_t	thread = (thread_t)(void *)queue_first(&task->threads);

	if (queue_end(&task->threads, (queue_entry_t)thread))
		thread = THREAD_NULL;

	if (!task->active)
		return (THREAD_NULL);

	return (thread);
}