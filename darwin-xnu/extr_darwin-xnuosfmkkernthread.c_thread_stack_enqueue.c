#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  event_t ;
struct TYPE_5__ {int /*<<< orphan*/  runq_links; } ;

/* Variables and functions */
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DBG_MACH_SCHED ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_STACK_WAIT ; 
 int /*<<< orphan*/  assert_thread_magic (TYPE_1__*) ; 
 int /*<<< orphan*/  enqueue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_stack_lock ; 
 int /*<<< orphan*/  thread_stack_queue ; 
 int /*<<< orphan*/  thread_tid (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 

void
thread_stack_enqueue(
	thread_t		thread)
{
	KERNEL_DEBUG_CONSTANT(MACHDBG_CODE(DBG_MACH_SCHED,MACH_STACK_WAIT) | DBG_FUNC_START, thread_tid(thread), 0, 0, 0, 0);
	assert_thread_magic(thread);

	simple_lock(&thread_stack_lock);
	enqueue_tail(&thread_stack_queue, &thread->runq_links);
	simple_unlock(&thread_stack_lock);

	thread_wakeup((event_t)&thread_stack_queue);
}