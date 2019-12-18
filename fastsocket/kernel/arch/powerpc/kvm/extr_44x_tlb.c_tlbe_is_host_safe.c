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
struct kvmppc_44x_tlbe {int dummy; } ;
struct TYPE_2__ {int msr; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_1__ arch; } ;
typedef  int gpa_t ;

/* Variables and functions */
 int MSR_IS ; 
 int PAGE_SHIFT ; 
 int get_tlb_raddr (struct kvmppc_44x_tlbe const*) ; 
 int get_tlb_ts (struct kvmppc_44x_tlbe const*) ; 
 int /*<<< orphan*/  get_tlb_v (struct kvmppc_44x_tlbe const*) ; 
 int /*<<< orphan*/  gfn_to_memslot (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tlbe_is_host_safe(const struct kvm_vcpu *vcpu,
                             const struct kvmppc_44x_tlbe *tlbe)
{
	gpa_t gpa;

	if (!get_tlb_v(tlbe))
		return 0;

	/* Does it match current guest AS? */
	/* XXX what about IS != DS? */
	if (get_tlb_ts(tlbe) != !!(vcpu->arch.msr & MSR_IS))
		return 0;

	gpa = get_tlb_raddr(tlbe);
	if (!gfn_to_memslot(vcpu->kvm, gpa >> PAGE_SHIFT))
		/* Mapping is not for RAM. */
		return 0;

	return 1;
}