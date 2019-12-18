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
struct swsusp_info {int dummy; } ;
struct snapshot_handle {scalar_t__ cur; scalar_t__ prev; scalar_t__ buf_offset; scalar_t__ cur_offset; scalar_t__ offset; void* buffer; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  KM_USER0 ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PG_ANY ; 
 scalar_t__ PageHighMem (struct page*) ; 
 void* buffer ; 
 int /*<<< orphan*/  copy_bm ; 
 void* get_image_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int init_header (struct swsusp_info*) ; 
 void* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  memory_bm_next_pfn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memory_bm_position_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nr_copy_pages ; 
 scalar_t__ nr_meta_pages ; 
 int /*<<< orphan*/  orig_bm ; 
 int /*<<< orphan*/  pack_pfns (void*,int /*<<< orphan*/ *) ; 
 void* page_address (struct page*) ; 
 struct page* pfn_to_page (int /*<<< orphan*/ ) ; 

int snapshot_read_next(struct snapshot_handle *handle, size_t count)
{
	if (handle->cur > nr_meta_pages + nr_copy_pages)
		return 0;

	if (!buffer) {
		/* This makes the buffer be freed by swsusp_free() */
		buffer = get_image_page(GFP_ATOMIC, PG_ANY);
		if (!buffer)
			return -ENOMEM;
	}
	if (!handle->offset) {
		int error;

		error = init_header((struct swsusp_info *)buffer);
		if (error)
			return error;
		handle->buffer = buffer;
		memory_bm_position_reset(&orig_bm);
		memory_bm_position_reset(&copy_bm);
	}
	if (handle->prev < handle->cur) {
		if (handle->cur <= nr_meta_pages) {
			memset(buffer, 0, PAGE_SIZE);
			pack_pfns(buffer, &orig_bm);
		} else {
			struct page *page;

			page = pfn_to_page(memory_bm_next_pfn(&copy_bm));
			if (PageHighMem(page)) {
				/* Highmem pages are copied to the buffer,
				 * because we can't return with a kmapped
				 * highmem page (we may not be called again).
				 */
				void *kaddr;

				kaddr = kmap_atomic(page, KM_USER0);
				memcpy(buffer, kaddr, PAGE_SIZE);
				kunmap_atomic(kaddr, KM_USER0);
				handle->buffer = buffer;
			} else {
				handle->buffer = page_address(page);
			}
		}
		handle->prev = handle->cur;
	}
	handle->buf_offset = handle->cur_offset;
	if (handle->cur_offset + count >= PAGE_SIZE) {
		count = PAGE_SIZE - handle->cur_offset;
		handle->cur_offset = 0;
		handle->cur++;
	} else {
		handle->cur_offset += count;
	}
	handle->offset += count;
	return count;
}