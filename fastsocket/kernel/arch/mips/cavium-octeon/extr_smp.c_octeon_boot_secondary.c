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
struct task_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ __KSTK_TOS (struct task_struct*) ; 
 int /*<<< orphan*/  cpu_logical_map (int) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  octeon_processor_boot ; 
 unsigned long octeon_processor_gp ; 
 scalar_t__ octeon_processor_sp ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ task_thread_info (struct task_struct*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void octeon_boot_secondary(int cpu, struct task_struct *idle)
{
	int count;

	pr_info("SMP: Booting CPU%02d (CoreId %2d)...\n", cpu,
		cpu_logical_map(cpu));

	octeon_processor_sp = __KSTK_TOS(idle);
	octeon_processor_gp = (unsigned long)(task_thread_info(idle));
	octeon_processor_boot = cpu_logical_map(cpu);
	mb();

	count = 10000;
	while (octeon_processor_sp && count) {
		/* Waiting for processor to get the SP and GP */
		udelay(1);
		count--;
	}
	if (count == 0)
		pr_err("Secondary boot timeout\n");
}