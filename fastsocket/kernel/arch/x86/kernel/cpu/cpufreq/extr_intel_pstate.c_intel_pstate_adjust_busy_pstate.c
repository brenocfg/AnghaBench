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
struct _pid {int dummy; } ;
struct cpudata {struct _pid pid; } ;

/* Variables and functions */
 int abs (int) ; 
 int intel_pstate_get_scaled_busy (struct cpudata*) ; 
 int /*<<< orphan*/  intel_pstate_pstate_decrease (struct cpudata*,int) ; 
 int /*<<< orphan*/  intel_pstate_pstate_increase (struct cpudata*,int) ; 
 int pid_calc (struct _pid*,int) ; 

__attribute__((used)) static inline void intel_pstate_adjust_busy_pstate(struct cpudata *cpu)
{
	int busy_scaled;
	struct _pid *pid;
	signed int ctl = 0;
	int steps;

	pid = &cpu->pid;
	busy_scaled = intel_pstate_get_scaled_busy(cpu);

	ctl = pid_calc(pid, busy_scaled);

	steps = abs(ctl);
	if (ctl < 0)
		intel_pstate_pstate_increase(cpu, steps);
	else
		intel_pstate_pstate_decrease(cpu, steps);
}