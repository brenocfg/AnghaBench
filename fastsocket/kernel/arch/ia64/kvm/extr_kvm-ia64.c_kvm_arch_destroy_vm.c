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
struct TYPE_2__ {int /*<<< orphan*/  vioapic; } ;
struct kvm {int /*<<< orphan*/  srcu; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_kvm (struct kvm*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_free_all_assigned_devices (struct kvm*) ; 
 int /*<<< orphan*/  kvm_free_physmem (struct kvm*) ; 
 int /*<<< orphan*/  kvm_iommu_unmap_guest (struct kvm*) ; 
 int /*<<< orphan*/  kvm_release_vm_pages (struct kvm*) ; 

void kvm_arch_destroy_vm(struct kvm *kvm)
{
	kvm_iommu_unmap_guest(kvm);
#ifdef  KVM_CAP_DEVICE_ASSIGNMENT
	kvm_free_all_assigned_devices(kvm);
#endif
	kfree(kvm->arch.vioapic);
	kvm_release_vm_pages(kvm);
	kvm_free_physmem(kvm);
	cleanup_srcu_struct(&kvm->srcu);
	free_kvm(kvm);
}