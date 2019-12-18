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
typedef  int u64 ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  scalar_t__ pfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PAGE_SHIFT ; 
 int PT64_BASE_ADDR_MASK ; 
 int PT_WRITABLE_MASK ; 
 int SPTE_HOST_WRITEABLE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_spte (int*,int) ; 
 int /*<<< orphan*/  is_shadow_present_pte (int) ; 
 scalar_t__ is_writeble_pte (int) ; 
 int /*<<< orphan*/  kvm_flush_remote_tlbs (struct kvm*) ; 
 int /*<<< orphan*/  kvm_set_pfn_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_write (int /*<<< orphan*/ ) ; 
 int* rmap_next (struct kvm*,unsigned long*,int*) ; 
 int /*<<< orphan*/  rmap_printk (char*,int*,int) ; 
 int /*<<< orphan*/  rmap_remove (struct kvm*,int*) ; 
 int shadow_trap_nonpresent_pte ; 
 int /*<<< orphan*/  spte_to_pfn (int) ; 

__attribute__((used)) static int kvm_set_pte_rmapp(struct kvm *kvm, unsigned long *rmapp,
			     unsigned long data)
{
	int need_flush = 0;
	u64 *spte, new_spte;
	pte_t *ptep = (pte_t *)data;
	pfn_t new_pfn;

	WARN_ON(pte_huge(*ptep));
	new_pfn = pte_pfn(*ptep);
	spte = rmap_next(kvm, rmapp, NULL);
	while (spte) {
		BUG_ON(!is_shadow_present_pte(*spte));
		rmap_printk("kvm_set_pte_rmapp: spte %p %llx\n", spte, *spte);
		need_flush = 1;
		if (pte_write(*ptep)) {
			rmap_remove(kvm, spte);
			__set_spte(spte, shadow_trap_nonpresent_pte);
			spte = rmap_next(kvm, rmapp, NULL);
		} else {
			new_spte = *spte &~ (PT64_BASE_ADDR_MASK);
			new_spte |= (u64)new_pfn << PAGE_SHIFT;

			new_spte &= ~PT_WRITABLE_MASK;
			new_spte &= ~SPTE_HOST_WRITEABLE;
			if (is_writeble_pte(*spte))
				kvm_set_pfn_dirty(spte_to_pfn(*spte));
			__set_spte(spte, new_spte);
			spte = rmap_next(kvm, rmapp, spte);
		}
	}
	if (need_flush)
		kvm_flush_remote_tlbs(kvm);

	return 0;
}