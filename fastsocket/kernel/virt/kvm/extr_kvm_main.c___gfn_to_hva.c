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
struct kvm_memory_slot {int flags; unsigned long userspace_addr; int base_gfn; } ;
typedef  int gfn_t ;

/* Variables and functions */
 int KVM_MEMSLOT_INVALID ; 
 int PAGE_SIZE ; 
 unsigned long bad_hva () ; 

__attribute__((used)) static unsigned long
__gfn_to_hva(struct kvm_memory_slot *slot, gfn_t gfn)
{
	if (!slot || slot->flags & KVM_MEMSLOT_INVALID)
		return bad_hva();
	return (slot->userspace_addr + (gfn - slot->base_gfn) * PAGE_SIZE);
}