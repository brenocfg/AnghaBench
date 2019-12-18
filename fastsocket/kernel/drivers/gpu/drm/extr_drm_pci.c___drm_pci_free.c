#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_device {TYPE_1__* pdev; } ;
struct TYPE_5__ {size_t size; int /*<<< orphan*/  busaddr; scalar_t__ vaddr; } ;
typedef  TYPE_2__ drm_dma_handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageReserved (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (unsigned long) ; 

void __drm_pci_free(struct drm_device * dev, drm_dma_handle_t * dmah)
{
#if 1
	unsigned long addr;
	size_t sz;
#endif

	if (dmah->vaddr) {
		/* XXX - Is virt_to_page() legal for consistent mem? */
		/* Unreserve */
		for (addr = (unsigned long)dmah->vaddr, sz = dmah->size;
		     sz > 0; addr += PAGE_SIZE, sz -= PAGE_SIZE) {
			ClearPageReserved(virt_to_page(addr));
		}
		dma_free_coherent(&dev->pdev->dev, dmah->size, dmah->vaddr,
				  dmah->busaddr);
	}
}