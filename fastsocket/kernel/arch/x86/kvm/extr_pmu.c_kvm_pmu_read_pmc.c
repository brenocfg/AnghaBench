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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct kvm_pmu {unsigned int nr_arch_gp_counters; unsigned int nr_arch_fixed_counters; struct kvm_pmc* gp_counters; struct kvm_pmc* fixed_counters; } ;
struct TYPE_2__ {struct kvm_pmu pmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_pmc {int dummy; } ;

/* Variables and functions */
 scalar_t__ read_pmc (struct kvm_pmc*) ; 

int kvm_pmu_read_pmc(struct kvm_vcpu *vcpu, unsigned pmc, u64 *data)
{
	struct kvm_pmu *pmu = &vcpu->arch.pmu;
	bool fast_mode = pmc & (1u << 31);
	bool fixed = pmc & (1u << 30);
	struct kvm_pmc *counters;
	u64 ctr;

	pmc &= ~(3u << 30);
	if (!fixed && pmc >= pmu->nr_arch_gp_counters)
		return 1;
	if (fixed && pmc >= pmu->nr_arch_fixed_counters)
		return 1;
	counters = fixed ? pmu->fixed_counters : pmu->gp_counters;
	ctr = read_pmc(&counters[pmc]);
	if (fast_mode)
		ctr = (u32)ctr;
	*data = ctr;

	return 0;
}