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
struct file {int dummy; } ;
struct address_space {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int smb_updatepage (struct file*,struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int smb_write_end(struct file *file, struct address_space *mapping,
			loff_t pos, unsigned len, unsigned copied,
			struct page *page, void *fsdata)
{
	int status;
	unsigned offset = pos & (PAGE_CACHE_SIZE - 1);

	lock_kernel();
	status = smb_updatepage(file, page, offset, copied);
	unlock_kernel();

	if (!status) {
		if (!PageUptodate(page) && copied == PAGE_CACHE_SIZE)
			SetPageUptodate(page);
		status = copied;
	}

	unlock_page(page);
	page_cache_release(page);

	return status;
}