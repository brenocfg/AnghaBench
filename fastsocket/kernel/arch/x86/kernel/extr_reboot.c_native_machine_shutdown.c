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

/* Variables and functions */
 scalar_t__ cpu_online (int) ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  disable_IO_APIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpet_disable () ; 
 int /*<<< orphan*/  lapic_shutdown () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int nr_cpu_ids ; 
 int /*<<< orphan*/  pci_iommu_shutdown () ; 
 int reboot_cpu ; 
 int /*<<< orphan*/  set_cpus_allowed_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  stop_other_cpus () ; 

void native_machine_shutdown(void)
{
	/* Stop the cpus and apics */
#ifdef CONFIG_SMP

	/* The boot cpu is always logical cpu 0 */
	int reboot_cpu_id = 0;

#ifdef CONFIG_X86_32
	/* See if there has been given a command line override */
	if ((reboot_cpu != -1) && (reboot_cpu < nr_cpu_ids) &&
		cpu_online(reboot_cpu))
		reboot_cpu_id = reboot_cpu;
#endif

	/* Make certain the cpu I'm about to reboot on is online */
	if (!cpu_online(reboot_cpu_id))
		reboot_cpu_id = smp_processor_id();

	/* Make certain I only run on the appropriate processor */
	set_cpus_allowed_ptr(current, cpumask_of(reboot_cpu_id));

	/*
	 * O.K Now that I'm on the appropriate processor, stop all of the
	 * others. Also disable the local irq to not receive the per-cpu
	 * timer interrupt which may trigger scheduler's load balance.
	 */
	local_irq_disable();
	stop_other_cpus();
#endif

	lapic_shutdown();

#ifdef CONFIG_X86_IO_APIC
	disable_IO_APIC(0);
#endif

#ifdef CONFIG_HPET_TIMER
	hpet_disable();
#endif

#ifdef CONFIG_X86_64
	pci_iommu_shutdown();
#endif
}