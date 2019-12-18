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
struct ttm_dma_tt {scalar_t__* dma_address; } ;
struct TYPE_2__ {scalar_t__ stat; } ;
struct nouveau_drm {TYPE_1__ agp; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ENABLED ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int TTM_PAGE_FLAG_SG ; 
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ swiotlb_nr_tbl () ; 
 int /*<<< orphan*/  ttm_agp_tt_unpopulate (struct ttm_tt*) ; 
 int /*<<< orphan*/  ttm_dma_unpopulate (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_pool_unpopulate (struct ttm_tt*) ; 

__attribute__((used)) static void
nouveau_ttm_tt_unpopulate(struct ttm_tt *ttm)
{
	struct ttm_dma_tt *ttm_dma = (void *)ttm;
	struct nouveau_drm *drm;
	struct drm_device *dev;
	unsigned i;
	bool slave = !!(ttm->page_flags & TTM_PAGE_FLAG_SG);

	if (slave)
		return;

	drm = nouveau_bdev(ttm->bdev);
	dev = drm->dev;

#if __OS_HAS_AGP
	if (drm->agp.stat == ENABLED) {
		ttm_agp_tt_unpopulate(ttm);
		return;
	}
#endif

#ifdef CONFIG_SWIOTLB
	if (swiotlb_nr_tbl()) {
		ttm_dma_unpopulate((void *)ttm, dev->dev);
		return;
	}
#endif

	for (i = 0; i < ttm->num_pages; i++) {
		if (ttm_dma->dma_address[i]) {
			pci_unmap_page(dev->pdev, ttm_dma->dma_address[i],
				       PAGE_SIZE, PCI_DMA_BIDIRECTIONAL);
		}
	}

	ttm_pool_unpopulate(ttm);
}