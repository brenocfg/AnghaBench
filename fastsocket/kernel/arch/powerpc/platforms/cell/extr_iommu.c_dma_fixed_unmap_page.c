#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dma_attrs {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmap_page ) (struct device*,int /*<<< orphan*/ ,size_t,int,struct dma_attrs*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_WEAK_ORDERING ; 
 int /*<<< orphan*/  cell_get_iommu_table (struct device*) ; 
 TYPE_1__ dma_direct_ops ; 
 scalar_t__ dma_get_attr (int /*<<< orphan*/ ,struct dma_attrs*) ; 
 scalar_t__ iommu_fixed_is_weak ; 
 int /*<<< orphan*/  iommu_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int,struct dma_attrs*) ; 
 int /*<<< orphan*/  stub1 (struct device*,int /*<<< orphan*/ ,size_t,int,struct dma_attrs*) ; 

__attribute__((used)) static void dma_fixed_unmap_page(struct device *dev, dma_addr_t dma_addr,
				 size_t size, enum dma_data_direction direction,
				 struct dma_attrs *attrs)
{
	if (iommu_fixed_is_weak == dma_get_attr(DMA_ATTR_WEAK_ORDERING, attrs))
		dma_direct_ops.unmap_page(dev, dma_addr, size, direction,
					  attrs);
	else
		iommu_unmap_page(cell_get_iommu_table(dev), dma_addr, size,
				 direction, attrs);
}