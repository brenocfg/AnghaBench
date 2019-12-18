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
struct TYPE_2__ {int /*<<< orphan*/  max_pstate; int /*<<< orphan*/  turbo_pstate; int /*<<< orphan*/  min_pstate; } ;
struct cpudata {TYPE_1__ pstate; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pstate_max_pstate () ; 
 int /*<<< orphan*/  intel_pstate_min_pstate () ; 
 int /*<<< orphan*/  intel_pstate_set_pstate (struct cpudata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pstate_turbo_pstate () ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void intel_pstate_get_cpu_pstates(struct cpudata *cpu)
{
	sprintf(cpu->name, "Intel 2nd generation core");

	cpu->pstate.min_pstate = intel_pstate_min_pstate();
	cpu->pstate.max_pstate = intel_pstate_max_pstate();
	cpu->pstate.turbo_pstate = intel_pstate_turbo_pstate();

	/*
	 * goto max pstate so we don't slow up boot if we are built-in if we are
	 * a module we will take care of it during normal operation
	 */
	intel_pstate_set_pstate(cpu, cpu->pstate.max_pstate);
}