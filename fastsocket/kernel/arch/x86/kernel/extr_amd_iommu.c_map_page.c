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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct protection_domain {int /*<<< orphan*/  lock; int /*<<< orphan*/  priv; } ;
struct page {int dummy; } ;
struct dma_attrs {int dummy; } ;
struct device {int /*<<< orphan*/ * dma_mask; } ;
struct amd_iommu {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  INC_STATS_COUNTER (int /*<<< orphan*/ ) ; 
 scalar_t__ __map_single (struct device*,struct amd_iommu*,int /*<<< orphan*/ ,scalar_t__,size_t,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bad_dma_address ; 
 int /*<<< orphan*/  check_device (struct device*) ; 
 int /*<<< orphan*/  cnt_map_single ; 
 int /*<<< orphan*/  dma_ops_domain (struct protection_domain*) ; 
 int /*<<< orphan*/  get_device_resources (struct device*,struct amd_iommu**,struct protection_domain**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_completion_wait (struct amd_iommu*) ; 
 scalar_t__ page_to_phys (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static dma_addr_t map_page(struct device *dev, struct page *page,
			   unsigned long offset, size_t size,
			   enum dma_data_direction dir,
			   struct dma_attrs *attrs)
{
	unsigned long flags;
	struct amd_iommu *iommu;
	struct protection_domain *domain;
	u16 devid;
	dma_addr_t addr;
	u64 dma_mask;
	phys_addr_t paddr = page_to_phys(page) + offset;

	INC_STATS_COUNTER(cnt_map_single);

	if (!check_device(dev))
		return bad_dma_address;

	dma_mask = *dev->dma_mask;

	get_device_resources(dev, &iommu, &domain, &devid);

	if (iommu == NULL || domain == NULL)
		/* device not handled by any AMD IOMMU */
		return (dma_addr_t)paddr;

	if (!dma_ops_domain(domain))
		return bad_dma_address;

	spin_lock_irqsave(&domain->lock, flags);
	addr = __map_single(dev, iommu, domain->priv, paddr, size, dir, false,
			    dma_mask);
	if (addr == bad_dma_address)
		goto out;

	iommu_completion_wait(iommu);

out:
	spin_unlock_irqrestore(&domain->lock, flags);

	return addr;
}