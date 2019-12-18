#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fw_iso_buffer {int page_count; int direction; int /*<<< orphan*/ ** pages; } ;
struct fw_card {int /*<<< orphan*/  device; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA32 ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * alloc_page (int) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** kmalloc (int,int) ; 
 int /*<<< orphan*/  page_private (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_page_private (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int fw_iso_buffer_init(struct fw_iso_buffer *buffer, struct fw_card *card,
		       int page_count, enum dma_data_direction direction)
{
	int i, j;
	dma_addr_t address;

	buffer->page_count = page_count;
	buffer->direction = direction;

	buffer->pages = kmalloc(page_count * sizeof(buffer->pages[0]),
				GFP_KERNEL);
	if (buffer->pages == NULL)
		goto out;

	for (i = 0; i < buffer->page_count; i++) {
		buffer->pages[i] = alloc_page(GFP_KERNEL | GFP_DMA32 | __GFP_ZERO);
		if (buffer->pages[i] == NULL)
			goto out_pages;

		address = dma_map_page(card->device, buffer->pages[i],
				       0, PAGE_SIZE, direction);
		if (dma_mapping_error(card->device, address)) {
			__free_page(buffer->pages[i]);
			goto out_pages;
		}
		set_page_private(buffer->pages[i], address);
	}

	return 0;

 out_pages:
	for (j = 0; j < i; j++) {
		address = page_private(buffer->pages[j]);
		dma_unmap_page(card->device, address,
			       PAGE_SIZE, direction);
		__free_page(buffer->pages[j]);
	}
	kfree(buffer->pages);
 out:
	buffer->pages = NULL;

	return -ENOMEM;
}