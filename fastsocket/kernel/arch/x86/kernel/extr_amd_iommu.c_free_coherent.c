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
struct device {int dummy; } ;
struct amd_iommu {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  INC_STATS_COUNTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __unmap_single (struct amd_iommu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_device (struct device*) ; 
 int /*<<< orphan*/  cnt_free_coherent ; 
 int /*<<< orphan*/  dma_ops_domain (struct protection_domain*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device_resources (struct device*,struct amd_iommu**,struct protection_domain**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  iommu_completion_wait (struct amd_iommu*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void free_coherent(struct device *dev, size_t size,
			  void *virt_addr, dma_addr_t dma_addr)
{
	unsigned long flags;
	struct amd_iommu *iommu;
	struct protection_domain *domain;
	u16 devid;

	INC_STATS_COUNTER(cnt_free_coherent);

	if (!check_device(dev))
		return;

	get_device_resources(dev, &iommu, &domain, &devid);

	if (!iommu || !domain)
		goto free_mem;

	if (!dma_ops_domain(domain))
		goto free_mem;

	spin_lock_irqsave(&domain->lock, flags);

	__unmap_single(iommu, domain->priv, dma_addr, size, DMA_BIDIRECTIONAL);

	iommu_completion_wait(iommu);

	spin_unlock_irqrestore(&domain->lock, flags);

free_mem:
	free_pages((unsigned long)virt_addr, get_order(size));
}