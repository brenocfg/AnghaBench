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
struct TYPE_2__ {int* last_pte_updated; scalar_t__ last_pte_gfn; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  scalar_t__ gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  PT_ACCESSED_SHIFT ; 
 scalar_t__ is_shadow_present_pte (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int shadow_accessed_mask ; 

__attribute__((used)) static void kvm_mmu_access_page(struct kvm_vcpu *vcpu, gfn_t gfn)
{
	u64 *spte = vcpu->arch.last_pte_updated;

	if (spte
	    && vcpu->arch.last_pte_gfn == gfn
	    && shadow_accessed_mask
	    && !(*spte & shadow_accessed_mask)
	    && is_shadow_present_pte(*spte))
		set_bit(PT_ACCESSED_SHIFT, (unsigned long *)spte);
}