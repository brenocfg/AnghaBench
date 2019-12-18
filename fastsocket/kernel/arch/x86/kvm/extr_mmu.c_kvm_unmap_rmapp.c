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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PT_PRESENT_MASK ; 
 int /*<<< orphan*/  __set_spte (int*,int /*<<< orphan*/ ) ; 
 int* rmap_next (struct kvm*,unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmap_printk (char*,int*,int) ; 
 int /*<<< orphan*/  rmap_remove (struct kvm*,int*) ; 
 int /*<<< orphan*/  shadow_trap_nonpresent_pte ; 

__attribute__((used)) static int kvm_unmap_rmapp(struct kvm *kvm, unsigned long *rmapp,
			   unsigned long data)
{
	u64 *spte;
	int need_tlb_flush = 0;

	while ((spte = rmap_next(kvm, rmapp, NULL))) {
		BUG_ON(!(*spte & PT_PRESENT_MASK));
		rmap_printk("kvm_rmap_unmap_hva: spte %p %llx\n", spte, *spte);
		rmap_remove(kvm, spte);
		__set_spte(spte, shadow_trap_nonpresent_pte);
		need_tlb_flush = 1;
	}
	return need_tlb_flush;
}