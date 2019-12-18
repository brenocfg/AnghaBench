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
struct ttm_dma_tt {scalar_t__* dma_address; } ;
struct TYPE_2__ {scalar_t__ stat; } ;
struct nouveau_drm {TYPE_1__ agp; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ ENABLED ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int TTM_PAGE_FLAG_SG ; 
 int /*<<< orphan*/  drm_prime_sg_to_page_addr_arrays (scalar_t__,int /*<<< orphan*/ *,scalar_t__*,unsigned int) ; 
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pci_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ swiotlb_nr_tbl () ; 
 scalar_t__ tt_unbound ; 
 scalar_t__ tt_unpopulated ; 
 int ttm_agp_tt_populate (struct ttm_tt*) ; 
 int ttm_dma_populate (void*,int /*<<< orphan*/ ) ; 
 int ttm_pool_populate (struct ttm_tt*) ; 
 int /*<<< orphan*/  ttm_pool_unpopulate (struct ttm_tt*) ; 

__attribute__((used)) static int
nouveau_ttm_tt_populate(struct ttm_tt *ttm)
{
	struct ttm_dma_tt *ttm_dma = (void *)ttm;
	struct nouveau_drm *drm;
	struct drm_device *dev;
	unsigned i;
	int r;
	bool slave = !!(ttm->page_flags & TTM_PAGE_FLAG_SG);

	if (ttm->state != tt_unpopulated)
		return 0;

	if (slave && ttm->sg) {
		/* make userspace faulting work */
		drm_prime_sg_to_page_addr_arrays(ttm->sg, ttm->pages,
						 ttm_dma->dma_address, ttm->num_pages);
		ttm->state = tt_unbound;
		return 0;
	}

	drm = nouveau_bdev(ttm->bdev);
	dev = drm->dev;

#if __OS_HAS_AGP
	if (drm->agp.stat == ENABLED) {
		return ttm_agp_tt_populate(ttm);
	}
#endif

#ifdef CONFIG_SWIOTLB
	if (swiotlb_nr_tbl()) {
		return ttm_dma_populate((void *)ttm, dev->dev);
	}
#endif

	r = ttm_pool_populate(ttm);
	if (r) {
		return r;
	}

	for (i = 0; i < ttm->num_pages; i++) {
		ttm_dma->dma_address[i] = pci_map_page(dev->pdev, ttm->pages[i],
						   0, PAGE_SIZE,
						   PCI_DMA_BIDIRECTIONAL);
		if (pci_dma_mapping_error(dev->pdev, ttm_dma->dma_address[i])) {
			while (--i) {
				pci_unmap_page(dev->pdev, ttm_dma->dma_address[i],
					       PAGE_SIZE, PCI_DMA_BIDIRECTIONAL);
				ttm_dma->dma_address[i] = 0;
			}
			ttm_pool_unpopulate(ttm);
			return -EFAULT;
		}
	}
	return 0;
}