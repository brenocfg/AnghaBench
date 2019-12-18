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
struct kvm_memslots {int nmemslots; struct kvm_memory_slot* memslots; } ;
struct kvm_memory_slot {scalar_t__ base_gfn; scalar_t__ npages; } ;
struct kvm {int /*<<< orphan*/  memslots; } ;
typedef  scalar_t__ gfn_t ;

/* Variables and functions */
 struct kvm_memslots* rcu_dereference (int /*<<< orphan*/ ) ; 
 scalar_t__ unalias_gfn (struct kvm*,scalar_t__) ; 

int memslot_id(struct kvm *kvm, gfn_t gfn)
{
	int i;
	struct kvm_memslots *slots = rcu_dereference(kvm->memslots);
	struct kvm_memory_slot *memslot = NULL;

	gfn = unalias_gfn(kvm, gfn);
	for (i = 0; i < slots->nmemslots; ++i) {
		memslot = &slots->memslots[i];

		if (gfn >= memslot->base_gfn
		    && gfn < memslot->base_gfn + memslot->npages)
			break;
	}

	return memslot - slots->memslots;
}