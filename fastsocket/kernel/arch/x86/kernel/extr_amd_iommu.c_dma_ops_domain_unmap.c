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
typedef  unsigned long long u64 ;
struct dma_ops_domain {unsigned long aperture_size; struct aperture_range** aperture; } ;
struct aperture_range {unsigned long long** pte_pages; } ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 size_t APERTURE_PAGE_INDEX (unsigned long) ; 
 size_t APERTURE_RANGE_INDEX (unsigned long) ; 
 int /*<<< orphan*/  PM_LEVEL_INDEX (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void dma_ops_domain_unmap(struct amd_iommu *iommu,
				 struct dma_ops_domain *dom,
				 unsigned long address)
{
	struct aperture_range *aperture;
	u64 *pte;

	if (address >= dom->aperture_size)
		return;

	aperture = dom->aperture[APERTURE_RANGE_INDEX(address)];
	if (!aperture)
		return;

	pte  = aperture->pte_pages[APERTURE_PAGE_INDEX(address)];
	if (!pte)
		return;

	pte += PM_LEVEL_INDEX(0, address);

	WARN_ON(!*pte);

	*pte = 0ULL;
}