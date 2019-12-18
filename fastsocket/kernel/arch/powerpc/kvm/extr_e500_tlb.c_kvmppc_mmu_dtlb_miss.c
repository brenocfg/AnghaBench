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
struct TYPE_2__ {int msr; int /*<<< orphan*/  fault_dear; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int MSR_DS ; 
 int /*<<< orphan*/  kvmppc_e500_deliver_tlb_miss (struct kvm_vcpu*,int /*<<< orphan*/ ,unsigned int) ; 

void kvmppc_mmu_dtlb_miss(struct kvm_vcpu *vcpu)
{
	unsigned int as = !!(vcpu->arch.msr & MSR_DS);

	kvmppc_e500_deliver_tlb_miss(vcpu, vcpu->arch.fault_dear, as);
}