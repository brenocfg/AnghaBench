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
struct ttm_tt {int page_flags; unsigned int num_pages; int /*<<< orphan*/  bdev; } ;
struct TYPE_2__ {scalar_t__* dma_address; } ;
struct radeon_ttm_tt {TYPE_1__ ttm; } ;
struct radeon_device {int flags; int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int RADEON_IS_AGP ; 
 int TTM_PAGE_FLAG_SG ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct radeon_device* radeon_get_rdev (int /*<<< orphan*/ ) ; 
 scalar_t__ swiotlb_nr_tbl () ; 
 int /*<<< orphan*/  ttm_agp_tt_unpopulate (struct ttm_tt*) ; 
 int /*<<< orphan*/  ttm_dma_unpopulate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_pool_unpopulate (struct ttm_tt*) ; 

__attribute__((used)) static void radeon_ttm_tt_unpopulate(struct ttm_tt *ttm)
{
	struct radeon_device *rdev;
	struct radeon_ttm_tt *gtt = (void *)ttm;
	unsigned i;
	bool slave = !!(ttm->page_flags & TTM_PAGE_FLAG_SG);

	if (slave)
		return;

	rdev = radeon_get_rdev(ttm->bdev);
#if __OS_HAS_AGP
	if (rdev->flags & RADEON_IS_AGP) {
		ttm_agp_tt_unpopulate(ttm);
		return;
	}
#endif

#ifdef CONFIG_SWIOTLB
	if (swiotlb_nr_tbl()) {
		ttm_dma_unpopulate(&gtt->ttm, rdev->dev);
		return;
	}
#endif

	for (i = 0; i < ttm->num_pages; i++) {
		if (gtt->ttm.dma_address[i]) {
			pci_unmap_page(rdev->pdev, gtt->ttm.dma_address[i],
				       PAGE_SIZE, PCI_DMA_BIDIRECTIONAL);
		}
	}

	ttm_pool_unpopulate(ttm);
}