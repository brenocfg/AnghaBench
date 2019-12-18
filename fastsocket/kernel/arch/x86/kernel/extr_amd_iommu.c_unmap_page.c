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
typedef  int /*<<< orphan*/  u16 ;
struct protection_domain {int /*<<< orphan*/  lock; int /*<<< orphan*/  priv; } ;
struct dma_attrs {int dummy; } ;
struct device {int dummy; } ;
struct amd_iommu {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  INC_STATS_COUNTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __unmap_single (struct amd_iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  check_device (struct device*) ; 
 int /*<<< orphan*/  cnt_unmap_single ; 
 int /*<<< orphan*/  dma_ops_domain (struct protection_domain*) ; 
 int /*<<< orphan*/  get_device_resources (struct device*,struct amd_iommu**,struct protection_domain**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_completion_wait (struct amd_iommu*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void unmap_page(struct device *dev, dma_addr_t dma_addr, size_t size,
		       enum dma_data_direction dir, struct dma_attrs *attrs)
{
	unsigned long flags;
	struct amd_iommu *iommu;
	struct protection_domain *domain;
	u16 devid;

	INC_STATS_COUNTER(cnt_unmap_single);

	if (!check_device(dev) ||
	    !get_device_resources(dev, &iommu, &domain, &devid))
		/* device not handled by any AMD IOMMU */
		return;

	if (!dma_ops_domain(domain))
		return;

	spin_lock_irqsave(&domain->lock, flags);

	__unmap_single(iommu, domain->priv, dma_addr, size, dir);

	iommu_completion_wait(iommu);

	spin_unlock_irqrestore(&domain->lock, flags);
}