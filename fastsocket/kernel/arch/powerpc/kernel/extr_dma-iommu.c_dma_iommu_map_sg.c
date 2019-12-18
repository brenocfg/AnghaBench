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
struct scatterlist {int dummy; } ;
struct dma_attrs {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  device_to_mask (struct device*) ; 
 int /*<<< orphan*/  get_iommu_table_base (struct device*) ; 
 int iommu_map_sg (struct device*,int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ,int,struct dma_attrs*) ; 

__attribute__((used)) static int dma_iommu_map_sg(struct device *dev, struct scatterlist *sglist,
			    int nelems, enum dma_data_direction direction,
			    struct dma_attrs *attrs)
{
	return iommu_map_sg(dev, get_iommu_table_base(dev), sglist, nelems,
			    device_to_mask(dev), direction, attrs);
}