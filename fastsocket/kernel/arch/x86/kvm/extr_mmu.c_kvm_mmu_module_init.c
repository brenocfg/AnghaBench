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
struct kvm_rmap_desc {int dummy; } ;
struct kvm_pte_chain {int dummy; } ;
struct kvm_mmu_page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_total_used_mmu_pages ; 
 int /*<<< orphan*/  mmu_destroy_caches () ; 
 void* mmu_page_header_cache ; 
 int /*<<< orphan*/  mmu_shrinker ; 
 scalar_t__ percpu_counter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* pte_chain_cache ; 
 int /*<<< orphan*/  register_shrinker (int /*<<< orphan*/ *) ; 
 void* rmap_desc_cache ; 

int kvm_mmu_module_init(void)
{
	pte_chain_cache = kmem_cache_create("kvm_pte_chain",
					    sizeof(struct kvm_pte_chain),
					    0, 0, NULL);
	if (!pte_chain_cache)
		goto nomem;
	rmap_desc_cache = kmem_cache_create("kvm_rmap_desc",
					    sizeof(struct kvm_rmap_desc),
					    0, 0, NULL);
	if (!rmap_desc_cache)
		goto nomem;

	mmu_page_header_cache = kmem_cache_create("kvm_mmu_page_header",
						  sizeof(struct kvm_mmu_page),
						  0, 0, NULL);
	if (!mmu_page_header_cache)
		goto nomem;

	if (percpu_counter_init(&kvm_total_used_mmu_pages, 0))
		goto nomem;

	register_shrinker(&mmu_shrinker);

	return 0;

nomem:
	mmu_destroy_caches();
	return -ENOMEM;
}