#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct inode {TYPE_1__* i_mapping; } ;
struct buffer_head {int b_size; } ;
struct block_device {struct inode* bd_inode; } ;
typedef  scalar_t__ sector_t ;
typedef  int pgoff_t ;
struct TYPE_3__ {int /*<<< orphan*/  private_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int __GFP_FS ; 
 int __GFP_MOVABLE ; 
 struct buffer_head* alloc_page_buffers (struct page*,int,int /*<<< orphan*/ ) ; 
 struct page* find_or_create_page (TYPE_1__*,int,int) ; 
 scalar_t__ init_page_buffers (struct page*,struct block_device*,int,int) ; 
 int /*<<< orphan*/  link_dev_buffers (struct page*,struct buffer_head*) ; 
 int mapping_gfp_mask (TYPE_1__*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 scalar_t__ page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_to_free_buffers (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int
grow_dev_page(struct block_device *bdev, sector_t block,
		pgoff_t index, int size, int sizebits)
{
	struct inode *inode = bdev->bd_inode;
	struct page *page;
	struct buffer_head *bh;
	sector_t end_block;
	int ret = 0;		/* Will call free_more_memory() */

	page = find_or_create_page(inode->i_mapping, index,
		(mapping_gfp_mask(inode->i_mapping) & ~__GFP_FS)|__GFP_MOVABLE);
	if (!page)
		return ret;

	BUG_ON(!PageLocked(page));

	if (page_has_buffers(page)) {
		bh = page_buffers(page);
		if (bh->b_size == size) {
			end_block = init_page_buffers(page, bdev,
						index << sizebits, size);
			goto done;
		}
		if (!try_to_free_buffers(page))
			goto failed;
	}

	/*
	 * Allocate some buffers for this page
	 */
	bh = alloc_page_buffers(page, size, 0);
	if (!bh)
		goto failed;

	/*
	 * Link the page to the buffers and initialise them.  Take the
	 * lock to be atomic wrt __find_get_block(), which does not
	 * run under the page lock.
	 */
	spin_lock(&inode->i_mapping->private_lock);
	link_dev_buffers(page, bh);
	end_block = init_page_buffers(page, bdev, index << sizebits, size);
	spin_unlock(&inode->i_mapping->private_lock);
done:
	ret = (block < end_block) ? 1 : -ENXIO;
failed:
	unlock_page(page);
	page_cache_release(page);
	return ret;
}