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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  destroy_kvm_mmu (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  free_mmu_pages (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  mmu_free_memory_caches (struct kvm_vcpu*) ; 

void kvm_mmu_destroy(struct kvm_vcpu *vcpu)
{
	ASSERT(vcpu);

	destroy_kvm_mmu(vcpu);
	free_mmu_pages(vcpu);
	mmu_free_memory_caches(vcpu);
}