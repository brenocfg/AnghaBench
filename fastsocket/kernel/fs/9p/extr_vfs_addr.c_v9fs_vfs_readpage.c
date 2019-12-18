#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  page_offset (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int v9fs_file_readn (struct file*,char*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int v9fs_readpage_from_fscache (struct inode*,struct page*) ; 
 int /*<<< orphan*/  v9fs_readpage_to_fscache (struct inode*,struct page*) ; 
 int /*<<< orphan*/  v9fs_uncache_page (struct inode*,struct page*) ; 

__attribute__((used)) static int v9fs_vfs_readpage(struct file *filp, struct page *page)
{
	int retval;
	loff_t offset;
	char *buffer;
	struct inode *inode;

	inode = page->mapping->host;
	P9_DPRINTK(P9_DEBUG_VFS, "\n");

	BUG_ON(!PageLocked(page));

	retval = v9fs_readpage_from_fscache(inode, page);
	if (retval == 0)
		return retval;

	buffer = kmap(page);
	offset = page_offset(page);

	retval = v9fs_file_readn(filp, buffer, NULL, PAGE_CACHE_SIZE, offset);
	if (retval < 0) {
		v9fs_uncache_page(inode, page);
		goto done;
	}

	memset(buffer + retval, 0, PAGE_CACHE_SIZE - retval);
	flush_dcache_page(page);
	SetPageUptodate(page);

	v9fs_readpage_to_fscache(inode, page);
	retval = 0;

done:
	kunmap(page);
	unlock_page(page);
	return retval;
}