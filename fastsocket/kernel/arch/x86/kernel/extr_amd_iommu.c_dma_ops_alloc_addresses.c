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
struct dma_ops_domain {int need_flush; unsigned long aperture_size; scalar_t__ next_address; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned long bad_dma_address ; 
 unsigned long dma_ops_area_alloc (struct device*,struct dma_ops_domain*,unsigned int,unsigned long,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned long dma_ops_alloc_addresses(struct device *dev,
					     struct dma_ops_domain *dom,
					     unsigned int pages,
					     unsigned long align_mask,
					     u64 dma_mask)
{
	unsigned long address;

#ifdef CONFIG_IOMMU_STRESS
	dom->next_address = 0;
	dom->need_flush = true;
#endif

	address = dma_ops_area_alloc(dev, dom, pages, align_mask,
				     dma_mask, dom->next_address);

	if (address == -1) {
		dom->next_address = 0;
		address = dma_ops_area_alloc(dev, dom, pages, align_mask,
					     dma_mask, 0);
		dom->need_flush = true;
	}

	if (unlikely(address == -1))
		address = bad_dma_address;

	WARN_ON((address + (PAGE_SIZE*pages)) > dom->aperture_size);

	return address;
}