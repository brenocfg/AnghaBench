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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int CPU_PROFILING ; 
 scalar_t__ cpumask_test_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pt_regs* get_irq_regs () ; 
 int /*<<< orphan*/ * prof_cpu_mask ; 
 int /*<<< orphan*/  profile_hit (int,void*) ; 
 scalar_t__ profile_pc (struct pt_regs*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  timer_hook (struct pt_regs*) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

void profile_tick(int type)
{
	struct pt_regs *regs = get_irq_regs();

	if (type == CPU_PROFILING && timer_hook)
		timer_hook(regs);
	if (!user_mode(regs) && prof_cpu_mask != NULL &&
	    cpumask_test_cpu(smp_processor_id(), prof_cpu_mask))
		profile_hit(type, (void *)profile_pc(regs));
}