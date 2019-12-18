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
struct TYPE_2__ {int /*<<< orphan*/  mmu_pte_chain_cache; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_pte_chain {int dummy; } ;

/* Variables and functions */
 struct kvm_pte_chain* mmu_memory_cache_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct kvm_pte_chain *mmu_alloc_pte_chain(struct kvm_vcpu *vcpu)
{
	return mmu_memory_cache_alloc(&vcpu->arch.mmu_pte_chain_cache,
				      sizeof(struct kvm_pte_chain));
}