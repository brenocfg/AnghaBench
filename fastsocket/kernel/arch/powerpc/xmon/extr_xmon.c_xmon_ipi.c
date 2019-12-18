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
 int /*<<< orphan*/  cpu_isset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpus_in_xmon ; 
 scalar_t__ in_xmon ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  xmon_core (struct pt_regs*,int) ; 

__attribute__((used)) static int xmon_ipi(struct pt_regs *regs)
{
#ifdef CONFIG_SMP
	if (in_xmon && !cpu_isset(smp_processor_id(), cpus_in_xmon))
		xmon_core(regs, 1);
#endif
	return 0;
}