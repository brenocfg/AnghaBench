#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spl_t ;
typedef  TYPE_1__* processor_t ;
typedef  TYPE_2__* processor_set_t ;
struct TYPE_10__ {int /*<<< orphan*/  online_processor_count; } ;
struct TYPE_9__ {int /*<<< orphan*/  cpu_id; TYPE_2__* processor_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROCESSOR_RUNNING ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  commpage_update_active_cpus () ; 
 int /*<<< orphan*/  dtrace_cpu_state_changed_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_atomic_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_ast_check (TYPE_1__*) ; 
 int /*<<< orphan*/  ml_cpu_up () ; 
 int /*<<< orphan*/  processor_avail_count ; 
 int /*<<< orphan*/  pset_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  pset_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  pset_update_processor_state (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
processor_up(
	processor_t			processor)
{
	processor_set_t		pset;
	spl_t				s;

	s = splsched();
	init_ast_check(processor);
	pset = processor->processor_set;
	pset_lock(pset);
	++pset->online_processor_count;
	pset_update_processor_state(pset, processor, PROCESSOR_RUNNING);
	(void)hw_atomic_add(&processor_avail_count, 1);
	commpage_update_active_cpus();
	pset_unlock(pset);
	ml_cpu_up();
	splx(s);

#if CONFIG_DTRACE
	if (dtrace_cpu_state_changed_hook)
		(*dtrace_cpu_state_changed_hook)(processor->cpu_id, TRUE);
#endif
}