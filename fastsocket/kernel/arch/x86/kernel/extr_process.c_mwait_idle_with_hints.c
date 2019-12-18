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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_CSTATE ; 
 int /*<<< orphan*/  X86_FEATURE_CLFLUSH_MONITOR ; 
 int /*<<< orphan*/  __monitor (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mwait (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  clflush (void*) ; 
 scalar_t__ cpu_has (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_cpu_data ; 
 TYPE_1__* current_thread_info () ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  trace_power_start (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

void mwait_idle_with_hints(unsigned long ax, unsigned long cx)
{
	trace_power_start(POWER_CSTATE, (ax>>4)+1, smp_processor_id());
	if (!need_resched()) {
		if (cpu_has(&current_cpu_data, X86_FEATURE_CLFLUSH_MONITOR))
			clflush((void *)&current_thread_info()->flags);

		__monitor((void *)&current_thread_info()->flags, 0, 0);
		smp_mb();
		if (!need_resched())
			__mwait(ax, cx);
	}
}