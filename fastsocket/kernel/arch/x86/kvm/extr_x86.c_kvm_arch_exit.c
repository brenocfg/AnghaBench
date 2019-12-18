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
 int /*<<< orphan*/  CPUFREQ_TRANSITION_NOTIFIER ; 
 int /*<<< orphan*/  X86_FEATURE_CONSTANT_TSC ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpufreq_unregister_notifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_guest_cbs ; 
 int /*<<< orphan*/  kvm_mmu_module_exit () ; 
 int /*<<< orphan*/ * kvm_x86_ops ; 
 int /*<<< orphan*/  kvmclock_cpu_notifier_block ; 
 int /*<<< orphan*/  kvmclock_cpufreq_notifier_block ; 
 int /*<<< orphan*/  perf_unregister_guest_info_callbacks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_hotcpu_notifier (int /*<<< orphan*/ *) ; 

void kvm_arch_exit(void)
{
	perf_unregister_guest_info_callbacks(&kvm_guest_cbs);

	if (!boot_cpu_has(X86_FEATURE_CONSTANT_TSC))
		cpufreq_unregister_notifier(&kvmclock_cpufreq_notifier_block,
					    CPUFREQ_TRANSITION_NOTIFIER);
#ifdef CONFIG_HOTPLUG_CPU
	unregister_hotcpu_notifier(&kvmclock_cpu_notifier_block);
#endif
	kvm_x86_ops = NULL;
	kvm_mmu_module_exit();
}