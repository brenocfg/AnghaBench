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
typedef  int /*<<< orphan*/  spl_t ;
typedef  TYPE_1__* processor_t ;
typedef  int /*<<< orphan*/  processor_set_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  cpu_id; int /*<<< orphan*/  processor_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ PROCESSOR_DISPATCHING ; 
 scalar_t__ PROCESSOR_OFF_LINE ; 
 scalar_t__ PROCESSOR_SHUTDOWN ; 
 scalar_t__ PROCESSOR_START ; 
 int /*<<< orphan*/  cpu_exit_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/  processor_doshutdown (TYPE_1__*) ; 
 int /*<<< orphan*/  pset_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pset_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pset_update_processor_state (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 

kern_return_t
processor_shutdown(
	processor_t			processor)
{
	processor_set_t		pset;
	spl_t				s;

	s = splsched();
	pset = processor->processor_set;
	pset_lock(pset);
	if (processor->state == PROCESSOR_OFF_LINE) {
		/*
		 * Success if already shutdown.
		 */
		pset_unlock(pset);
		splx(s);

		return (KERN_SUCCESS);
	}

	if (processor->state == PROCESSOR_START) {
		/*
		 * Failure if currently being started.
		 */
		pset_unlock(pset);
		splx(s);

		return (KERN_FAILURE);
	}

	/*
	 * If the processor is dispatching, let it finish.
	 */
	while (processor->state == PROCESSOR_DISPATCHING) {
		pset_unlock(pset);
		splx(s);
		delay(1);
		s = splsched();
		pset_lock(pset);
	}

	/*
	 * Success if already being shutdown.
	 */
	if (processor->state == PROCESSOR_SHUTDOWN) {
		pset_unlock(pset);
		splx(s);

		return (KERN_SUCCESS);
	}

	pset_update_processor_state(pset, processor, PROCESSOR_SHUTDOWN);

	pset_unlock(pset);

	processor_doshutdown(processor);
	splx(s);

	cpu_exit_wait(processor->cpu_id);

	return (KERN_SUCCESS);
}