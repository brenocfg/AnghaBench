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
struct kvm_userspace_memory_region {int guest_phys_addr; int /*<<< orphan*/  memory_size; scalar_t__ flags; int /*<<< orphan*/  slot; } ;
struct TYPE_2__ {int ept_identity_map_addr; scalar_t__ ept_identity_pagetable; } ;
struct kvm {int /*<<< orphan*/  slots_lock; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDENTITY_PAGETABLE_PRIVATE_MEMSLOT ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __kvm_set_memory_region (struct kvm*,struct kvm_userspace_memory_region*,int /*<<< orphan*/ ) ; 
 scalar_t__ gfn_to_page (struct kvm*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alloc_identity_pagetable(struct kvm *kvm)
{
	struct kvm_userspace_memory_region kvm_userspace_mem;
	int r = 0;

	mutex_lock(&kvm->slots_lock);
	if (kvm->arch.ept_identity_pagetable)
		goto out;
	kvm_userspace_mem.slot = IDENTITY_PAGETABLE_PRIVATE_MEMSLOT;
	kvm_userspace_mem.flags = 0;
	kvm_userspace_mem.guest_phys_addr =
		kvm->arch.ept_identity_map_addr;
	kvm_userspace_mem.memory_size = PAGE_SIZE;
	r = __kvm_set_memory_region(kvm, &kvm_userspace_mem, 0);
	if (r)
		goto out;

	kvm->arch.ept_identity_pagetable = gfn_to_page(kvm,
			kvm->arch.ept_identity_map_addr >> PAGE_SHIFT);
out:
	mutex_unlock(&kvm->slots_lock);
	return r;
}