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
struct kvmppc_vcpu_44x {struct kvmppc_44x_tlbe* guest_tlb; } ;
struct kvmppc_44x_tlbe {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
typedef  scalar_t__ gva_t ;

/* Variables and functions */
 int ARRAY_SIZE (struct kvmppc_44x_tlbe*) ; 
 scalar_t__ get_tlb_eaddr (struct kvmppc_44x_tlbe*) ; 
 scalar_t__ get_tlb_end (struct kvmppc_44x_tlbe*) ; 
 unsigned int get_tlb_tid (struct kvmppc_44x_tlbe*) ; 
 unsigned int get_tlb_ts (struct kvmppc_44x_tlbe*) ; 
 int /*<<< orphan*/  get_tlb_v (struct kvmppc_44x_tlbe*) ; 
 struct kvmppc_vcpu_44x* to_44x (struct kvm_vcpu*) ; 

int kvmppc_44x_tlb_index(struct kvm_vcpu *vcpu, gva_t eaddr, unsigned int pid,
                         unsigned int as)
{
	struct kvmppc_vcpu_44x *vcpu_44x = to_44x(vcpu);
	int i;

	/* XXX Replace loop with fancy data structures. */
	for (i = 0; i < ARRAY_SIZE(vcpu_44x->guest_tlb); i++) {
		struct kvmppc_44x_tlbe *tlbe = &vcpu_44x->guest_tlb[i];
		unsigned int tid;

		if (eaddr < get_tlb_eaddr(tlbe))
			continue;

		if (eaddr > get_tlb_end(tlbe))
			continue;

		tid = get_tlb_tid(tlbe);
		if (tid && (tid != pid))
			continue;

		if (!get_tlb_v(tlbe))
			continue;

		if (get_tlb_ts(tlbe) != as)
			continue;

		return i;
	}

	return -1;
}