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
struct kvm_mmu_page {int /*<<< orphan*/  slot_bitmap; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  __pa (void*) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int memslot_id (struct kvm*,int /*<<< orphan*/ ) ; 
 struct kvm_mmu_page* page_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void page_header_update_slot(struct kvm *kvm, void *pte, gfn_t gfn)
{
	int slot = memslot_id(kvm, gfn);
	struct kvm_mmu_page *sp = page_header(__pa(pte));

	__set_bit(slot, sp->slot_bitmap);
}