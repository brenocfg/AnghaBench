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
struct kvm_userspace_memory_region {int userspace_addr; int memory_size; scalar_t__ guest_phys_addr; scalar_t__ slot; } ;
struct kvm_memory_slot {int dummy; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int PAGE_SIZE ; 

int kvm_arch_prepare_memory_region(struct kvm *kvm,
				   struct kvm_memory_slot *memslot,
				   struct kvm_memory_slot old,
				   struct kvm_userspace_memory_region *mem,
				   int user_alloc)
{
	/* A few sanity checks. We can have exactly one memory slot which has
	   to start at guest virtual zero and which has to be located at a
	   page boundary in userland and which has to end at a page boundary.
	   The memory in userland is ok to be fragmented into various different
	   vmas. It is okay to mmap() and munmap() stuff in this slot after
	   doing this call at any time */

	if (mem->slot)
		return -EINVAL;

	if (mem->guest_phys_addr)
		return -EINVAL;

	if (mem->userspace_addr & (PAGE_SIZE - 1))
		return -EINVAL;

	if (mem->memory_size & (PAGE_SIZE - 1))
		return -EINVAL;

	if (!user_alloc)
		return -EINVAL;

	return 0;
}