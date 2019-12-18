#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_12__ {TYPE_4__* dentry; } ;
struct file {TYPE_5__ f_path; } ;
struct address_space {TYPE_7__* host; } ;
typedef  int pgoff_t ;
typedef  int loff_t ;
struct TYPE_14__ {int /*<<< orphan*/  i_ino; } ;
struct TYPE_13__ {int /*<<< orphan*/  flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {TYPE_3__ d_name; TYPE_2__* d_parent; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {TYPE_1__ d_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_6__* NFS_I (TYPE_7__*) ; 
 int /*<<< orphan*/  NFS_INO_FLUSHING ; 
 int /*<<< orphan*/  PAGECACHE ; 
 int PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,long long) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,int,unsigned int) ; 
 int nfs_flush_incompatible (struct file*,struct page*) ; 
 int nfs_readpage (struct file*,struct page*) ; 
 int /*<<< orphan*/  nfs_wait_bit_killable ; 
 scalar_t__ nfs_want_read_modify_write (struct file*,struct page*,int,unsigned int) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs_write_begin(struct file *file, struct address_space *mapping,
			loff_t pos, unsigned len, unsigned flags,
			struct page **pagep, void **fsdata)
{
	int ret;
	pgoff_t index = pos >> PAGE_CACHE_SHIFT;
	struct page *page;
	int once_thru = 0;

	dfprintk(PAGECACHE, "NFS: write_begin(%s/%s(%ld), %u@%lld)\n",
		file->f_path.dentry->d_parent->d_name.name,
		file->f_path.dentry->d_name.name,
		mapping->host->i_ino, len, (long long) pos);

start:
	/*
	 * Prevent starvation issues if someone is doing a consistency
	 * sync-to-disk
	 */
	ret = wait_on_bit(&NFS_I(mapping->host)->flags, NFS_INO_FLUSHING,
			nfs_wait_bit_killable, TASK_KILLABLE);
	if (ret)
		return ret;

	page = grab_cache_page_write_begin(mapping, index, flags);
	if (!page)
		return -ENOMEM;
	*pagep = page;

	ret = nfs_flush_incompatible(file, page);
	if (ret) {
		unlock_page(page);
		page_cache_release(page);
	} else if (!once_thru &&
		   nfs_want_read_modify_write(file, page, pos, len)) {
		once_thru = 1;
		ret = nfs_readpage(file, page);
		page_cache_release(page);
		if (!ret)
			goto start;
	}
	return ret;
}