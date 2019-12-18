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
typedef  int /*<<< orphan*/  u64 ;
struct protection_domain {int mode; int /*<<< orphan*/ * pt_root; } ;

/* Variables and functions */
 int /*<<< orphan*/ * IOMMU_PTE_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOMMU_PTE_PRESENT (int /*<<< orphan*/ ) ; 
 size_t PM_LEVEL_INDEX (int,unsigned long) ; 
 scalar_t__ PM_PTE_LEVEL (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 *fetch_pte(struct protection_domain *domain,
		      unsigned long address, int map_size)
{
	int level;
	u64 *pte;

	level =  domain->mode - 1;
	pte   = &domain->pt_root[PM_LEVEL_INDEX(level, address)];

	while (level > map_size) {
		if (!IOMMU_PTE_PRESENT(*pte))
			return NULL;

		level -= 1;

		pte = IOMMU_PTE_PAGE(*pte);
		pte = &pte[PM_LEVEL_INDEX(level, address)];

		if ((PM_PTE_LEVEL(*pte) == 0) && level != map_size) {
			pte = NULL;
			break;
		}
	}

	return pte;
}