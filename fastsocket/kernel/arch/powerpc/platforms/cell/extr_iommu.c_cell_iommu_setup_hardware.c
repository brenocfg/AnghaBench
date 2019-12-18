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
struct cbe_iommu {int /*<<< orphan*/  ptab; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_PAGE_SHIFT ; 
 int /*<<< orphan*/  cell_iommu_alloc_ptab (struct cbe_iommu*,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cell_iommu_enable_hardware (struct cbe_iommu*) ; 
 int /*<<< orphan*/  cell_iommu_setup_stab (struct cbe_iommu*,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cell_iommu_setup_hardware(struct cbe_iommu *iommu,
	unsigned long base, unsigned long size)
{
	cell_iommu_setup_stab(iommu, base, size, 0, 0);
	iommu->ptab = cell_iommu_alloc_ptab(iommu, base, size, 0, 0,
					    IOMMU_PAGE_SHIFT);
	cell_iommu_enable_hardware(iommu);
}