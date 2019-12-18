#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvmppc_vcpu_e500 {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _tlbil_all () ; 
 int /*<<< orphan*/  kvmppc_e500_stlbe_invalidate (struct kvmppc_vcpu_e500*,int,int) ; 
 int tlb1_max_shadow_size () ; 
 struct kvmppc_vcpu_e500* to_e500 (struct kvm_vcpu*) ; 

void kvmppc_mmu_priv_switch(struct kvm_vcpu *vcpu, int usermode)
{
	if (usermode) {
		struct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
		int i;

		/* XXX Replace loop with fancy data structures. */
		for (i = 0; i < tlb1_max_shadow_size(); i++)
			kvmppc_e500_stlbe_invalidate(vcpu_e500, 1, i);

		_tlbil_all();
	}
}