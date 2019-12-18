#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  processorCount; } ;

/* Variables and functions */
 int any_online_cpu (int /*<<< orphan*/ ) ; 
 int boot_cpuid ; 
 int /*<<< orphan*/  cpu_online_map ; 
 int /*<<< orphan*/  set_cpu_online (int,int) ; 
 int smp_processor_id () ; 
 TYPE_1__* vdso_data ; 
 int /*<<< orphan*/  xics_migrate_irqs_away () ; 

__attribute__((used)) static int pseries_cpu_disable(void)
{
	int cpu = smp_processor_id();

	set_cpu_online(cpu, false);
	vdso_data->processorCount--;

	/*fix boot_cpuid here*/
	if (cpu == boot_cpuid)
		boot_cpuid = any_online_cpu(cpu_online_map);

	/* FIXME: abstract this to not be platform specific later on */
	xics_migrate_irqs_away();
	return 0;
}