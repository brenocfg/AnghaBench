#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  current_pstate; int /*<<< orphan*/  turbo_pstate; } ;
struct cpudata {size_t sample_ptr; TYPE_2__ pstate; TYPE_1__* samples; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  core_pct_busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  div_fp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fp_toint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_tofp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul_fp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int intel_pstate_get_scaled_busy(struct cpudata *cpu)
{
	int32_t busy_scaled;
	int32_t core_busy, turbo_pstate, current_pstate;

	core_busy = int_tofp(cpu->samples[cpu->sample_ptr].core_pct_busy);
	turbo_pstate = int_tofp(cpu->pstate.turbo_pstate);
	current_pstate = int_tofp(cpu->pstate.current_pstate);
	busy_scaled = mul_fp(core_busy, div_fp(turbo_pstate, current_pstate));

	return fp_toint(busy_scaled);
}