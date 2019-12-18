#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_CSTATE ; 
 int /*<<< orphan*/  TS_POLLING ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_1__* current_thread_info () ; 
 scalar_t__ hlt_use_halt () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  safe_halt () ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  trace_power_start (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void default_idle(void)
{
	if (hlt_use_halt()) {
		trace_power_start(POWER_CSTATE, 1, smp_processor_id());
		current_thread_info()->status &= ~TS_POLLING;
		/*
		 * TS_POLLING-cleared state must be visible before we
		 * test NEED_RESCHED:
		 */
		smp_mb();

		if (!need_resched())
			safe_halt();	/* enables interrupts racelessly */
		else
			local_irq_enable();
		current_thread_info()->status |= TS_POLLING;
	} else {
		local_irq_enable();
		/* loop is done by the caller */
		cpu_relax();
	}
}