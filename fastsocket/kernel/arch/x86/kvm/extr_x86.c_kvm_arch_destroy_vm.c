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
struct TYPE_2__ {struct kvm* aliases; scalar_t__ ept_identity_pagetable; scalar_t__ apic_access_page; struct kvm* vioapic; struct kvm* vpic; } ;
struct kvm {TYPE_1__ arch; int /*<<< orphan*/  srcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct kvm*) ; 
 int /*<<< orphan*/  kvm_free_physmem (struct kvm*) ; 
 int /*<<< orphan*/  kvm_free_vcpus (struct kvm*) ; 
 int /*<<< orphan*/  kvm_iommu_unmap_guest (struct kvm*) ; 
 int /*<<< orphan*/  put_page (scalar_t__) ; 

void kvm_arch_destroy_vm(struct kvm *kvm)
{
	kvm_iommu_unmap_guest(kvm);
	kfree(kvm->arch.vpic);
	kfree(kvm->arch.vioapic);
	kvm_free_vcpus(kvm);
	kvm_free_physmem(kvm);
	if (kvm->arch.apic_access_page)
		put_page(kvm->arch.apic_access_page);
	if (kvm->arch.ept_identity_pagetable)
		put_page(kvm->arch.ept_identity_pagetable);
	cleanup_srcu_struct(&kvm->srcu);
	kfree(kvm->arch.aliases);
	kfree(kvm);
}