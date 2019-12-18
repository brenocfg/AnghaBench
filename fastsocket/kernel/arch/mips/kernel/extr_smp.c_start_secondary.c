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
struct TYPE_4__ {int /*<<< orphan*/  udelay_val; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* smp_finish ) () ;int /*<<< orphan*/  (* init_secondary ) () ;} ;

/* Variables and functions */
 int TCBIND_CURTC ; 
 int /*<<< orphan*/  calibrate_delay () ; 
 int /*<<< orphan*/  cpu_callin_map ; 
 TYPE_2__* cpu_data ; 
 int /*<<< orphan*/  cpu_idle () ; 
 int /*<<< orphan*/  cpu_probe () ; 
 int /*<<< orphan*/  cpu_report () ; 
 int /*<<< orphan*/  cpu_set (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loops_per_jiffy ; 
 int /*<<< orphan*/  mips_clockevent_init () ; 
 TYPE_1__* mp_ops ; 
 int /*<<< orphan*/  notify_cpu_starting (unsigned int) ; 
 int /*<<< orphan*/  per_cpu_trap_init () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int read_c0_tcbind () ; 
 int /*<<< orphan*/  set_cpu_sibling_map (unsigned int) ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  synchronise_count_slave () ; 

void start_secondary(void)
{
	unsigned int cpu;

#ifdef CONFIG_MIPS_MT_SMTC
	/* Only do cpu_probe for first TC of CPU */
	if ((read_c0_tcbind() & TCBIND_CURTC) == 0)
#endif /* CONFIG_MIPS_MT_SMTC */
	cpu_probe();
	cpu_report();
	per_cpu_trap_init();
	mips_clockevent_init();
	mp_ops->init_secondary();

	/*
	 * XXX parity protection should be folded in here when it's converted
	 * to an option instead of something based on .cputype
	 */

	calibrate_delay();
	preempt_disable();
	cpu = smp_processor_id();
	cpu_data[cpu].udelay_val = loops_per_jiffy;

	notify_cpu_starting(cpu);

	mp_ops->smp_finish();
	set_cpu_sibling_map(cpu);

	cpu_set(cpu, cpu_callin_map);

	synchronise_count_slave();

	cpu_idle();
}