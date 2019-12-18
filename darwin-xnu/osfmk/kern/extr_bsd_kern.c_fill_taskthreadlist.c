#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  TYPE_2__* thread_t ;
typedef  TYPE_3__* task_t ;
typedef  int /*<<< orphan*/  queue_entry_t ;
struct TYPE_9__ {int /*<<< orphan*/  threads; } ;
struct TYPE_7__ {int /*<<< orphan*/  cthread_self; } ;
struct TYPE_8__ {int /*<<< orphan*/  task_threads; TYPE_1__ machine; int /*<<< orphan*/  thread_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_first (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  task_unlock (TYPE_3__*) ; 

int
fill_taskthreadlist(task_t task, void * buffer, int thcount, bool thuniqueid)
{
	int numthr=0;
	thread_t thact;
	uint64_t * uptr;
	uint64_t  thaddr;

	uptr = (uint64_t *)buffer;

	task_lock(task);

	for (thact  = (thread_t)(void *)queue_first(&task->threads);
			!queue_end(&task->threads, (queue_entry_t)thact); ) {
		thaddr = (thuniqueid) ? thact->thread_id : thact->machine.cthread_self;
		*uptr++ = thaddr;
		numthr++;
		if (numthr >= thcount)
			goto out;
		thact = (thread_t)(void *)queue_next(&thact->task_threads);
	}

out:
	task_unlock(task);
	return (int)(numthr * sizeof(uint64_t));
	
}