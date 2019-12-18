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
struct iommu {int /*<<< orphan*/ * page_table; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  iopte_t ;

/* Variables and functions */
 unsigned long DMA_ERROR_CODE ; 
 unsigned long iommu_range_alloc (struct device*,struct iommu*,unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline iopte_t *alloc_npages(struct device *dev, struct iommu *iommu,
				    unsigned long npages)
{
	unsigned long entry;

	entry = iommu_range_alloc(dev, iommu, npages, NULL);
	if (unlikely(entry == DMA_ERROR_CODE))
		return NULL;

	return iommu->page_table + entry;
}