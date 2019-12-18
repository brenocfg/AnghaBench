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
typedef  scalar_t__ u64 ;
struct kvm_mmu_page {scalar_t__* spt; } ;

/* Variables and functions */
 int PT64_ENT_PER_PAGE ; 
 int /*<<< orphan*/  __set_spte (scalar_t__*,scalar_t__) ; 
 scalar_t__ shadow_notrap_nonpresent_pte ; 
 scalar_t__ shadow_trap_nonpresent_pte ; 

__attribute__((used)) static void mmu_convert_notrap(struct kvm_mmu_page *sp)
{
	int i;
	u64 *pt = sp->spt;

	if (shadow_trap_nonpresent_pte == shadow_notrap_nonpresent_pte)
		return;

	for (i = 0; i < PT64_ENT_PER_PAGE; ++i) {
		if (pt[i] == shadow_notrap_nonpresent_pte)
			__set_spte(&pt[i], shadow_trap_nonpresent_pte);
	}
}