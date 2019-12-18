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
struct kvmppc_vcpu_44x {struct kvmppc_44x_tlbe* shadow_tlb; } ;
struct kvmppc_44x_tlbe {int dummy; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ get_tlb_ts (struct kvmppc_44x_tlbe*) ; 
 scalar_t__ get_tlb_v (struct kvmppc_44x_tlbe*) ; 
 int /*<<< orphan*/  kvmppc_44x_tlbwe (int,struct kvmppc_44x_tlbe*) ; 
 int tlb_44x_hwater ; 
 struct kvmppc_vcpu_44x* to_44x (struct kvm_vcpu*) ; 

void kvmppc_44x_tlb_load(struct kvm_vcpu *vcpu)
{
	struct kvmppc_vcpu_44x *vcpu_44x = to_44x(vcpu);
	int i;

	for (i = 0; i <= tlb_44x_hwater; i++) {
		struct kvmppc_44x_tlbe *stlbe = &vcpu_44x->shadow_tlb[i];

		if (get_tlb_v(stlbe) && get_tlb_ts(stlbe))
			kvmppc_44x_tlbwe(i, stlbe);
	}
}