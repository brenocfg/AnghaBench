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
struct page {int dummy; } ;
struct dma_attrs {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_to_mask (struct device*) ; 
 int /*<<< orphan*/  get_iommu_table_base (struct device*) ; 
 int /*<<< orphan*/  iommu_map_page (struct device*,int /*<<< orphan*/ ,struct page*,unsigned long,size_t,int /*<<< orphan*/ ,int,struct dma_attrs*) ; 

__attribute__((used)) static dma_addr_t dma_iommu_map_page(struct device *dev, struct page *page,
				     unsigned long offset, size_t size,
				     enum dma_data_direction direction,
				     struct dma_attrs *attrs)
{
	return iommu_map_page(dev, get_iommu_table_base(dev), page, offset,
			      size, device_to_mask(dev), direction, attrs);
}