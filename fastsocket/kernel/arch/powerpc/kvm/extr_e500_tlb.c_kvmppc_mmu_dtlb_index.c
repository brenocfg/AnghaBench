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
struct TYPE_2__ {int msr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  gva_t ;

/* Variables and functions */
 int MSR_DS ; 
 int /*<<< orphan*/  get_cur_pid (struct kvm_vcpu*) ; 
 int kvmppc_e500_tlb_search (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int kvmppc_mmu_dtlb_index(struct kvm_vcpu *vcpu, gva_t eaddr)
{
	unsigned int as = !!(vcpu->arch.msr & MSR_DS);

	return kvmppc_e500_tlb_search(vcpu, eaddr, get_cur_pid(vcpu), as);
}