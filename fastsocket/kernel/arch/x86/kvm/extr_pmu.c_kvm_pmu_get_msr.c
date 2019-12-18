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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct kvm_pmu {int /*<<< orphan*/  global_ovf_ctrl; int /*<<< orphan*/  global_ctrl; int /*<<< orphan*/  global_status; int /*<<< orphan*/  fixed_ctr_ctrl; } ;
struct TYPE_2__ {struct kvm_pmu pmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_pmc {int /*<<< orphan*/  eventsel; } ;

/* Variables and functions */
#define  MSR_CORE_PERF_FIXED_CTR_CTRL 131 
#define  MSR_CORE_PERF_GLOBAL_CTRL 130 
#define  MSR_CORE_PERF_GLOBAL_OVF_CTRL 129 
#define  MSR_CORE_PERF_GLOBAL_STATUS 128 
 int /*<<< orphan*/  MSR_IA32_PERFCTR0 ; 
 int /*<<< orphan*/  MSR_P6_EVNTSEL0 ; 
 struct kvm_pmc* get_fixed_pmc (struct kvm_pmu*,int) ; 
 struct kvm_pmc* get_gp_pmc (struct kvm_pmu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_pmc (struct kvm_pmc*) ; 

int kvm_pmu_get_msr(struct kvm_vcpu *vcpu, u32 index, u64 *data)
{
	struct kvm_pmu *pmu = &vcpu->arch.pmu;
	struct kvm_pmc *pmc;

	switch (index) {
	case MSR_CORE_PERF_FIXED_CTR_CTRL:
		*data = pmu->fixed_ctr_ctrl;
		return 0;
	case MSR_CORE_PERF_GLOBAL_STATUS:
		*data = pmu->global_status;
		return 0;
	case MSR_CORE_PERF_GLOBAL_CTRL:
		*data = pmu->global_ctrl;
		return 0;
	case MSR_CORE_PERF_GLOBAL_OVF_CTRL:
		*data = pmu->global_ovf_ctrl;
		return 0;
	default:
		if ((pmc = get_gp_pmc(pmu, index, MSR_IA32_PERFCTR0)) ||
				(pmc = get_fixed_pmc(pmu, index))) {
			*data = read_pmc(pmc);
			return 0;
		} else if ((pmc = get_gp_pmc(pmu, index, MSR_P6_EVNTSEL0))) {
			*data = pmc->eventsel;
			return 0;
		}
	}
	return 1;
}