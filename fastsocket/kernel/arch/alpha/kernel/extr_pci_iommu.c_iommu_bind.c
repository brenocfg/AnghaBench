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
struct pci_iommu_arena {unsigned long* ptes; int /*<<< orphan*/  lock; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 unsigned long IOMMU_RESERVED_PTE ; 
 unsigned long mk_iommu_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
iommu_bind(struct pci_iommu_arena *arena, long pg_start, long pg_count, 
	   struct page **pages)
{
	unsigned long flags;
	unsigned long *ptes;
	long i, j;

	if (!arena) return -EINVAL;
	
	spin_lock_irqsave(&arena->lock, flags);

	ptes = arena->ptes;

	for(j = pg_start; j < pg_start + pg_count; j++) {
		if (ptes[j] != IOMMU_RESERVED_PTE) {
			spin_unlock_irqrestore(&arena->lock, flags);
			return -EBUSY;
		}
	}
		
	for(i = 0, j = pg_start; i < pg_count; i++, j++)
		ptes[j] = mk_iommu_pte(page_to_phys(pages[i]));

	spin_unlock_irqrestore(&arena->lock, flags);

	return 0;
}