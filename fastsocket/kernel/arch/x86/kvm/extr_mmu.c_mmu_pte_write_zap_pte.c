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
typedef  int u64 ;
struct kvm_vcpu {TYPE_3__* kvm; } ;
struct TYPE_4__ {int /*<<< orphan*/  level; } ;
struct kvm_mmu_page {TYPE_1__ role; } ;
struct TYPE_5__ {int /*<<< orphan*/  lpages; } ;
struct TYPE_6__ {TYPE_2__ stat; } ;

/* Variables and functions */
 int PT64_BASE_ADDR_MASK ; 
 int /*<<< orphan*/  __set_spte (int*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_large_pte (int) ; 
 scalar_t__ is_last_spte (int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_shadow_present_pte (int) ; 
 int /*<<< orphan*/  mmu_page_remove_parent_pte (struct kvm_mmu_page*,int*) ; 
 struct kvm_mmu_page* page_header (int) ; 
 int /*<<< orphan*/  rmap_remove (TYPE_3__*,int*) ; 
 int /*<<< orphan*/  shadow_trap_nonpresent_pte ; 

__attribute__((used)) static void mmu_pte_write_zap_pte(struct kvm_vcpu *vcpu,
				  struct kvm_mmu_page *sp,
				  u64 *spte)
{
	u64 pte;
	struct kvm_mmu_page *child;

	pte = *spte;
	if (is_shadow_present_pte(pte)) {
		if (is_last_spte(pte, sp->role.level))
			rmap_remove(vcpu->kvm, spte);
		else {
			child = page_header(pte & PT64_BASE_ADDR_MASK);
			mmu_page_remove_parent_pte(child, spte);
		}
	}
	__set_spte(spte, shadow_trap_nonpresent_pte);
	if (is_large_pte(pte))
		--vcpu->kvm->stat.lpages;
}