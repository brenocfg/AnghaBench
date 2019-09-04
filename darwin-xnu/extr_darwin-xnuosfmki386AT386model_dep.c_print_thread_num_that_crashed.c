#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* task_t ;
struct TYPE_6__ {int thread_count; int /*<<< orphan*/  threads; } ;
struct TYPE_5__ {int /*<<< orphan*/  task_threads; } ;

/* Variables and functions */
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  paniclog_append_noflush (char*,int) ; 
 scalar_t__ queue_first (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_next (int /*<<< orphan*/ *) ; 

void
print_thread_num_that_crashed(task_t task)
{
	thread_t		c_thread = current_thread();
	thread_t		thread;
	int             j;
	
	for (j = 0, thread = (thread_t) queue_first(&task->threads); j < task->thread_count;
			++j, thread = (thread_t) queue_next(&thread->task_threads)) {

		if (c_thread == thread) {
			paniclog_append_noflush("\nThread %d crashed\n", j);
			break;
		}
	}
}