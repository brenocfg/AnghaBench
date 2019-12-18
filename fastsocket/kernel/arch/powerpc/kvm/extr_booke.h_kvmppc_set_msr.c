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
struct TYPE_2__ {int msr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMULATED_MTMSRWE_EXITS ; 
 int MSR_PR ; 
 int MSR_WE ; 
 int /*<<< orphan*/  kvm_vcpu_block (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_mmu_priv_switch (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_set_exit_type (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void kvmppc_set_msr(struct kvm_vcpu *vcpu, u32 new_msr)
{
	if ((new_msr & MSR_PR) != (vcpu->arch.msr & MSR_PR))
		kvmppc_mmu_priv_switch(vcpu, new_msr & MSR_PR);

	vcpu->arch.msr = new_msr;

	if (vcpu->arch.msr & MSR_WE) {
		kvm_vcpu_block(vcpu);
		kvmppc_set_exit_type(vcpu, EMULATED_MTMSRWE_EXITS);
	};
}