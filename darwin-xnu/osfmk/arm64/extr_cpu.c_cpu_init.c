#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ timer_cnt_wake; scalar_t__ ipi_cnt_wake; scalar_t__ irq_ex_cnt_wake; } ;
struct TYPE_10__ {int /*<<< orphan*/  deadline; int /*<<< orphan*/  queue; } ;
struct TYPE_13__ {scalar_t__ cpu_type; int cpu_sleep_token_last; int cpu_sleep_token; int /*<<< orphan*/  cpu_running; TYPE_3__ cpu_stat; int /*<<< orphan*/  cpu_threadtype; int /*<<< orphan*/  cpu_subtype; TYPE_1__ rtclock_timer; } ;
typedef  TYPE_4__ cpu_data_t ;
struct TYPE_11__ {int arm_arch; } ;
struct TYPE_14__ {TYPE_2__ arm_info; } ;
typedef  TYPE_5__ arm_cpu_info_t ;

/* Variables and functions */
 TYPE_4__ BootCpuData ; 
#define  CPU_ARCH_ARMv8 128 
 int /*<<< orphan*/  CPU_SUBTYPE_ARM64_V8 ; 
 int /*<<< orphan*/  CPU_THREADTYPE_NONE ; 
 scalar_t__ CPU_TYPE_ARM64 ; 
 int /*<<< orphan*/  EndOfAllTime ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_5__* cpuid_info () ; 
 int /*<<< orphan*/  do_cacheid () ; 
 int /*<<< orphan*/  do_cpuid () ; 
 int /*<<< orphan*/  do_debugid () ; 
 int /*<<< orphan*/  do_mvfpid () ; 
 scalar_t__ exception_stack_pointer () ; 
 TYPE_4__* getCpuDatap () ; 
 int /*<<< orphan*/  kpc_idle_exit () ; 
 int /*<<< orphan*/  mt_cpu_up (TYPE_4__*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_cpu_data_init () ; 
 int /*<<< orphan*/  timer_call_queue_init (int /*<<< orphan*/ *) ; 

void
cpu_init(void)
{
	cpu_data_t     *cdp = getCpuDatap();
	arm_cpu_info_t *cpu_info_p;

	assert(exception_stack_pointer() != 0);

	if (cdp->cpu_type != CPU_TYPE_ARM64) {

		cdp->cpu_type = CPU_TYPE_ARM64;

		timer_call_queue_init(&cdp->rtclock_timer.queue);
		cdp->rtclock_timer.deadline = EndOfAllTime;

		if (cdp == &BootCpuData) {
			do_cpuid();
			do_cacheid();
			do_mvfpid();
		} else {
			/*
			 * We initialize non-boot CPUs here; the boot CPU is
			 * dealt with as part of pmap_bootstrap.
			 */
			pmap_cpu_data_init();
		}
		/* ARM_SMP: Assuming identical cpu */
		do_debugid();

		cpu_info_p = cpuid_info();

		/* switch based on CPU's reported architecture */
		switch (cpu_info_p->arm_info.arm_arch) {
		case CPU_ARCH_ARMv8:
			cdp->cpu_subtype = CPU_SUBTYPE_ARM64_V8;
			break;
		default:
			//cdp->cpu_subtype = CPU_SUBTYPE_ARM64_ALL;
			/* this panic doesn't work this early in startup */
			panic("Unknown CPU subtype...");
			break;
		}

		cdp->cpu_threadtype = CPU_THREADTYPE_NONE;
	}
	cdp->cpu_stat.irq_ex_cnt_wake = 0;
	cdp->cpu_stat.ipi_cnt_wake = 0;
	cdp->cpu_stat.timer_cnt_wake = 0;
	cdp->cpu_running = TRUE;
	cdp->cpu_sleep_token_last = cdp->cpu_sleep_token;
	cdp->cpu_sleep_token = 0x0UL;
#if KPC
	kpc_idle_exit();
#endif /* KPC */
#if MONOTONIC
	mt_cpu_up(cdp);
#endif /* MONOTONIC */
}