#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct mt_cpu {int /*<<< orphan*/ * mtc_snaps; } ;
struct TYPE_3__ {struct mt_cpu cpu_monotonic; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int MT_CORE_NFIXED ; 
 int /*<<< orphan*/  PMCR0 ; 
 int PMCR0_FIXED_EN ; 
 int PMCR0_INIT ; 
 int __builtin_arm_rsr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __builtin_arm_wsr64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  core_init_execution_modes () ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  mt_core_set_snap (int,int /*<<< orphan*/ ) ; 

void
mt_cpu_run(cpu_data_t *cpu)
{
	uint64_t pmcr0;
	struct mt_cpu *mtc;

	assert(cpu != NULL);
	assert(ml_get_interrupts_enabled() == FALSE);

	mtc = &cpu->cpu_monotonic;

	for (int i = 0; i < MT_CORE_NFIXED; i++) {
		mt_core_set_snap(i, mtc->mtc_snaps[i]);
	}

	/* re-enable the counters */
	core_init_execution_modes();

	pmcr0 = __builtin_arm_rsr64(PMCR0);
	pmcr0 |= PMCR0_INIT | PMCR0_FIXED_EN;
	__builtin_arm_wsr64(PMCR0, pmcr0);
}