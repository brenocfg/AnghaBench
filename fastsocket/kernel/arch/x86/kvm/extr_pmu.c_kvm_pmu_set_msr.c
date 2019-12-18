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
typedef  int u32 ;
struct msr_data {int index; int data; int /*<<< orphan*/  host_initiated; } ;
struct kvm_pmu {int fixed_ctr_ctrl; int global_status; int global_ctrl; int global_ctrl_mask; int global_ovf_ctrl; } ;
struct TYPE_2__ {struct kvm_pmu pmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_pmc {int counter; int eventsel; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
#define  MSR_CORE_PERF_FIXED_CTR_CTRL 131 
#define  MSR_CORE_PERF_GLOBAL_CTRL 130 
#define  MSR_CORE_PERF_GLOBAL_OVF_CTRL 129 
#define  MSR_CORE_PERF_GLOBAL_STATUS 128 
 int /*<<< orphan*/  MSR_IA32_PERFCTR0 ; 
 int /*<<< orphan*/  MSR_P6_EVNTSEL0 ; 
 struct kvm_pmc* get_fixed_pmc (struct kvm_pmu*,int) ; 
 struct kvm_pmc* get_gp_pmc (struct kvm_pmu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  global_ctrl_changed (struct kvm_pmu*,int) ; 
 int read_pmc (struct kvm_pmc*) ; 
 int /*<<< orphan*/  reprogram_fixed_counters (struct kvm_pmu*,int) ; 
 int /*<<< orphan*/  reprogram_gp_counter (struct kvm_pmc*,int) ; 

int kvm_pmu_set_msr(struct kvm_vcpu *vcpu, struct msr_data *msr_info)
{
	struct kvm_pmu *pmu = &vcpu->arch.pmu;
	struct kvm_pmc *pmc;
	u32 index = msr_info->index;
	u64 data = msr_info->data;

	switch (index) {
	case MSR_CORE_PERF_FIXED_CTR_CTRL:
		if (pmu->fixed_ctr_ctrl == data)
			return 0;
		if (!(data & 0xfffffffffffff444)) {
			reprogram_fixed_counters(pmu, data);
			return 0;
		}
		break;
	case MSR_CORE_PERF_GLOBAL_STATUS:
		if (msr_info->host_initiated) {
			pmu->global_status = data;
			return 0;
		}
		break; /* RO MSR */
	case MSR_CORE_PERF_GLOBAL_CTRL:
		if (pmu->global_ctrl == data)
			return 0;
		if (!(data & pmu->global_ctrl_mask)) {
			global_ctrl_changed(pmu, data);
			return 0;
		}
		break;
	case MSR_CORE_PERF_GLOBAL_OVF_CTRL:
		if (!(data & (pmu->global_ctrl_mask & ~(3ull<<62)))) {
			if (!msr_info->host_initiated)
				pmu->global_status &= ~data;
			pmu->global_ovf_ctrl = data;
			return 0;
		}
		break;
	default:
		if ((pmc = get_gp_pmc(pmu, index, MSR_IA32_PERFCTR0)) ||
				(pmc = get_fixed_pmc(pmu, index))) {
			if (!msr_info->host_initiated)
				data = (s64)(s32)data;
			pmc->counter += data - read_pmc(pmc);
			return 0;
		} else if ((pmc = get_gp_pmc(pmu, index, MSR_P6_EVNTSEL0))) {
			if (data == pmc->eventsel)
				return 0;
			if (!(data & 0xffffffff00200000ull)) {
				reprogram_gp_counter(pmc, data);
				return 0;
			}
		}
	}
	return 1;
}