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
struct kvm_userspace_memory_region {unsigned int guest_phys_addr; int memory_size; int /*<<< orphan*/  flags; int /*<<< orphan*/  slot; } ;
struct TYPE_2__ {unsigned int tss_addr; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TSS_PRIVATE_MEMSLOT ; 
 int /*<<< orphan*/  init_rmode_tss (struct kvm*) ; 
 int kvm_set_memory_region (struct kvm*,struct kvm_userspace_memory_region*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmx_set_tss_addr(struct kvm *kvm, unsigned int addr)
{
	int ret;
	struct kvm_userspace_memory_region tss_mem = {
		.slot = TSS_PRIVATE_MEMSLOT,
		.guest_phys_addr = addr,
		.memory_size = PAGE_SIZE * 3,
		.flags = 0,
	};

	ret = kvm_set_memory_region(kvm, &tss_mem, 0);
	if (ret)
		return ret;
	kvm->arch.tss_addr = addr;
	if (!init_rmode_tss(kvm))
		return  -ENOMEM;

	return 0;
}