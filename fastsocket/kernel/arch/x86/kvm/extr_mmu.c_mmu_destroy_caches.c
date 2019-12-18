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

/* Variables and functions */
 int /*<<< orphan*/  kmem_cache_destroy (scalar_t__) ; 
 scalar_t__ mmu_page_header_cache ; 
 scalar_t__ pte_chain_cache ; 
 scalar_t__ rmap_desc_cache ; 

__attribute__((used)) static void mmu_destroy_caches(void)
{
	if (pte_chain_cache)
		kmem_cache_destroy(pte_chain_cache);
	if (rmap_desc_cache)
		kmem_cache_destroy(rmap_desc_cache);
	if (mmu_page_header_cache)
		kmem_cache_destroy(mmu_page_header_cache);
}