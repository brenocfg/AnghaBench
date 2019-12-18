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
struct kvm_memslots {int nmemslots; int /*<<< orphan*/ * memslots; } ;
struct kvm {int /*<<< orphan*/  memslots; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_iommu_unmap_pages (struct kvm*,int /*<<< orphan*/ *) ; 
 struct kvm_memslots* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_iommu_unmap_memslots(struct kvm *kvm)
{
	int i;
	struct kvm_memslots *slots;

	slots = rcu_dereference(kvm->memslots);

	for (i = 0; i < slots->nmemslots; i++) {
		kvm_iommu_unmap_pages(kvm, &slots->memslots[i]);
	}

	return 0;
}