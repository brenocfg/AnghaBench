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
struct pci_iommu_arena {unsigned long* ptes; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long IOMMU_RESERVED_PTE ; 

int
iommu_unbind(struct pci_iommu_arena *arena, long pg_start, long pg_count)
{
	unsigned long *p;
	long i;

	if (!arena) return -EINVAL;

	p = arena->ptes + pg_start;
	for(i = 0; i < pg_count; i++)
		p[i] = IOMMU_RESERVED_PTE;

	return 0;
}