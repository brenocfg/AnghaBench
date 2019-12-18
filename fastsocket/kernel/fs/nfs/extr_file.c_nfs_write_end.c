#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_11__ {TYPE_4__* dentry; } ;
struct file {TYPE_5__ f_path; } ;
struct address_space {TYPE_6__* host; } ;
typedef  int loff_t ;
struct TYPE_12__ {int /*<<< orphan*/  i_ino; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {TYPE_3__ d_name; TYPE_2__* d_parent; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGECACHE ; 
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,long long) ; 
 unsigned int nfs_page_length (struct page*) ; 
 int nfs_updatepage (struct file*,struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,unsigned int,int) ; 
 int /*<<< orphan*/  zero_user_segments (struct page*,int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 

__attribute__((used)) static int nfs_write_end(struct file *file, struct address_space *mapping,
			loff_t pos, unsigned len, unsigned copied,
			struct page *page, void *fsdata)
{
	unsigned offset = pos & (PAGE_CACHE_SIZE - 1);
	int status;

	dfprintk(PAGECACHE, "NFS: write_end(%s/%s(%ld), %u@%lld)\n",
		file->f_path.dentry->d_parent->d_name.name,
		file->f_path.dentry->d_name.name,
		mapping->host->i_ino, len, (long long) pos);

	/*
	 * Zero any uninitialised parts of the page, and then mark the page
	 * as up to date if it turns out that we're extending the file.
	 */
	if (!PageUptodate(page)) {
		unsigned pglen = nfs_page_length(page);
		unsigned end = offset + len;

		if (pglen == 0) {
			zero_user_segments(page, 0, offset,
					end, PAGE_CACHE_SIZE);
			SetPageUptodate(page);
		} else if (end >= pglen) {
			zero_user_segment(page, end, PAGE_CACHE_SIZE);
			if (offset == 0)
				SetPageUptodate(page);
		} else
			zero_user_segment(page, pglen, PAGE_CACHE_SIZE);
	}

	status = nfs_updatepage(file, page, offset, copied);

	unlock_page(page);
	page_cache_release(page);

	if (status < 0)
		return status;
	return copied;
}