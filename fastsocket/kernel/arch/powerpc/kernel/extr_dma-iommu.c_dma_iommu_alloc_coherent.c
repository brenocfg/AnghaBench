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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_to_node (struct device*) ; 
 int /*<<< orphan*/  device_to_mask (struct device*) ; 
 int /*<<< orphan*/  get_iommu_table_base (struct device*) ; 
 void* iommu_alloc_coherent (struct device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *dma_iommu_alloc_coherent(struct device *dev, size_t size,
				      dma_addr_t *dma_handle, gfp_t flag)
{
	return iommu_alloc_coherent(dev, get_iommu_table_base(dev), size,
				    dma_handle, device_to_mask(dev), flag,
				    dev_to_node(dev));
}