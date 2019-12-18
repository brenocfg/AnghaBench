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
struct inode {int i_blkbits; } ;
struct buffer_head {int dummy; } ;
struct address_space {int /*<<< orphan*/ * assoc_mapping; } ;
typedef  unsigned long pgoff_t ;

/* Variables and functions */
 scalar_t__ NILFS_MDT (struct inode*) ; 
 int PAGE_CACHE_SHIFT ; 
 struct buffer_head* __nilfs_get_page_block (struct page*,unsigned long,unsigned long,int,unsigned long) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_nilfs_node (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 struct page* find_lock_page (int /*<<< orphan*/ *,unsigned long) ; 
 struct page* grab_cache_page (struct address_space*,unsigned long) ; 
 int /*<<< orphan*/  nilfs_copy_buffer (struct buffer_head*,struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (struct inode*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

struct buffer_head *nilfs_grab_buffer(struct inode *inode,
				      struct address_space *mapping,
				      unsigned long blkoff,
				      unsigned long b_state)
{
	int blkbits = inode->i_blkbits;
	pgoff_t index = blkoff >> (PAGE_CACHE_SHIFT - blkbits);
	struct page *page, *opage;
	struct buffer_head *bh, *obh;

	page = grab_cache_page(mapping, index);
	if (unlikely(!page))
		return NULL;

	bh = __nilfs_get_page_block(page, blkoff, index, blkbits, b_state);
	if (unlikely(!bh)) {
		unlock_page(page);
		page_cache_release(page);
		return NULL;
	}
	if (!buffer_uptodate(bh) && mapping->assoc_mapping != NULL) {
		/*
		 * Shadow page cache uses assoc_mapping to point its original
		 * page cache.  The following code tries the original cache
		 * if the given cache is a shadow and it didn't hit.
		 */
		opage = find_lock_page(mapping->assoc_mapping, index);
		if (!opage)
			return bh;

		obh = __nilfs_get_page_block(opage, blkoff, index, blkbits,
					     b_state);
		if (buffer_uptodate(obh)) {
			nilfs_copy_buffer(bh, obh);
			if (buffer_dirty(obh)) {
				nilfs_mark_buffer_dirty(bh);
				if (!buffer_nilfs_node(bh) && NILFS_MDT(inode))
					nilfs_mdt_mark_dirty(inode);
			}
		}
		brelse(obh);
		unlock_page(opage);
		page_cache_release(opage);
	}
	return bh;
}