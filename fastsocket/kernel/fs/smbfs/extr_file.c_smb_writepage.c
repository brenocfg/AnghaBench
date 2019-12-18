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
struct writeback_control {int dummy; } ;
struct page {unsigned long index; struct address_space* mapping; } ;
struct inode {unsigned long i_size; } ;
struct address_space {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  page_cache_get (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int smb_writepage_sync (struct inode*,struct page*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int
smb_writepage(struct page *page, struct writeback_control *wbc)
{
	struct address_space *mapping = page->mapping;
	struct inode *inode;
	unsigned long end_index;
	unsigned offset = PAGE_CACHE_SIZE;
	int err;

	BUG_ON(!mapping);
	inode = mapping->host;
	BUG_ON(!inode);

	end_index = inode->i_size >> PAGE_CACHE_SHIFT;

	/* easy case */
	if (page->index < end_index)
		goto do_it;
	/* things got complicated... */
	offset = inode->i_size & (PAGE_CACHE_SIZE-1);
	/* OK, are we completely out? */
	if (page->index >= end_index+1 || !offset)
		return 0; /* truncated - don't care */
do_it:
	page_cache_get(page);
	err = smb_writepage_sync(inode, page, 0, offset);
	SetPageUptodate(page);
	unlock_page(page);
	page_cache_release(page);
	return err;
}