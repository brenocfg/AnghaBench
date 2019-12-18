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
struct TYPE_2__ {int current_pstate; } ;
struct cpudata {TYPE_1__ pstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pstate_set_pstate (struct cpudata*,int) ; 

__attribute__((used)) static inline void intel_pstate_pstate_increase(struct cpudata *cpu, int steps)
{
	int target;
	target = cpu->pstate.current_pstate + steps;

	intel_pstate_set_pstate(cpu, target);
}