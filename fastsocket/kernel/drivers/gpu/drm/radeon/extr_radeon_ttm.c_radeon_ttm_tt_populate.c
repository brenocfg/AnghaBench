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
struct ttm_tt {int page_flags; scalar_t__ state; unsigned int num_pages; int /*<<< orphan*/ * pages; int /*<<< orphan*/  bdev; scalar_t__ sg; } ;
struct TYPE_2__ {scalar_t__* dma_address; } ;
struct radeon_ttm_tt {TYPE_1__ ttm; } ;
struct radeon_device {int flags; int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int RADEON_IS_AGP ; 
 int TTM_PAGE_FLAG_SG ; 
 int /*<<< orphan*/  drm_prime_sg_to_page_addr_arrays (scalar_t__,int /*<<< orphan*/ *,scalar_t__*,unsigned int) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pci_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct radeon_device* radeon_get_rdev (int /*<<< orphan*/ ) ; 
 scalar_t__ swiotlb_nr_tbl () ; 
 scalar_t__ tt_unbound ; 
 scalar_t__ tt_unpopulated ; 
 int ttm_agp_tt_populate (struct ttm_tt*) ; 
 int ttm_dma_populate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int ttm_pool_populate (struct ttm_tt*) ; 
 int /*<<< orphan*/  ttm_pool_unpopulate (struct ttm_tt*) ; 

__attribute__((used)) static int radeon_ttm_tt_populate(struct ttm_tt *ttm)
{
	struct radeon_device *rdev;
	struct radeon_ttm_tt *gtt = (void *)ttm;
	unsigned i;
	int r;
	bool slave = !!(ttm->page_flags & TTM_PAGE_FLAG_SG);

	if (ttm->state != tt_unpopulated)
		return 0;

	if (slave && ttm->sg) {
		drm_prime_sg_to_page_addr_arrays(ttm->sg, ttm->pages,
						 gtt->ttm.dma_address, ttm->num_pages);
		ttm->state = tt_unbound;
		return 0;
	}

	rdev = radeon_get_rdev(ttm->bdev);
#if __OS_HAS_AGP
	if (rdev->flags & RADEON_IS_AGP) {
		return ttm_agp_tt_populate(ttm);
	}
#endif

#ifdef CONFIG_SWIOTLB
	if (swiotlb_nr_tbl()) {
		return ttm_dma_populate(&gtt->ttm, rdev->dev);
	}
#endif

	r = ttm_pool_populate(ttm);
	if (r) {
		return r;
	}

	for (i = 0; i < ttm->num_pages; i++) {
		gtt->ttm.dma_address[i] = pci_map_page(rdev->pdev, ttm->pages[i],
						       0, PAGE_SIZE,
						       PCI_DMA_BIDIRECTIONAL);
		if (pci_dma_mapping_error(rdev->pdev, gtt->ttm.dma_address[i])) {
			while (--i) {
				pci_unmap_page(rdev->pdev, gtt->ttm.dma_address[i],
					       PAGE_SIZE, PCI_DMA_BIDIRECTIONAL);
				gtt->ttm.dma_address[i] = 0;
			}
			ttm_pool_unpopulate(ttm);
			return -EFAULT;
		}
	}
	return 0;
}