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
struct iommu_table {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 size_t PAGE_ALIGN (size_t) ; 
 size_t PAGE_SHIFT ; 
 struct iommu_table* find_iommu_table (struct device*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  iommu_free (struct iommu_table*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void calgary_free_coherent(struct device *dev, size_t size,
				  void *vaddr, dma_addr_t dma_handle)
{
	unsigned int npages;
	struct iommu_table *tbl = find_iommu_table(dev);

	size = PAGE_ALIGN(size);
	npages = size >> PAGE_SHIFT;

	iommu_free(tbl, dma_handle, npages);
	free_pages((unsigned long)vaddr, get_order(size));
}