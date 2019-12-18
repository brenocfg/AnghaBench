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
typedef  int u32 ;
struct kvm_pmu {int version; } ;
struct TYPE_2__ {struct kvm_pmu pmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
#define  MSR_CORE_PERF_FIXED_CTR_CTRL 131 
#define  MSR_CORE_PERF_GLOBAL_CTRL 130 
#define  MSR_CORE_PERF_GLOBAL_OVF_CTRL 129 
#define  MSR_CORE_PERF_GLOBAL_STATUS 128 
 int /*<<< orphan*/  MSR_IA32_PERFCTR0 ; 
 int /*<<< orphan*/  MSR_P6_EVNTSEL0 ; 
 int /*<<< orphan*/  get_fixed_pmc (struct kvm_pmu*,int) ; 
 int /*<<< orphan*/  get_gp_pmc (struct kvm_pmu*,int,int /*<<< orphan*/ ) ; 

bool kvm_pmu_msr(struct kvm_vcpu *vcpu, u32 msr)
{
	struct kvm_pmu *pmu = &vcpu->arch.pmu;
	int ret;

	switch (msr) {
	case MSR_CORE_PERF_FIXED_CTR_CTRL:
	case MSR_CORE_PERF_GLOBAL_STATUS:
	case MSR_CORE_PERF_GLOBAL_CTRL:
	case MSR_CORE_PERF_GLOBAL_OVF_CTRL:
		ret = pmu->version > 1;
		break;
	default:
		ret = get_gp_pmc(pmu, msr, MSR_IA32_PERFCTR0)
			|| get_gp_pmc(pmu, msr, MSR_P6_EVNTSEL0)
			|| get_fixed_pmc(pmu, msr);
		break;
	}
	return ret;
}