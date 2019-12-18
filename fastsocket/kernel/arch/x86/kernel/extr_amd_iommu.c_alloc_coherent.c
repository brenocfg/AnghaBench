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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct protection_domain {int /*<<< orphan*/  lock; int /*<<< orphan*/  priv; } ;
struct device {scalar_t__* dma_mask; scalar_t__ coherent_dma_mask; } ;
struct amd_iommu {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  int gfp_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  INC_STATS_COUNTER (int /*<<< orphan*/ ) ; 
 int __GFP_DMA ; 
 int __GFP_DMA32 ; 
 int __GFP_HIGHMEM ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 scalar_t__ __map_single (struct device*,struct amd_iommu*,int /*<<< orphan*/ ,scalar_t__,size_t,int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ bad_dma_address ; 
 int /*<<< orphan*/  check_device (struct device*) ; 
 int /*<<< orphan*/  cnt_alloc_coherent ; 
 int /*<<< orphan*/  dma_ops_domain (struct protection_domain*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device_resources (struct device*,struct amd_iommu**,struct protection_domain**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 int /*<<< orphan*/  iommu_completion_wait (struct amd_iommu*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ virt_to_phys (void*) ; 

__attribute__((used)) static void *alloc_coherent(struct device *dev, size_t size,
			    dma_addr_t *dma_addr, gfp_t flag)
{
	unsigned long flags;
	void *virt_addr;
	struct amd_iommu *iommu;
	struct protection_domain *domain;
	u16 devid;
	phys_addr_t paddr;
	u64 dma_mask = dev->coherent_dma_mask;

	INC_STATS_COUNTER(cnt_alloc_coherent);

	if (!check_device(dev))
		return NULL;

	if (!get_device_resources(dev, &iommu, &domain, &devid))
		flag &= ~(__GFP_DMA | __GFP_HIGHMEM | __GFP_DMA32);

	flag |= __GFP_ZERO;
	virt_addr = (void *)__get_free_pages(flag, get_order(size));
	if (!virt_addr)
		return NULL;

	paddr = virt_to_phys(virt_addr);

	if (!iommu || !domain) {
		*dma_addr = (dma_addr_t)paddr;
		return virt_addr;
	}

	if (!dma_ops_domain(domain))
		goto out_free;

	if (!dma_mask)
		dma_mask = *dev->dma_mask;

	spin_lock_irqsave(&domain->lock, flags);

	*dma_addr = __map_single(dev, iommu, domain->priv, paddr,
				 size, DMA_BIDIRECTIONAL, true, dma_mask);

	if (*dma_addr == bad_dma_address) {
		spin_unlock_irqrestore(&domain->lock, flags);
		goto out_free;
	}

	iommu_completion_wait(iommu);

	spin_unlock_irqrestore(&domain->lock, flags);

	return virt_addr;

out_free:

	free_pages((unsigned long)virt_addr, get_order(size));

	return NULL;
}