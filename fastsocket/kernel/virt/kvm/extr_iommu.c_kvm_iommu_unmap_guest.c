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
struct TYPE_2__ {struct iommu_domain* iommu_domain; } ;
struct kvm {int /*<<< orphan*/  slots_lock; TYPE_1__ arch; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iommu_domain_free (struct iommu_domain*) ; 
 int /*<<< orphan*/  kvm_iommu_unmap_memslots (struct kvm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int kvm_iommu_unmap_guest(struct kvm *kvm)
{
	struct iommu_domain *domain = kvm->arch.iommu_domain;

	/* check if iommu exists and in use */
	if (!domain)
		return 0;

	mutex_lock(&kvm->slots_lock);
	kvm_iommu_unmap_memslots(kvm);
	kvm->arch.iommu_domain = NULL;
	mutex_unlock(&kvm->slots_lock);

	iommu_domain_free(domain);
	return 0;
}