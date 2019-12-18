#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_4__ {int state; int num_desc_pages; int num_pages; scalar_t__ free_on_sequence; struct page** bounce_buffer; struct page** pages; int /*<<< orphan*/  direction; int /*<<< orphan*/ ** desc_pages; } ;
typedef  TYPE_1__ drm_via_sg_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  PageReserved (struct page*) ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
#define  dr_via_desc_pages_alloc 131 
#define  dr_via_device_mapped 130 
#define  dr_via_pages_alloc 129 
#define  dr_via_pages_locked 128 
 int dr_via_sg_init ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  vfree (struct page**) ; 
 int /*<<< orphan*/  via_unmap_blit_from_device (struct pci_dev*,TYPE_1__*) ; 

__attribute__((used)) static void
via_free_sg_info(struct pci_dev *pdev, drm_via_sg_info_t *vsg)
{
	struct page *page;
	int i;

	switch (vsg->state) {
	case dr_via_device_mapped:
		via_unmap_blit_from_device(pdev, vsg);
	case dr_via_desc_pages_alloc:
		for (i = 0; i < vsg->num_desc_pages; ++i) {
			if (vsg->desc_pages[i] != NULL)
				free_page((unsigned long)vsg->desc_pages[i]);
		}
		kfree(vsg->desc_pages);
	case dr_via_pages_locked:
		for (i = 0; i < vsg->num_pages; ++i) {
			if (NULL != (page = vsg->pages[i])) {
				if (!PageReserved(page) && (DMA_FROM_DEVICE == vsg->direction))
					SetPageDirty(page);
				page_cache_release(page);
			}
		}
	case dr_via_pages_alloc:
		vfree(vsg->pages);
	default:
		vsg->state = dr_via_sg_init;
	}
	vfree(vsg->bounce_buffer);
	vsg->bounce_buffer = NULL;
	vsg->free_on_sequence = 0;
}