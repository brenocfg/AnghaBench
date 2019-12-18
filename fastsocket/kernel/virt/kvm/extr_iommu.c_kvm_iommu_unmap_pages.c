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
struct kvm_memory_slot {int /*<<< orphan*/  npages; int /*<<< orphan*/  base_gfn; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_iommu_put_pages (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kvm_iommu_unmap_pages(struct kvm *kvm, struct kvm_memory_slot *slot)
{
	kvm_iommu_put_pages(kvm, slot->base_gfn, slot->npages);
}