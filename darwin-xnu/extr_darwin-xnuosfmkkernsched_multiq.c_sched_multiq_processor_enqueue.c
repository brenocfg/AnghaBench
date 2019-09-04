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
typedef  scalar_t__ processor_t ;
typedef  int /*<<< orphan*/  integer_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {scalar_t__ chosen_processor; scalar_t__ bound_processor; scalar_t__ runq; int /*<<< orphan*/  sched_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PROCESSOR_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  multiq_bound_runq (scalar_t__) ; 
 int /*<<< orphan*/  multiq_main_entryq (scalar_t__) ; 
 int /*<<< orphan*/  run_queue_enqueue (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_group_enqueue_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
sched_multiq_processor_enqueue(
                               processor_t      processor,
                               thread_t         thread,
                               integer_t        options)
{
	boolean_t       result;

	assert(processor == thread->chosen_processor);

	if (thread->bound_processor != PROCESSOR_NULL) {
		assert(thread->bound_processor == processor);

		result = run_queue_enqueue(multiq_bound_runq(processor), thread, options);
		thread->runq = processor;

		return result;
	}

	sched_group_enqueue_thread(multiq_main_entryq(processor),
	                           thread->sched_group,
	                           thread, options);

	thread->runq = processor;

	return (FALSE);
}