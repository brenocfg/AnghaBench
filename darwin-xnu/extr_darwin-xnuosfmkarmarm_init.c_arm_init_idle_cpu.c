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
struct TYPE_3__ {int /*<<< orphan*/  cpu_active_thread; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cpu_idle_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fiq_context_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_set_current_thread (int /*<<< orphan*/ ) ; 

void __attribute__((noreturn))
arm_init_idle_cpu(
	cpu_data_t	*cpu_data_ptr)
{
#if __ARM_PAN_AVAILABLE__
	__builtin_arm_wsr("pan", 1);
#endif
#if     __ARM_SMP__ && defined(ARMA7)
	cpu_data_ptr->cpu_CLW_active = 1;
#endif

	machine_set_current_thread(cpu_data_ptr->cpu_active_thread);

#if __arm64__
	pmap_clear_user_ttb();
	flush_mmu_tlb();
	/* Enable asynchronous exceptions */
	__builtin_arm_wsr("DAIFClr", DAIFSC_ASYNCF);
#endif

#if	(__ARM_ARCH__ == 7)
	if (arm_diag & 0x8000)
		set_mmu_control((get_mmu_control()) ^ SCTLR_PREDIC);
#endif
#ifdef	APPLETYPHOON
	if ((cpus_defeatures & (0xF << 4*cpu_data_ptr->cpu_number)) != 0)
		cpu_defeatures_set((cpus_defeatures >> 4*cpu_data_ptr->cpu_number) & 0xF);
#endif

	fiq_context_init(FALSE);

	cpu_idle_exit(TRUE);
}