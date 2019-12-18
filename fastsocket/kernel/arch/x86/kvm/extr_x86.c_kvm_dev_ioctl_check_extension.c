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
struct TYPE_2__ {int /*<<< orphan*/  (* cpu_has_accelerated_tpr ) () ;} ;

/* Variables and functions */
#define  KVM_CAP_ADJUST_CLOCK 161 
#define  KVM_CAP_ASSIGN_DEV_IRQ 160 
#define  KVM_CAP_CLOCKSOURCE 159 
#define  KVM_CAP_COALESCED_MMIO 158 
#define  KVM_CAP_EXT_CPUID 157 
#define  KVM_CAP_GET_TSC_KHZ 156 
#define  KVM_CAP_HLT 155 
#define  KVM_CAP_HYPERV 154 
#define  KVM_CAP_IOEVENTFD 153 
#define  KVM_CAP_IOMMU 152 
#define  KVM_CAP_IRQCHIP 151 
#define  KVM_CAP_IRQFD 150 
#define  KVM_CAP_IRQ_INJECT_STATUS 149 
#define  KVM_CAP_KVMCLOCK_CTRL 148 
#define  KVM_CAP_MCE 147 
#define  KVM_CAP_MMU_SHADOW_CACHE_CONTROL 146 
#define  KVM_CAP_MP_STATE 145 
#define  KVM_CAP_NOP_IO_DELAY 144 
#define  KVM_CAP_NR_MEMSLOTS 143 
#define  KVM_CAP_NR_VCPUS 142 
#define  KVM_CAP_PIT 141 
#define  KVM_CAP_PIT2 140 
#define  KVM_CAP_PIT_STATE2 139 
#define  KVM_CAP_PV_MMU 138 
#define  KVM_CAP_REINJECT_CONTROL 137 
#define  KVM_CAP_SET_IDENTITY_MAP_ADDR 136 
#define  KVM_CAP_SET_TSS_ADDR 135 
#define  KVM_CAP_SYNC_MMU 134 
#define  KVM_CAP_TSC_CONTROL 133 
#define  KVM_CAP_TSC_DEADLINE_TIMER 132 
#define  KVM_CAP_VAPIC 131 
#define  KVM_CAP_VCPU_EVENTS 130 
#define  KVM_CAP_XCRS 129 
#define  KVM_CAP_XSAVE 128 
 int KVM_COALESCED_MMIO_PAGE_OFFSET ; 
 int KVM_MAX_MCE_BANKS ; 
 int KVM_MAX_VCPUS ; 
 int KVM_MEMORY_SLOTS ; 
 int /*<<< orphan*/  X86_FEATURE_TSC_DEADLINE_TIMER ; 
 int boot_cpu_has (int /*<<< orphan*/ ) ; 
 int cpu_has_xsave ; 
 int iommu_found () ; 
 int kvm_has_tsc_control ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 () ; 

int kvm_dev_ioctl_check_extension(long ext)
{
	int r;

	switch (ext) {
	case KVM_CAP_IRQCHIP:
	case KVM_CAP_HLT:
	case KVM_CAP_MMU_SHADOW_CACHE_CONTROL:
	case KVM_CAP_SET_TSS_ADDR:
	case KVM_CAP_EXT_CPUID:
	case KVM_CAP_CLOCKSOURCE:
	case KVM_CAP_PIT:
	case KVM_CAP_NOP_IO_DELAY:
	case KVM_CAP_MP_STATE:
	case KVM_CAP_SYNC_MMU:
	case KVM_CAP_REINJECT_CONTROL:
	case KVM_CAP_IRQ_INJECT_STATUS:
	case KVM_CAP_ASSIGN_DEV_IRQ:
	case KVM_CAP_IRQFD:
	case KVM_CAP_IOEVENTFD:
	case KVM_CAP_PIT2:
	case KVM_CAP_PIT_STATE2:
	case KVM_CAP_SET_IDENTITY_MAP_ADDR:
	case KVM_CAP_ADJUST_CLOCK:
	case KVM_CAP_VCPU_EVENTS:
	case KVM_CAP_HYPERV:
	case KVM_CAP_XSAVE:
	case KVM_CAP_GET_TSC_KHZ:
	case KVM_CAP_KVMCLOCK_CTRL:
		r = 1;
		break;
	case KVM_CAP_COALESCED_MMIO:
		r = KVM_COALESCED_MMIO_PAGE_OFFSET;
		break;
	case KVM_CAP_VAPIC:
		r = !kvm_x86_ops->cpu_has_accelerated_tpr();
		break;
	case KVM_CAP_NR_VCPUS:
		r = KVM_MAX_VCPUS;
		break;
	case KVM_CAP_NR_MEMSLOTS:
		r = KVM_MEMORY_SLOTS;
		break;
	case KVM_CAP_PV_MMU:	/* obsolete */
		r = 0;
		break;
	case KVM_CAP_IOMMU:
		r = iommu_found();
		break;
	case KVM_CAP_MCE:
		r = KVM_MAX_MCE_BANKS;
		break;
	case KVM_CAP_XCRS:
		r = cpu_has_xsave;
		break;
	case KVM_CAP_TSC_CONTROL:
		r = kvm_has_tsc_control;
		break;
	case KVM_CAP_TSC_DEADLINE_TIMER:
		r = boot_cpu_has(X86_FEATURE_TSC_DEADLINE_TIMER);
		break;
	default:
		r = 0;
		break;
	}
	return r;

}