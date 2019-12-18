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
struct tlbe {int dummy; } ;
struct kvmppc_vcpu_e500 {struct tlbe** shadow_tlb; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 unsigned int MAS0_ESEL (int /*<<< orphan*/ ) ; 
 unsigned int MAS0_TLBSEL (int) ; 
 int /*<<< orphan*/  SPRN_MAS0 ; 
 int /*<<< orphan*/  __write_host_tlbe (struct tlbe*) ; 
 scalar_t__ get_tlb_v (struct tlbe*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 unsigned int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,unsigned int) ; 
 int tlb1_max_shadow_size () ; 
 struct kvmppc_vcpu_e500* to_e500 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  to_htlb1_esel (int) ; 

void kvmppc_e500_tlb_load(struct kvm_vcpu *vcpu, int cpu)
{
	struct kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	int i;
	unsigned register mas0;

	/* Load all valid TLB1 entries to reduce guest tlb miss fault */
	local_irq_disable();
	mas0 = mfspr(SPRN_MAS0);
	for (i = 0; i < tlb1_max_shadow_size(); i++) {
		struct tlbe *stlbe = &vcpu_e500->shadow_tlb[1][i];

		if (get_tlb_v(stlbe)) {
			mtspr(SPRN_MAS0, MAS0_TLBSEL(1)
					| MAS0_ESEL(to_htlb1_esel(i)));
			__write_host_tlbe(stlbe);
		}
	}
	mtspr(SPRN_MAS0, mas0);
	local_irq_enable();
}