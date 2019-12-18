#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ timer_cnt_wake; scalar_t__ ipi_cnt_wake; scalar_t__ irq_ex_cnt_wake; } ;
struct TYPE_9__ {int /*<<< orphan*/  deadline; int /*<<< orphan*/  queue; } ;
struct TYPE_12__ {scalar_t__ cpu_type; int cpu_sleep_token_last; int cpu_sleep_token; int /*<<< orphan*/  cpu_running; TYPE_3__ cpu_stat; int /*<<< orphan*/  cpu_threadtype; int /*<<< orphan*/  cpu_subtype; TYPE_1__ rtclock_timer; } ;
typedef  TYPE_4__ cpu_data_t ;
struct TYPE_10__ {int arm_arch; int /*<<< orphan*/  arm_implementor; } ;
struct TYPE_13__ {TYPE_2__ arm_info; } ;
typedef  TYPE_5__ arm_cpu_info_t ;

/* Variables and functions */
 TYPE_4__ BootCpuData ; 
#define  CPU_ARCH_ARMv4T 136 
#define  CPU_ARCH_ARMv5T 135 
#define  CPU_ARCH_ARMv5TE 134 
#define  CPU_ARCH_ARMv5TEJ 133 
#define  CPU_ARCH_ARMv6 132 
#define  CPU_ARCH_ARMv7 131 
#define  CPU_ARCH_ARMv7f 130 
#define  CPU_ARCH_ARMv7k 129 
#define  CPU_ARCH_ARMv7s 128 
 int /*<<< orphan*/  CPU_SUBTYPE_ARM_ALL ; 
 int /*<<< orphan*/  CPU_SUBTYPE_ARM_V4T ; 
 int /*<<< orphan*/  CPU_SUBTYPE_ARM_V5TEJ ; 
 int /*<<< orphan*/  CPU_SUBTYPE_ARM_V6 ; 
 int /*<<< orphan*/  CPU_SUBTYPE_ARM_V7 ; 
 int /*<<< orphan*/  CPU_SUBTYPE_ARM_V7F ; 
 int /*<<< orphan*/  CPU_SUBTYPE_ARM_V7K ; 
 int /*<<< orphan*/  CPU_SUBTYPE_ARM_V7S ; 
 int /*<<< orphan*/  CPU_SUBTYPE_ARM_XSCALE ; 
 int /*<<< orphan*/  CPU_THREADTYPE_NONE ; 
 scalar_t__ CPU_TYPE_ARM ; 
 int /*<<< orphan*/  CPU_VID_INTEL ; 
 int /*<<< orphan*/  EndOfAllTime ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_5__* cpuid_info () ; 
 int /*<<< orphan*/  do_cacheid () ; 
 int /*<<< orphan*/  do_cpuid () ; 
 int /*<<< orphan*/  do_debugid () ; 
 int /*<<< orphan*/  do_mvfpid () ; 
 TYPE_4__* getCpuDatap () ; 
 int /*<<< orphan*/  pmap_cpu_data_init () ; 
 int /*<<< orphan*/  timer_call_queue_init (int /*<<< orphan*/ *) ; 

void
cpu_init(void)
{
	cpu_data_t     *cdp = getCpuDatap();
	arm_cpu_info_t *cpu_info_p;

	if (cdp->cpu_type != CPU_TYPE_ARM) {

		cdp->cpu_type = CPU_TYPE_ARM;

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
		case CPU_ARCH_ARMv4T:
		case CPU_ARCH_ARMv5T:
			cdp->cpu_subtype = CPU_SUBTYPE_ARM_V4T;
			break;
		case CPU_ARCH_ARMv5TE:
		case CPU_ARCH_ARMv5TEJ:
			if (cpu_info_p->arm_info.arm_implementor == CPU_VID_INTEL)
				cdp->cpu_subtype = CPU_SUBTYPE_ARM_XSCALE;
			else
				cdp->cpu_subtype = CPU_SUBTYPE_ARM_V5TEJ;
			break;
		case CPU_ARCH_ARMv6:
			cdp->cpu_subtype = CPU_SUBTYPE_ARM_V6;
			break;
		case CPU_ARCH_ARMv7:
			cdp->cpu_subtype = CPU_SUBTYPE_ARM_V7;
			break;
		case CPU_ARCH_ARMv7f:
			cdp->cpu_subtype = CPU_SUBTYPE_ARM_V7F;
			break;
		case CPU_ARCH_ARMv7s:
			cdp->cpu_subtype = CPU_SUBTYPE_ARM_V7S;
			break;
		case CPU_ARCH_ARMv7k:
			cdp->cpu_subtype = CPU_SUBTYPE_ARM_V7K;
			break;
		default:
			cdp->cpu_subtype = CPU_SUBTYPE_ARM_ALL;
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

}