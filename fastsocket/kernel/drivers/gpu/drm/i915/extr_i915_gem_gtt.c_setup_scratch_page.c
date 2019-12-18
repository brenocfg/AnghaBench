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
struct TYPE_2__ {int /*<<< orphan*/  scratch_page_dma; struct page* scratch_page; } ;
struct drm_i915_private {TYPE_1__ gtt; } ;
struct drm_device {int /*<<< orphan*/  pdev; struct drm_i915_private* dev_private; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_DMA32 ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int __GFP_ZERO ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pages_uc (struct page*,int) ; 

__attribute__((used)) static int setup_scratch_page(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	struct page *page;
	dma_addr_t dma_addr;

	page = alloc_page(GFP_KERNEL | GFP_DMA32 | __GFP_ZERO);
	if (page == NULL)
		return -ENOMEM;
	get_page(page);
	set_pages_uc(page, 1);

#ifdef CONFIG_INTEL_IOMMU
	dma_addr = pci_map_page(dev->pdev, page, 0, PAGE_SIZE,
				PCI_DMA_BIDIRECTIONAL);
	if (pci_dma_mapping_error(dev->pdev, dma_addr))
		return -EINVAL;
#else
	dma_addr = page_to_phys(page);
#endif
	dev_priv->gtt.scratch_page = page;
	dev_priv->gtt.scratch_page_dma = dma_addr;

	return 0;
}