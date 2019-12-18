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
struct dmar_domain {int /*<<< orphan*/  gaw; int /*<<< orphan*/  iovad; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_MAX_PFN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pte_clear_range (struct dmar_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pte_free_pagetable (struct dmar_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_domain_mem (struct dmar_domain*) ; 
 int /*<<< orphan*/  iommu_free_vm_domain (struct dmar_domain*) ; 
 int /*<<< orphan*/  put_iova_domain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_domain_remove_all_dev_info (struct dmar_domain*) ; 

__attribute__((used)) static void vm_domain_exit(struct dmar_domain *domain)
{
	/* Domain 0 is reserved, so dont process it */
	if (!domain)
		return;

	vm_domain_remove_all_dev_info(domain);
	/* destroy iovas */
	put_iova_domain(&domain->iovad);

	/* clear ptes */
	dma_pte_clear_range(domain, 0, DOMAIN_MAX_PFN(domain->gaw));

	/* free page tables */
	dma_pte_free_pagetable(domain, 0, DOMAIN_MAX_PFN(domain->gaw));

	iommu_free_vm_domain(domain);
	free_domain_mem(domain);
}