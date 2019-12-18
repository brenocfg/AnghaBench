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
struct kvm_memory_slot {unsigned long* rmap; size_t base_gfn; TYPE_1__** lpage_info; } ;
struct kvm {int dummy; } ;
typedef  size_t gfn_t ;
struct TYPE_2__ {unsigned long rmap_pde; } ;

/* Variables and functions */
 size_t KVM_PAGES_PER_HPAGE (int) ; 
 int PT_PAGE_TABLE_LEVEL ; 
 struct kvm_memory_slot* gfn_to_memslot (struct kvm*,size_t) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static unsigned long *gfn_to_rmap(struct kvm *kvm, gfn_t gfn, int level)
{
	struct kvm_memory_slot *slot;
	unsigned long idx;

	slot = gfn_to_memslot(kvm, gfn);
	if (likely(level == PT_PAGE_TABLE_LEVEL))
		return &slot->rmap[gfn - slot->base_gfn];

	idx = (gfn / KVM_PAGES_PER_HPAGE(level)) -
		(slot->base_gfn / KVM_PAGES_PER_HPAGE(level));

	return &slot->lpage_info[level - 2][idx].rmap_pde;
}