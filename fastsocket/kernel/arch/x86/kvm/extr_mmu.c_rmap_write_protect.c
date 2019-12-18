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
struct TYPE_2__ {int /*<<< orphan*/  lpages; } ;
struct kvm {TYPE_1__ stat; } ;
typedef  int /*<<< orphan*/  pfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int KVM_NR_PAGE_SIZES ; 
 int PT_DIRECTORY_LEVEL ; 
 int PT_PAGE_SIZE_MASK ; 
 int PT_PAGE_TABLE_LEVEL ; 
 int PT_PRESENT_MASK ; 
 int PT_WRITABLE_MASK ; 
 int /*<<< orphan*/  __set_spte (int*,int) ; 
 unsigned long* gfn_to_rmap (struct kvm*,int,int) ; 
 scalar_t__ is_writeble_pte (int) ; 
 int /*<<< orphan*/  kvm_set_pfn_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgprintk (char*,int*,int,int) ; 
 int* rmap_next (struct kvm*,unsigned long*,int*) ; 
 int /*<<< orphan*/  rmap_printk (char*,int*,int) ; 
 int /*<<< orphan*/  rmap_remove (struct kvm*,int*) ; 
 int shadow_trap_nonpresent_pte ; 
 int /*<<< orphan*/  spte_to_pfn (int) ; 
 int unalias_gfn (struct kvm*,int) ; 

__attribute__((used)) static int rmap_write_protect(struct kvm *kvm, u64 gfn)
{
	unsigned long *rmapp;
	u64 *spte;
	int i, write_protected = 0;

	gfn = unalias_gfn(kvm, gfn);
	rmapp = gfn_to_rmap(kvm, gfn, PT_PAGE_TABLE_LEVEL);

	spte = rmap_next(kvm, rmapp, NULL);
	while (spte) {
		BUG_ON(!spte);
		BUG_ON(!(*spte & PT_PRESENT_MASK));
		rmap_printk("rmap_write_protect: spte %p %llx\n", spte, *spte);
		if (is_writeble_pte(*spte)) {
			__set_spte(spte, *spte & ~PT_WRITABLE_MASK);
			write_protected = 1;
		}
		spte = rmap_next(kvm, rmapp, spte);
	}
	if (write_protected) {
		pfn_t pfn;

		spte = rmap_next(kvm, rmapp, NULL);
		pfn = spte_to_pfn(*spte);
		kvm_set_pfn_dirty(pfn);
	}

	/* check for huge page mappings */
	for (i = PT_DIRECTORY_LEVEL;
	     i < PT_PAGE_TABLE_LEVEL + KVM_NR_PAGE_SIZES; ++i) {
		rmapp = gfn_to_rmap(kvm, gfn, i);
		spte = rmap_next(kvm, rmapp, NULL);
		while (spte) {
			BUG_ON(!spte);
			BUG_ON(!(*spte & PT_PRESENT_MASK));
			BUG_ON((*spte & (PT_PAGE_SIZE_MASK|PT_PRESENT_MASK)) != (PT_PAGE_SIZE_MASK|PT_PRESENT_MASK));
			pgprintk("rmap_write_protect(large): spte %p %llx %lld\n", spte, *spte, gfn);
			if (is_writeble_pte(*spte)) {
				rmap_remove(kvm, spte);
				--kvm->stat.lpages;
				__set_spte(spte, shadow_trap_nonpresent_pte);
				spte = NULL;
				write_protected = 1;
			}
			spte = rmap_next(kvm, rmapp, spte);
		}
	}

	return write_protected;
}