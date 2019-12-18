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
typedef  int u64 ;
struct kvm_pmu {int nr_arch_gp_counters; unsigned long long nr_arch_fixed_counters; int* counter_bitmask; int version; unsigned long long available_event_types; int global_ctrl; int global_ctrl_mask; } ;
struct TYPE_2__ {struct kvm_pmu pmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_cpuid_entry2 {int eax; unsigned long long ebx; int edx; } ;

/* Variables and functions */
 size_t KVM_PMC_FIXED ; 
 size_t KVM_PMC_GP ; 
 unsigned long long X86_PMC_IDX_FIXED ; 
 int /*<<< orphan*/  X86_PMC_MAX_FIXED ; 
 int /*<<< orphan*/  X86_PMC_MAX_GENERIC ; 
 struct kvm_cpuid_entry2* kvm_find_cpuid_entry (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 
 void* min (int,int /*<<< orphan*/ ) ; 

void kvm_pmu_cpuid_update(struct kvm_vcpu *vcpu)
{
	struct kvm_pmu *pmu = &vcpu->arch.pmu;
	struct kvm_cpuid_entry2 *entry;
	unsigned bitmap_len;

	pmu->nr_arch_gp_counters = 0;
	pmu->nr_arch_fixed_counters = 0;
	pmu->counter_bitmask[KVM_PMC_GP] = 0;
	pmu->counter_bitmask[KVM_PMC_FIXED] = 0;
	pmu->version = 0;

	entry = kvm_find_cpuid_entry(vcpu, 0xa, 0);
	if (!entry)
		return;

	pmu->version = entry->eax & 0xff;
	if (!pmu->version)
		return;

	pmu->nr_arch_gp_counters = min((int)(entry->eax >> 8) & 0xff,
			X86_PMC_MAX_GENERIC);
	pmu->counter_bitmask[KVM_PMC_GP] =
		((u64)1 << ((entry->eax >> 16) & 0xff)) - 1;
	bitmap_len = (entry->eax >> 24) & 0xff;
	pmu->available_event_types = ~entry->ebx & ((1ull << bitmap_len) - 1);

	if (pmu->version == 1) {
		pmu->global_ctrl = (1 << pmu->nr_arch_gp_counters) - 1;
		return;
	}

	pmu->nr_arch_fixed_counters = min((int)(entry->edx & 0x1f),
			X86_PMC_MAX_FIXED);
	pmu->counter_bitmask[KVM_PMC_FIXED] =
		((u64)1 << ((entry->edx >> 5) & 0xff)) - 1;
	pmu->global_ctrl_mask = ~(((1 << pmu->nr_arch_gp_counters) - 1)
			| (((1ull << pmu->nr_arch_fixed_counters) - 1)
				<< X86_PMC_IDX_FIXED));
}