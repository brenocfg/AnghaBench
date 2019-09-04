#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int DEBUGGER_NO_CPU ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atomic_compare_exchange_strong (int*,int*,int) ; 
 int cpu_number () ; 
 int debugger_cpu ; 
 scalar_t__ ml_get_interrupts_enabled () ; 

__attribute__((used)) static void
DebuggerLock()
{
	int my_cpu = cpu_number();
	int debugger_exp_cpu = DEBUGGER_NO_CPU;
	assert(ml_get_interrupts_enabled() == FALSE);

	if (debugger_cpu == my_cpu) {
		return;
	}

	while(!atomic_compare_exchange_strong(&debugger_cpu, &debugger_exp_cpu, my_cpu)) {
		debugger_exp_cpu = DEBUGGER_NO_CPU;
	}

	return;
}