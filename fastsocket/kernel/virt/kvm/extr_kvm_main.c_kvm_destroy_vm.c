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
struct mm_struct {int dummy; } ;
struct kvm {struct mm_struct* mm; int /*<<< orphan*/  mmu_notifier; int /*<<< orphan*/ * coalesced_mmio_ring; int /*<<< orphan*/ * buses; int /*<<< orphan*/  vm_list; } ;

/* Variables and functions */
 int KVM_NR_BUSES ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  hardware_disable_all () ; 
 int /*<<< orphan*/  kvm_arch_destroy_vm (struct kvm*) ; 
 int /*<<< orphan*/  kvm_arch_flush_shadow (struct kvm*) ; 
 int /*<<< orphan*/  kvm_arch_sync_events (struct kvm*) ; 
 int /*<<< orphan*/  kvm_free_irq_routing (struct kvm*) ; 
 int /*<<< orphan*/  kvm_io_bus_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmdrop (struct mm_struct*) ; 
 int /*<<< orphan*/  mmu_notifier_unregister (int /*<<< orphan*/ *,struct mm_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvm_destroy_vm(struct kvm *kvm)
{
	int i;
	struct mm_struct *mm = kvm->mm;

	kvm_arch_sync_events(kvm);
	spin_lock(&kvm_lock);
	list_del(&kvm->vm_list);
	spin_unlock(&kvm_lock);
	kvm_free_irq_routing(kvm);
	for (i = 0; i < KVM_NR_BUSES; i++)
		kvm_io_bus_destroy(kvm->buses[i]);
#ifdef KVM_COALESCED_MMIO_PAGE_OFFSET
	if (kvm->coalesced_mmio_ring != NULL)
		free_page((unsigned long)kvm->coalesced_mmio_ring);
#endif
#if defined(CONFIG_MMU_NOTIFIER) && defined(KVM_ARCH_WANT_MMU_NOTIFIER)
	mmu_notifier_unregister(&kvm->mmu_notifier, kvm->mm);
#else
	kvm_arch_flush_shadow(kvm);
#endif
	kvm_arch_destroy_vm(kvm);
	hardware_disable_all();
	mmdrop(mm);
}