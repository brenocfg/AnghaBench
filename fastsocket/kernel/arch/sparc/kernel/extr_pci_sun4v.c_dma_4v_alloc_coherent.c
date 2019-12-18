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
struct page {int dummy; } ;
struct iommu {int /*<<< orphan*/  lock; scalar_t__ page_table_map_base; } ;
struct TYPE_2__ {int numa_node; struct iommu* iommu; } ;
struct device {TYPE_1__ archdata; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 long DMA_ERROR_CODE ; 
 int HV_PCI_MAP_ATTR_READ ; 
 int HV_PCI_MAP_ATTR_WRITE ; 
 size_t IO_PAGE_ALIGN (size_t) ; 
 size_t IO_PAGE_SHIFT ; 
 unsigned long MAX_ORDER ; 
 unsigned long PAGE_SIZE ; 
 unsigned long __pa (unsigned long) ; 
 struct page* alloc_pages_node (int,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  free_pages (unsigned long,unsigned long) ; 
 unsigned long get_order (size_t) ; 
 long iommu_batch_add (unsigned long) ; 
 long iommu_batch_end () ; 
 int /*<<< orphan*/  iommu_batch_start (struct device*,int,long) ; 
 long iommu_range_alloc (struct device*,struct iommu*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iommu_range_free (struct iommu*,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void *dma_4v_alloc_coherent(struct device *dev, size_t size,
				   dma_addr_t *dma_addrp, gfp_t gfp)
{
	unsigned long flags, order, first_page, npages, n;
	struct iommu *iommu;
	struct page *page;
	void *ret;
	long entry;
	int nid;

	size = IO_PAGE_ALIGN(size);
	order = get_order(size);
	if (unlikely(order >= MAX_ORDER))
		return NULL;

	npages = size >> IO_PAGE_SHIFT;

	nid = dev->archdata.numa_node;
	page = alloc_pages_node(nid, gfp, order);
	if (unlikely(!page))
		return NULL;

	first_page = (unsigned long) page_address(page);
	memset((char *)first_page, 0, PAGE_SIZE << order);

	iommu = dev->archdata.iommu;

	spin_lock_irqsave(&iommu->lock, flags);
	entry = iommu_range_alloc(dev, iommu, npages, NULL);
	spin_unlock_irqrestore(&iommu->lock, flags);

	if (unlikely(entry == DMA_ERROR_CODE))
		goto range_alloc_fail;

	*dma_addrp = (iommu->page_table_map_base +
		      (entry << IO_PAGE_SHIFT));
	ret = (void *) first_page;
	first_page = __pa(first_page);

	local_irq_save(flags);

	iommu_batch_start(dev,
			  (HV_PCI_MAP_ATTR_READ |
			   HV_PCI_MAP_ATTR_WRITE),
			  entry);

	for (n = 0; n < npages; n++) {
		long err = iommu_batch_add(first_page + (n * PAGE_SIZE));
		if (unlikely(err < 0L))
			goto iommu_map_fail;
	}

	if (unlikely(iommu_batch_end() < 0L))
		goto iommu_map_fail;

	local_irq_restore(flags);

	return ret;

iommu_map_fail:
	/* Interrupts are disabled.  */
	spin_lock(&iommu->lock);
	iommu_range_free(iommu, *dma_addrp, npages);
	spin_unlock_irqrestore(&iommu->lock, flags);

range_alloc_fail:
	free_pages(first_page, order);
	return NULL;
}