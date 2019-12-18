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
typedef  int /*<<< orphan*/  run_queue_t ;
typedef  int /*<<< orphan*/  processor_t ;
typedef  int /*<<< orphan*/  integer_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  runq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dualq_runq_for_thread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  run_queue_enqueue (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
sched_dualq_processor_enqueue(
                              processor_t       processor,
                              thread_t          thread,
                              integer_t         options)
{
	run_queue_t     rq = dualq_runq_for_thread(processor, thread);
	boolean_t       result;

	result = run_queue_enqueue(rq, thread, options);
	thread->runq = processor;

	return (result);
}