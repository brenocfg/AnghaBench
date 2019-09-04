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
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int state; scalar_t__ runq; int /*<<< orphan*/  kernel_stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PROCESSOR_NULL ; 
 int TH_RUN ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static inline boolean_t
thread_isoncpu(thread_t thread)
{
	/* Not running or runnable */
	if (!(thread->state & TH_RUN))
		return (FALSE);

	/* Waiting on a runqueue, not currently running */
	/* TODO: This is invalid - it can get dequeued without thread lock, but not context switched. */
	if (thread->runq != PROCESSOR_NULL)
		return (FALSE);

	/*
	 * Thread does not have a stack yet
	 * It could be on the stack alloc queue or preparing to be invoked
	 */
	if (!thread->kernel_stack)
		return (FALSE);

	/*
	 * Thread must be running on a processor, or
	 * about to run, or just did run. In all these
	 * cases, an AST to the processor is needed
	 * to guarantee that the thread is kicked out
	 * of userspace and the processor has
	 * context switched (and saved register state).
	 */
	return (TRUE);
}