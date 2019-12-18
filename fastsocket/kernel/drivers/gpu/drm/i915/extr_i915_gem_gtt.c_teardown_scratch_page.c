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
struct TYPE_2__ {int /*<<< orphan*/  scratch_page; int /*<<< orphan*/  scratch_page_dma; } ;
struct drm_i915_private {TYPE_1__ gtt; } ;
struct drm_device {int /*<<< orphan*/  pdev; struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pages_wb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void teardown_scratch_page(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = dev->dev_private;
	set_pages_wb(dev_priv->gtt.scratch_page, 1);
	pci_unmap_page(dev->pdev, dev_priv->gtt.scratch_page_dma,
		       PAGE_SIZE, PCI_DMA_BIDIRECTIONAL);
	put_page(dev_priv->gtt.scratch_page);
	__free_page(dev_priv->gtt.scratch_page);
}