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
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int EFBIG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int MAX_ORDER ; 
 size_t PAGE_SHIFT ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int add_to_page_cache_lru (struct page*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int get_order (size_t) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,size_t) ; 
 int inode_newsize_ok (struct inode*,size_t) ; 
 int /*<<< orphan*/  mapping_gfp_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 void* page_address (struct page*) ; 
 int /*<<< orphan*/  split_page (struct page*,unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int ramfs_nommu_expand_for_mapping(struct inode *inode, size_t newsize)
{
	unsigned long npages, xpages, loop, limit;
	struct page *pages;
	unsigned order;
	void *data;
	int ret;

	/* make various checks */
	order = get_order(newsize);
	if (unlikely(order >= MAX_ORDER))
		return -EFBIG;

	ret = inode_newsize_ok(inode, newsize);
	if (ret)
		return ret;

	i_size_write(inode, newsize);

	/* allocate enough contiguous pages to be able to satisfy the
	 * request */
	pages = alloc_pages(mapping_gfp_mask(inode->i_mapping), order);
	if (!pages)
		return -ENOMEM;

	/* split the high-order page into an array of single pages */
	xpages = 1UL << order;
	npages = (newsize + PAGE_SIZE - 1) >> PAGE_SHIFT;

	split_page(pages, order);

	/* trim off any pages we don't actually require */
	for (loop = npages; loop < xpages; loop++)
		__free_page(pages + loop);

	/* clear the memory we allocated */
	newsize = PAGE_SIZE * npages;
	data = page_address(pages);
	memset(data, 0, newsize);

	/* attach all the pages to the inode's address space */
	for (loop = 0; loop < npages; loop++) {
		struct page *page = pages + loop;

		ret = add_to_page_cache_lru(page, inode->i_mapping, loop,
					GFP_KERNEL);
		if (ret < 0)
			goto add_error;

		/* prevent the page from being discarded on memory pressure */
		SetPageDirty(page);

		unlock_page(page);
	}

	return 0;

add_error:
	while (loop < npages)
		__free_page(pages + loop++);
	return ret;
}