#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kvm_pmu {int /*<<< orphan*/  irq_work; TYPE_3__* fixed_counters; TYPE_2__* gp_counters; } ;
struct TYPE_4__ {struct kvm_pmu pmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_6__ {scalar_t__ idx; struct kvm_vcpu* vcpu; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int idx; struct kvm_vcpu* vcpu; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_PMC_FIXED ; 
 int /*<<< orphan*/  KVM_PMC_GP ; 
 scalar_t__ X86_PMC_IDX_FIXED ; 
 int X86_PMC_MAX_FIXED ; 
 int X86_PMC_MAX_GENERIC ; 
 int /*<<< orphan*/  init_irq_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_pmu_cpuid_update (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  memset (struct kvm_pmu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trigger_pmi ; 

void kvm_pmu_init(struct kvm_vcpu *vcpu)
{
	int i;
	struct kvm_pmu *pmu = &vcpu->arch.pmu;

	memset(pmu, 0, sizeof(*pmu));
	for (i = 0; i < X86_PMC_MAX_GENERIC; i++) {
		pmu->gp_counters[i].type = KVM_PMC_GP;
		pmu->gp_counters[i].vcpu = vcpu;
		pmu->gp_counters[i].idx = i;
	}
	for (i = 0; i < X86_PMC_MAX_FIXED; i++) {
		pmu->fixed_counters[i].type = KVM_PMC_FIXED;
		pmu->fixed_counters[i].vcpu = vcpu;
		pmu->fixed_counters[i].idx = i + X86_PMC_IDX_FIXED;
	}
	init_irq_work(&pmu->irq_work, trigger_pmi);
	kvm_pmu_cpuid_update(vcpu);
}