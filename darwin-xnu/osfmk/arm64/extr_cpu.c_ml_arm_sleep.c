#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ cpu_sleep_token; scalar_t__* coresight_base; } ;
typedef  TYPE_1__ cpu_data_t ;
struct TYPE_6__ {scalar_t__ cpu_data_vaddr; } ;
typedef  int /*<<< orphan*/  SleepToken ;

/* Variables and functions */
 scalar_t__ ARM_CPU_ON_SLEEP_PATH ; 
 scalar_t__ ARM_DBG_LOCK_ACCESS_KEY ; 
 scalar_t__ ARM_DEBUG_OFFSET_DBGLAR ; 
 scalar_t__ ARM_DEBUG_OFFSET_DBGPRCR ; 
 TYPE_1__ BootCpuData ; 
 size_t CORESIGHT_ED ; 
 int /*<<< orphan*/  CleanPoU_Dcache () ; 
 int /*<<< orphan*/  CleanPoU_DcacheRegion (scalar_t__,int) ; 
 TYPE_3__* CpuDataEntries ; 
 int /*<<< orphan*/  DMB_ISH ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  __builtin_arm_dmb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __builtin_arm_wfe () ; 
 int /*<<< orphan*/  arm64_prepare_for_sleep () ; 
 scalar_t__ arm64_stall_sleep ; 
 int /*<<< orphan*/  bcopy (void const*,void*,int) ; 
 TYPE_1__* getCpuDatap () ; 
 int ml_get_max_cpu_number () ; 
 int /*<<< orphan*/  ml_get_timebase () ; 
 int /*<<< orphan*/  mt_sleep () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  platform_cache_shutdown () ; 
 scalar_t__ sleepTokenBuffer ; 
 scalar_t__ suspend_signature ; 
 int /*<<< orphan*/  wake_abstime ; 

__attribute__((noreturn))
void
ml_arm_sleep(void)
{
	cpu_data_t		*cpu_data_ptr = getCpuDatap();

	if (cpu_data_ptr == &BootCpuData) {
		cpu_data_t      *target_cdp;
		int		cpu;
		int		max_cpu;

		max_cpu = ml_get_max_cpu_number();
		for (cpu=0; cpu <= max_cpu; cpu++) {
			target_cdp = (cpu_data_t *)CpuDataEntries[cpu].cpu_data_vaddr;

			if ((target_cdp == NULL) || (target_cdp == cpu_data_ptr))
				continue;

			while (target_cdp->cpu_sleep_token != ARM_CPU_ON_SLEEP_PATH);
		}

		/*
		 * Now that the other cores have entered the sleep path, set
		 * the abstime value we'll use when we resume.
		 */
		wake_abstime = ml_get_timebase();
	} else {
		CleanPoU_Dcache();
	}

	cpu_data_ptr->cpu_sleep_token = ARM_CPU_ON_SLEEP_PATH;

	if (cpu_data_ptr == &BootCpuData) {
#if WITH_CLASSIC_S2R
		// Classic suspend to RAM writes the suspend signature into the
		// sleep token buffer so that iBoot knows that it's on the warm
		// boot (wake) path (as opposed to the cold boot path). Newer SoC
		// do not go through SecureROM/iBoot on the warm boot path. The
		// reconfig engine script brings the CPU out of reset at the kernel's
		// reset vector which points to the warm boot initialization code.
		if(sleepTokenBuffer != (vm_offset_t) NULL) {
			platform_cache_shutdown();
			bcopy((const void *)suspend_signature, (void *)sleepTokenBuffer, sizeof(SleepToken));
		}
		else {
			panic("No sleep token buffer");
		}
#endif

#if __ARM_GLOBAL_SLEEP_BIT__
		/* Allow other CPUs to go to sleep. */
		arm64_stall_sleep = FALSE;
		__builtin_arm_dmb(DMB_ISH);
#endif

		/* Architectural debug state: <rdar://problem/12390433>:
		 * 	Grab debug lock EDLAR and clear bit 0 in EDPRCR,
		 * 	tell debugger to not prevent power gating .
		 */
		if (cpu_data_ptr->coresight_base[CORESIGHT_ED]) {
			*(volatile uint32_t *)(cpu_data_ptr->coresight_base[CORESIGHT_ED] + ARM_DEBUG_OFFSET_DBGLAR) = ARM_DBG_LOCK_ACCESS_KEY;
			*(volatile uint32_t *)(cpu_data_ptr->coresight_base[CORESIGHT_ED] + ARM_DEBUG_OFFSET_DBGPRCR) = 0;
		}

#if MONOTONIC
		mt_sleep();
#endif /* MONOTONIC */
		/* ARM64-specific preparation */
		arm64_prepare_for_sleep();
	} else {
#if __ARM_GLOBAL_SLEEP_BIT__
		/*
		 * With the exception of the CPU revisions listed above, our ARM64 CPUs have a
		 * global register to manage entering deep sleep, as opposed to a per-CPU
		 * register.  We cannot update this register until all CPUs are ready to enter
		 * deep sleep, because if a CPU executes WFI outside of the deep sleep context
		 * (by idling), it will hang (due to the side effects of enabling deep sleep),
		 * which can hang the sleep process or cause memory corruption on wake.
		 *
		 * To avoid these issues, we'll stall on this global value, which CPU0 will
		 * manage.
		 */
		while (arm64_stall_sleep) {
			__builtin_arm_wfe();
		}
#endif
		CleanPoU_DcacheRegion((vm_offset_t) cpu_data_ptr, sizeof(cpu_data_t));

		/* Architectural debug state: <rdar://problem/12390433>:
		 * 	Grab debug lock EDLAR and clear bit 0 in EDPRCR,
		 * 	tell debugger to not prevent power gating .
		 */
		if (cpu_data_ptr->coresight_base[CORESIGHT_ED]) {
			*(volatile uint32_t *)(cpu_data_ptr->coresight_base[CORESIGHT_ED] + ARM_DEBUG_OFFSET_DBGLAR) = ARM_DBG_LOCK_ACCESS_KEY;
			*(volatile uint32_t *)(cpu_data_ptr->coresight_base[CORESIGHT_ED] + ARM_DEBUG_OFFSET_DBGPRCR) = 0;
		}

		/* ARM64-specific preparation */
		arm64_prepare_for_sleep();
	}
}