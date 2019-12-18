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
struct kvm_memslots {int nmemslots; struct kvm_memory_slot* memslots; } ;
struct kvm_memory_slot {unsigned long userspace_addr; unsigned long npages; unsigned long* rmap; size_t base_gfn; TYPE_1__** lpage_info; } ;
struct kvm {int /*<<< orphan*/  memslots; } ;
typedef  size_t gfn_t ;
struct TYPE_2__ {unsigned long rmap_pde; } ;

/* Variables and functions */
 int KVM_NR_PAGE_SIZES ; 
 int KVM_PAGES_PER_HPAGE (scalar_t__) ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ PT_DIRECTORY_LEVEL ; 
 struct kvm_memslots* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_handle_hva(struct kvm *kvm, unsigned long hva,
			  unsigned long data,
			  int (*handler)(struct kvm *kvm, unsigned long *rmapp,
					 unsigned long data))
{
	int i, j;
	int retval = 0;
	struct kvm_memslots *slots;

	slots = rcu_dereference(kvm->memslots);

	for (i = 0; i < slots->nmemslots; i++) {
		struct kvm_memory_slot *memslot = &slots->memslots[i];
		unsigned long start = memslot->userspace_addr;
		unsigned long end;

		end = start + (memslot->npages << PAGE_SHIFT);
		if (hva >= start && hva < end) {
			gfn_t gfn_offset = (hva - start) >> PAGE_SHIFT;

			retval |= handler(kvm, &memslot->rmap[gfn_offset],
					  data);

			for (j = 0; j < KVM_NR_PAGE_SIZES - 1; ++j) {
				unsigned long idx;
				int nr;

				nr = KVM_PAGES_PER_HPAGE(PT_DIRECTORY_LEVEL+j);
				idx = (memslot->base_gfn+gfn_offset) / nr -
					memslot->base_gfn / nr;
				retval |= handler(kvm,
					&memslot->lpage_info[j][idx].rmap_pde,
					data);
			}
		}
	}

	return retval;
}