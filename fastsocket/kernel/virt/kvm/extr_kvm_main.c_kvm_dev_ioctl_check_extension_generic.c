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
#define  KVM_CAP_DESTROY_MEMORY_REGION_WORKS 133 
#define  KVM_CAP_INTERNAL_ERROR_DATA 132 
#define  KVM_CAP_IRQ_ROUTING 131 
#define  KVM_CAP_JOIN_MEMORY_REGIONS_WORKS 130 
#define  KVM_CAP_SET_BOOT_CPU_ID 129 
#define  KVM_CAP_USER_MEMORY 128 
 long KVM_MAX_IRQ_ROUTES ; 
 long kvm_dev_ioctl_check_extension (long) ; 

__attribute__((used)) static long kvm_dev_ioctl_check_extension_generic(long arg)
{
	switch (arg) {
	case KVM_CAP_USER_MEMORY:
	case KVM_CAP_DESTROY_MEMORY_REGION_WORKS:
	case KVM_CAP_JOIN_MEMORY_REGIONS_WORKS:
#ifdef CONFIG_KVM_APIC_ARCHITECTURE
	case KVM_CAP_SET_BOOT_CPU_ID:
#endif
	case KVM_CAP_INTERNAL_ERROR_DATA:
		return 1;
#ifdef CONFIG_HAVE_KVM_IRQCHIP
	case KVM_CAP_IRQ_ROUTING:
		return KVM_MAX_IRQ_ROUTES;
#endif
	default:
		break;
	}
	return kvm_dev_ioctl_check_extension(arg);
}