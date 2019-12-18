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
 struct kvm_memory_slot* gfn_to_memslot_unaliased (struct kvm*,int /*<<< orphan*/ ) ; 
 int* slot_largepage_idx (int /*<<< orphan*/ ,struct kvm_memory_slot*,int) ; 
 int /*<<< orphan*/  unalias_gfn (struct kvm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int has_wrprotected_page(struct kvm *kvm,
				gfn_t gfn,
				int level)
{
	struct kvm_memory_slot *slot;
	int *largepage_idx;

	gfn = unalias_gfn(kvm, gfn);
	slot = gfn_to_memslot_unaliased(kvm, gfn);
	if (slot) {
		largepage_idx = slot_largepage_idx(gfn, slot, level);
		return *largepage_idx;
	}

	return 1;
}