#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_device {TYPE_1__* pdev; } ;
struct TYPE_7__ {size_t size; int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  busaddr; } ;
typedef  TYPE_2__ drm_dma_handle_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageReserved (int /*<<< orphan*/ ) ; 
 int __GFP_COMP ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kmalloc (int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  virt_to_page (unsigned long) ; 

drm_dma_handle_t *drm_pci_alloc(struct drm_device * dev, size_t size, size_t align)
{
	drm_dma_handle_t *dmah;
#if 1
	unsigned long addr;
	size_t sz;
#endif

	/* pci_alloc_consistent only guarantees alignment to the smallest
	 * PAGE_SIZE order which is greater than or equal to the requested size.
	 * Return NULL here for now to make sure nobody tries for larger alignment
	 */
	if (align > size)
		return NULL;

	dmah = kmalloc(sizeof(drm_dma_handle_t), GFP_KERNEL);
	if (!dmah)
		return NULL;

	dmah->size = size;
	dmah->vaddr = dma_alloc_coherent(&dev->pdev->dev, size, &dmah->busaddr, GFP_KERNEL | __GFP_COMP);

	if (dmah->vaddr == NULL) {
		kfree(dmah);
		return NULL;
	}

	memset(dmah->vaddr, 0, size);

	/* XXX - Is virt_to_page() legal for consistent mem? */
	/* Reserve */
	for (addr = (unsigned long)dmah->vaddr, sz = size;
	     sz > 0; addr += PAGE_SIZE, sz -= PAGE_SIZE) {
		SetPageReserved(virt_to_page(addr));
	}

	return dmah;
}