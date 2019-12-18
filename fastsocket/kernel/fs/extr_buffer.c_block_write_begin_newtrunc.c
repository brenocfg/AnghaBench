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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  get_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int ENOMEM ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int __block_prepare_write (struct inode*,struct page*,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,int,unsigned int) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int block_write_begin_newtrunc(struct file *file, struct address_space *mapping,
			loff_t pos, unsigned len, unsigned flags,
			struct page **pagep, void **fsdata,
			get_block_t *get_block)
{
	struct inode *inode = mapping->host;
	int status = 0;
	struct page *page;
	pgoff_t index;
	unsigned start, end;
	int ownpage = 0;

	index = pos >> PAGE_CACHE_SHIFT;
	start = pos & (PAGE_CACHE_SIZE - 1);
	end = start + len;

	page = *pagep;
	if (page == NULL) {
		ownpage = 1;
		page = grab_cache_page_write_begin(mapping, index, flags);
		if (!page) {
			status = -ENOMEM;
			goto out;
		}
		*pagep = page;
	} else
		BUG_ON(!PageLocked(page));

	status = __block_prepare_write(inode, page, start, end, get_block);
	if (unlikely(status)) {
		ClearPageUptodate(page);

		if (ownpage) {
			unlock_page(page);
			page_cache_release(page);
			*pagep = NULL;
		}
	}

out:
	return status;
}