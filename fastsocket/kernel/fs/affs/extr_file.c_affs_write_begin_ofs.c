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
typedef  int /*<<< orphan*/  u32 ;
struct page {int dummy; } ;
struct inode {scalar_t__ i_ino; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ pgoff_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {scalar_t__ mmu_private; } ;

/* Variables and functions */
 TYPE_1__* AFFS_I (struct inode*) ; 
 int ENOMEM ; 
 scalar_t__ PAGE_CACHE_SHIFT ; 
 int /*<<< orphan*/  PAGE_CACHE_SIZE ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int affs_do_readpage_ofs (struct file*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int affs_extent_file_ofs (struct inode*,scalar_t__) ; 
 struct page* grab_cache_page_write_begin (struct address_space*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned long long,unsigned int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int affs_write_begin_ofs(struct file *file, struct address_space *mapping,
				loff_t pos, unsigned len, unsigned flags,
				struct page **pagep, void **fsdata)
{
	struct inode *inode = mapping->host;
	struct page *page;
	pgoff_t index;
	int err = 0;

	pr_debug("AFFS: write_begin(%u, %llu, %llu)\n", (u32)inode->i_ino, (unsigned long long)pos, (unsigned long long)pos + len);
	if (pos > AFFS_I(inode)->mmu_private) {
		/* XXX: this probably leaves a too-big i_size in case of
		 * failure. Should really be updating i_size at write_end time
		 */
		err = affs_extent_file_ofs(inode, pos);
		if (err)
			return err;
	}

	index = pos >> PAGE_CACHE_SHIFT;
	page = grab_cache_page_write_begin(mapping, index, flags);
	if (!page)
		return -ENOMEM;
	*pagep = page;

	if (PageUptodate(page))
		return 0;

	/* XXX: inefficient but safe in the face of short writes */
	err = affs_do_readpage_ofs(file, page, 0, PAGE_CACHE_SIZE);
	if (err) {
		unlock_page(page);
		page_cache_release(page);
	}
	return err;
}