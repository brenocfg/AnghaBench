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
struct dmar_domain {struct dma_pte* pgd; int /*<<< orphan*/  agaw; } ;
struct dma_pte {int dummy; } ;

/* Variables and functions */
 int agaw_to_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pte_addr (struct dma_pte*) ; 
 int /*<<< orphan*/  dma_pte_present (struct dma_pte*) ; 
 int pfn_level_offset (unsigned long,int) ; 
 struct dma_pte* phys_to_virt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dma_pte *dma_pfn_level_pte(struct dmar_domain *domain,
					 unsigned long pfn,
					 int level)
{
	struct dma_pte *parent, *pte = NULL;
	int total = agaw_to_level(domain->agaw);
	int offset;

	parent = domain->pgd;
	while (level <= total) {
		offset = pfn_level_offset(pfn, total);
		pte = &parent[offset];
		if (level == total)
			return pte;

		if (!dma_pte_present(pte))
			break;
		parent = phys_to_virt(dma_pte_addr(pte));
		total--;
	}
	return NULL;
}