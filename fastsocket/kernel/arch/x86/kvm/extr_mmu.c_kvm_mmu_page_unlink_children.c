#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  level; } ;
struct kvm_mmu_page {TYPE_1__ role; int /*<<< orphan*/ * spt; } ;
struct TYPE_4__ {int /*<<< orphan*/  lpages; } ;
struct kvm {TYPE_2__ stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT64_BASE_ADDR_MASK ; 
 unsigned int PT64_ENT_PER_PAGE ; 
 scalar_t__ is_large_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_last_spte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_shadow_present_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_page_remove_parent_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmap_remove (struct kvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shadow_trap_nonpresent_pte ; 

__attribute__((used)) static void kvm_mmu_page_unlink_children(struct kvm *kvm,
					 struct kvm_mmu_page *sp)
{
	unsigned i;
	u64 *pt;
	u64 ent;

	pt = sp->spt;

	for (i = 0; i < PT64_ENT_PER_PAGE; ++i) {
		ent = pt[i];

		if (is_shadow_present_pte(ent)) {
			if (!is_last_spte(ent, sp->role.level)) {
				ent &= PT64_BASE_ADDR_MASK;
				mmu_page_remove_parent_pte(page_header(ent),
							   &pt[i]);
			} else {
				if (is_large_pte(ent))
					--kvm->stat.lpages;
				rmap_remove(kvm, &pt[i]);
			}
		}
		pt[i] = shadow_trap_nonpresent_pte;
	}
}