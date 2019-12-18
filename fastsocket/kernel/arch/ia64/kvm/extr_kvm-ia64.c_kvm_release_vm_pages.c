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
struct page {int dummy; } ;
struct kvm_memslots {int nmemslots; struct kvm_memory_slot* memslots; } ;
struct kvm_memory_slot {unsigned long base_gfn; int npages; scalar_t__* rmap; } ;
struct kvm {int /*<<< orphan*/  memslots; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct kvm_memslots* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_release_vm_pages(struct kvm *kvm)
{
	struct kvm_memslots *slots;
	struct kvm_memory_slot *memslot;
	int i, j;
	unsigned long base_gfn;

	slots = rcu_dereference(kvm->memslots);
	for (i = 0; i < slots->nmemslots; i++) {
		memslot = &slots->memslots[i];
		base_gfn = memslot->base_gfn;

		for (j = 0; j < memslot->npages; j++) {
			if (memslot->rmap[j])
				put_page((struct page *)memslot->rmap[j]);
		}
	}
}