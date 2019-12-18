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
struct TYPE_2__ {int /*<<< orphan*/  mmu_page_header_cache; int /*<<< orphan*/  mmu_page_cache; int /*<<< orphan*/  mmu_rmap_desc_cache; int /*<<< orphan*/  mmu_pte_chain_cache; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmu_page_header_cache ; 
 int mmu_topup_memory_cache (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mmu_topup_memory_cache_page (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pte_chain_cache ; 
 int /*<<< orphan*/  rmap_desc_cache ; 

__attribute__((used)) static int mmu_topup_memory_caches(struct kvm_vcpu *vcpu)
{
	int r;

	r = mmu_topup_memory_cache(&vcpu->arch.mmu_pte_chain_cache,
				   pte_chain_cache, 4);
	if (r)
		goto out;
	r = mmu_topup_memory_cache(&vcpu->arch.mmu_rmap_desc_cache,
				   rmap_desc_cache, 4);
	if (r)
		goto out;
	r = mmu_topup_memory_cache_page(&vcpu->arch.mmu_page_cache, 8);
	if (r)
		goto out;
	r = mmu_topup_memory_cache(&vcpu->arch.mmu_page_header_cache,
				   mmu_page_header_cache, 4);
out:
	return r;
}