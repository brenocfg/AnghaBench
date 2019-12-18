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
 unsigned long __gfn_to_hva (struct kvm_memory_slot*,int /*<<< orphan*/ ) ; 
 struct kvm_memory_slot* gfn_to_memslot_unaliased (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unalias_gfn_instantiation (struct kvm*,int /*<<< orphan*/ ) ; 

unsigned long gfn_to_hva(struct kvm *kvm, gfn_t gfn)
{
	struct kvm_memory_slot *slot;

	gfn = unalias_gfn_instantiation(kvm, gfn);
	slot = gfn_to_memslot_unaliased(kvm, gfn);
	return __gfn_to_hva(slot, gfn);
}