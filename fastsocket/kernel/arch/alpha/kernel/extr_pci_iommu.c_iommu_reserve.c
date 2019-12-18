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
struct pci_iommu_arena {unsigned long* ptes; long next_entry; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long IOMMU_RESERVED_PTE ; 
 long iommu_arena_find_pages (int /*<<< orphan*/ *,struct pci_iommu_arena*,long,long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
iommu_reserve(struct pci_iommu_arena *arena, long pg_count, long align_mask) 
{
	unsigned long flags;
	unsigned long *ptes;
	long i, p;

	if (!arena) return -EINVAL;

	spin_lock_irqsave(&arena->lock, flags);

	/* Search for N empty ptes.  */
	ptes = arena->ptes;
	p = iommu_arena_find_pages(NULL, arena, pg_count, align_mask);
	if (p < 0) {
		spin_unlock_irqrestore(&arena->lock, flags);
		return -1;
	}

	/* Success.  Mark them all reserved (ie not zero and invalid)
	   for the iommu tlb that could load them from under us.
	   They will be filled in with valid bits by _bind() */
	for (i = 0; i < pg_count; ++i)
		ptes[p+i] = IOMMU_RESERVED_PTE;

	arena->next_entry = p + pg_count;
	spin_unlock_irqrestore(&arena->lock, flags);

	return p;
}