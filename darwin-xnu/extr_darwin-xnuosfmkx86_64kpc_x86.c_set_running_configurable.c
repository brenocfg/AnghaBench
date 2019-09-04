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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int IA32_PERFEVTSEL_EN ; 
 int IA32_PERFEVTSEL_PMI ; 
 int IA32_PERFEVTSELx (scalar_t__) ; 
 int IA32_PMCx (scalar_t__) ; 
 int /*<<< orphan*/  MSR_IA32_PERF_GLOBAL_CTRL ; 
 scalar_t__ kpc_configurable_count () ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int rdmsr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrIA32_PERFEVTSELx (scalar_t__,int) ; 
 int /*<<< orphan*/  wrIA32_PMCx (scalar_t__,int) ; 
 int /*<<< orphan*/  wrmsr64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
set_running_configurable(uint64_t target_mask, uint64_t state_mask)
{
	uint32_t cfg_count = kpc_configurable_count();
	uint64_t global = 0ULL, cfg = 0ULL, save = 0ULL;
	boolean_t enabled;

	enabled = ml_set_interrupts_enabled(FALSE);

	/* rmw the global control */
	global = rdmsr64(MSR_IA32_PERF_GLOBAL_CTRL);

	/* need to save and restore counter since it resets when reconfigured */
	for (uint32_t i = 0; i < cfg_count; ++i) {
		cfg = IA32_PERFEVTSELx(i);
		save = IA32_PMCx(i);
		wrIA32_PERFEVTSELx(i, cfg | IA32_PERFEVTSEL_PMI | IA32_PERFEVTSEL_EN);
		wrIA32_PMCx(i, save);
	}

	/* update the global control value */
	global &= ~target_mask;	/* clear the targeted PMCs bits */
	global |= state_mask;	/* update the targeted PMCs bits with their new states */
	wrmsr64(MSR_IA32_PERF_GLOBAL_CTRL, global);

	ml_set_interrupts_enabled(enabled);
}