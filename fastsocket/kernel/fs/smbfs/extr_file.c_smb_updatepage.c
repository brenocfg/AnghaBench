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
struct page {scalar_t__ index; } ;
struct TYPE_2__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG1 (char*,int /*<<< orphan*/ ,unsigned int,unsigned long long) ; 
 int /*<<< orphan*/  DENTRY_PATH (struct dentry*) ; 
 unsigned long long PAGE_CACHE_SHIFT ; 
 int smb_writepage_sync (int /*<<< orphan*/ ,struct page*,unsigned long,unsigned int) ; 

__attribute__((used)) static int
smb_updatepage(struct file *file, struct page *page, unsigned long offset,
	       unsigned int count)
{
	struct dentry *dentry = file->f_path.dentry;

	DEBUG1("(%s/%s %d@%lld)\n", DENTRY_PATH(dentry), count,
		((unsigned long long)page->index << PAGE_CACHE_SHIFT) + offset);

	return smb_writepage_sync(dentry->d_inode, page, offset, count);
}