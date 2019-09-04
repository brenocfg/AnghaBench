#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
typedef  TYPE_2__* processor_t ;
typedef  scalar_t__ perfcontrol_class_t ;
typedef  int boolean_t ;
typedef  int /*<<< orphan*/  ast_t ;
struct TYPE_14__ {scalar_t__ state; scalar_t__ current_perfctl_class; int /*<<< orphan*/  current_recommended_pset_type; int /*<<< orphan*/  current_sfi_class; int /*<<< orphan*/  current_pri; TYPE_1__* active_thread; } ;
struct TYPE_13__ {int /*<<< orphan*/  sfi_class; int /*<<< orphan*/  sched_pri; } ;

/* Variables and functions */
 int /*<<< orphan*/  AST_NONE ; 
 int /*<<< orphan*/  PERFCONTROL_ATTR_UPDATE ; 
 scalar_t__ PROCESSOR_RUNNING ; 
 scalar_t__ PROCESSOR_SHUTDOWN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ast_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ast_propagate (TYPE_1__*) ; 
 int /*<<< orphan*/  csw_check (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  mach_approximate_time () ; 
 int /*<<< orphan*/  machine_switch_perfcontrol_state_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  recommended_pset_type (TYPE_1__*) ; 
 int /*<<< orphan*/  sfi_thread_classify (TYPE_1__*) ; 
 scalar_t__ thread_get_perfcontrol_class (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 

void
ast_check(processor_t processor)
{
	if (processor->state != PROCESSOR_RUNNING &&
	    processor->state != PROCESSOR_SHUTDOWN)
		return;

	thread_t thread = processor->active_thread;

	assert(thread == current_thread());

	thread_lock(thread);

	/*
	 * Propagate thread ast to processor.
	 * (handles IPI in response to setting AST flag)
	 */
	ast_propagate(thread);

	boolean_t needs_callout = false;
	processor->current_pri = thread->sched_pri;
	processor->current_sfi_class = thread->sfi_class = sfi_thread_classify(thread);
	processor->current_recommended_pset_type = recommended_pset_type(thread);
	perfcontrol_class_t thread_class = thread_get_perfcontrol_class(thread);
	if (thread_class != processor->current_perfctl_class) {
	    /* We updated the perfctl class of this thread from another core. 
	     * Since we dont do CLPC callouts from another core, do a callout
	     * here to let CLPC know that the currently running thread has a new
	     * class.
	     */
	    needs_callout = true;
	}
	processor->current_perfctl_class = thread_class;

	ast_t preempt;

	if ((preempt = csw_check(processor, AST_NONE)) != AST_NONE)
		ast_on(preempt);

	thread_unlock(thread);

	if (needs_callout) {
	    machine_switch_perfcontrol_state_update(PERFCONTROL_ATTR_UPDATE,
		    mach_approximate_time(), 0, thread);
	}
}