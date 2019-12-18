#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* processor_t ;
struct TYPE_8__ {scalar_t__ cpu_id; } ;
struct TYPE_7__ {scalar_t__ sched_pri; scalar_t__ runq; TYPE_2__* bound_processor; } ;

/* Variables and functions */
 scalar_t__ BASEPRI_RTQUEUES ; 
 int /*<<< orphan*/  DBG_MACH_SCHED ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_THREAD_BIND ; 
 scalar_t__ PROCESSOR_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  thread_tid (TYPE_1__*) ; 

__attribute__((used)) static processor_t
thread_bind_internal(
	thread_t		thread,
	processor_t		processor)
{
	processor_t		prev;

	/* <rdar://problem/15102234> */
	assert(thread->sched_pri < BASEPRI_RTQUEUES);
	/* A thread can't be bound if it's sitting on a (potentially incorrect) runqueue */
	assert(thread->runq == PROCESSOR_NULL);

	KERNEL_DEBUG_CONSTANT(MACHDBG_CODE(DBG_MACH_SCHED, MACH_THREAD_BIND), thread_tid(thread), processor ? (uintptr_t)processor->cpu_id : (uintptr_t)-1, 0, 0, 0);

	prev = thread->bound_processor;
	thread->bound_processor = processor;

	return (prev);
}