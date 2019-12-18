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
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bad_page ; 
 int /*<<< orphan*/  cpus_hardware_enabled ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hardware_disable ; 
 int /*<<< orphan*/  hwpoison_page ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_arch_exit () ; 
 int /*<<< orphan*/  kvm_arch_hardware_unsetup () ; 
 int /*<<< orphan*/  kvm_cpu_notifier ; 
 int /*<<< orphan*/  kvm_dev ; 
 int /*<<< orphan*/  kvm_exit_debug () ; 
 int /*<<< orphan*/  kvm_reboot_notifier ; 
 int /*<<< orphan*/  kvm_sysdev ; 
 int /*<<< orphan*/  kvm_sysdev_class ; 
 int /*<<< orphan*/  kvm_vcpu_cache ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sysdev_class_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysdev_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tracepoint_synchronize_unregister () ; 
 int /*<<< orphan*/  unregister_cpu_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 

void kvm_exit(void)
{
	tracepoint_synchronize_unregister();
	kvm_exit_debug();
	misc_deregister(&kvm_dev);
	kmem_cache_destroy(kvm_vcpu_cache);
	sysdev_unregister(&kvm_sysdev);
	sysdev_class_unregister(&kvm_sysdev_class);
	unregister_reboot_notifier(&kvm_reboot_notifier);
	unregister_cpu_notifier(&kvm_cpu_notifier);
	on_each_cpu(hardware_disable, NULL, 1);
	kvm_arch_hardware_unsetup();
	kvm_arch_exit();
	free_cpumask_var(cpus_hardware_enabled);
	__free_page(hwpoison_page);
	__free_page(bad_page);
}