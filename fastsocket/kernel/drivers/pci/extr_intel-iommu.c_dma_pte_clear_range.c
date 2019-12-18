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
struct dmar_domain {int /*<<< orphan*/  agaw; } ;
struct dma_pte {int dummy; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int VTD_PAGE_SHIFT ; 
 int agaw_to_width (int /*<<< orphan*/ ) ; 
 unsigned long align_to_level (unsigned long,int) ; 
 int /*<<< orphan*/  dma_clear_pte (struct dma_pte*) ; 
 struct dma_pte* dma_pfn_level_pte (struct dmar_domain*,unsigned long,int) ; 
 int /*<<< orphan*/  domain_flush_cache (struct dmar_domain*,struct dma_pte*,int) ; 
 int /*<<< orphan*/  first_pte_in_page (struct dma_pte*) ; 

__attribute__((used)) static void dma_pte_clear_range(struct dmar_domain *domain,
				unsigned long start_pfn,
				unsigned long last_pfn)
{
	int addr_width = agaw_to_width(domain->agaw) - VTD_PAGE_SHIFT;
	struct dma_pte *first_pte, *pte;

	BUG_ON(addr_width < BITS_PER_LONG && start_pfn >> addr_width);
	BUG_ON(addr_width < BITS_PER_LONG && last_pfn >> addr_width);
	BUG_ON(start_pfn > last_pfn);

	/* we don't need lock here; nobody else touches the iova range */
	do {
		first_pte = pte = dma_pfn_level_pte(domain, start_pfn, 1);
		if (!pte) {
			start_pfn = align_to_level(start_pfn + 1, 2);
			continue;
		}
		do { 
			dma_clear_pte(pte);
			start_pfn++;
			pte++;
		} while (start_pfn <= last_pfn && !first_pte_in_page(pte));

		domain_flush_cache(domain, first_pte,
				   (void *)pte - (void *)first_pte);

	} while (start_pfn && start_pfn <= last_pfn);
}