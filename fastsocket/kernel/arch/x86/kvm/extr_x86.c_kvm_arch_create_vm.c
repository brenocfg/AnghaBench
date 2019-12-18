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
struct kvm_mem_aliases {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tsc_write_lock; int /*<<< orphan*/  irq_sources_bitmap; int /*<<< orphan*/  assigned_dev_head; int /*<<< orphan*/  active_mmu_pages; void* aliases; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct kvm* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KVM_USERSPACE_IRQ_SOURCE_ID ; 
 int /*<<< orphan*/  kfree (struct kvm*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct  kvm *kvm_arch_create_vm(void)
{
	struct kvm *kvm = kzalloc(sizeof(struct kvm), GFP_KERNEL);

	if (!kvm)
		return ERR_PTR(-ENOMEM);

	kvm->arch.aliases = kzalloc(sizeof(struct kvm_mem_aliases), GFP_KERNEL);
	if (!kvm->arch.aliases) {
		kfree(kvm);
		return ERR_PTR(-ENOMEM);
	}

	INIT_LIST_HEAD(&kvm->arch.active_mmu_pages);
	INIT_LIST_HEAD(&kvm->arch.assigned_dev_head);

	/* Reserve bit 0 of irq_sources_bitmap for userspace irq source */
	set_bit(KVM_USERSPACE_IRQ_SOURCE_ID, &kvm->arch.irq_sources_bitmap);

	spin_lock_init(&kvm->arch.tsc_write_lock);

	return kvm;
}