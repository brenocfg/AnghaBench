#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
typedef  unsigned long loff_t ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 unsigned long EINVAL ; 
 unsigned long ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long MAP_SHARED ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 unsigned long find_get_pages (int /*<<< orphan*/ ,unsigned long,unsigned long,struct page**) ; 
 unsigned long i_size_read (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 struct page** kzalloc (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ page_address (struct page*) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

unsigned long ramfs_nommu_get_unmapped_area(struct file *file,
					    unsigned long addr, unsigned long len,
					    unsigned long pgoff, unsigned long flags)
{
	unsigned long maxpages, lpages, nr, loop, ret;
	struct inode *inode = file->f_path.dentry->d_inode;
	struct page **pages = NULL, **ptr, *page;
	loff_t isize;

	if (!(flags & MAP_SHARED))
		return addr;

	/* the mapping mustn't extend beyond the EOF */
	lpages = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	isize = i_size_read(inode);

	ret = -EINVAL;
	maxpages = (isize + PAGE_SIZE - 1) >> PAGE_SHIFT;
	if (pgoff >= maxpages)
		goto out;

	if (maxpages - pgoff < lpages)
		goto out;

	/* gang-find the pages */
	ret = -ENOMEM;
	pages = kzalloc(lpages * sizeof(struct page *), GFP_KERNEL);
	if (!pages)
		goto out_free;

	nr = find_get_pages(inode->i_mapping, pgoff, lpages, pages);
	if (nr != lpages)
		goto out_free_pages; /* leave if some pages were missing */

	/* check the pages for physical adjacency */
	ptr = pages;
	page = *ptr++;
	page++;
	for (loop = lpages; loop > 1; loop--)
		if (*ptr++ != page++)
			goto out_free_pages;

	/* okay - all conditions fulfilled */
	ret = (unsigned long) page_address(pages[0]);

out_free_pages:
	ptr = pages;
	for (loop = nr; loop > 0; loop--)
		put_page(*ptr++);
out_free:
	kfree(pages);
out:
	return ret;
}