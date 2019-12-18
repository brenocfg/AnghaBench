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
typedef  scalar_t__ gfn_t ;

/* Variables and functions */

__attribute__((used)) static struct kvm_memory_slot *
__gfn_to_memslot_unaliased(struct kvm_memslots *slots, gfn_t gfn)
{
	int i;

	for (i = 0; i < slots->nmemslots; ++i) {
		struct kvm_memory_slot *memslot = &slots->memslots[i];

		if (gfn >= memslot->base_gfn
		    && gfn < memslot->base_gfn + memslot->npages)
			return memslot;
	}
	return NULL;
}