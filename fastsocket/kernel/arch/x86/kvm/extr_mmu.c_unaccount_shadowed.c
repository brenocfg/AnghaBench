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
struct kvm_memory_slot {int dummy; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int KVM_NR_PAGE_SIZES ; 
 int PT_DIRECTORY_LEVEL ; 
 int PT_PAGE_TABLE_LEVEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct kvm_memory_slot* gfn_to_memslot_unaliased (struct kvm*,int /*<<< orphan*/ ) ; 
 int* slot_largepage_idx (int /*<<< orphan*/ ,struct kvm_memory_slot*,int) ; 
 int /*<<< orphan*/  unalias_gfn (struct kvm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unaccount_shadowed(struct kvm *kvm, gfn_t gfn)
{
	struct kvm_memory_slot *slot;
	int *write_count;
	int i;

	gfn = unalias_gfn(kvm, gfn);
	for (i = PT_DIRECTORY_LEVEL;
	     i < PT_PAGE_TABLE_LEVEL + KVM_NR_PAGE_SIZES; ++i) {
		slot          = gfn_to_memslot_unaliased(kvm, gfn);
		write_count   = slot_largepage_idx(gfn, slot, i);
		*write_count -= 1;
		WARN_ON(*write_count < 0);
	}
}