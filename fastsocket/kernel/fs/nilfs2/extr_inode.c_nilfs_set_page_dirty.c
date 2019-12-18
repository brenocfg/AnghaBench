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
struct nilfs_sb_info {int dummy; } ;
struct inode {int i_blkbits; int /*<<< orphan*/  i_sb; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 struct nilfs_sb_info* NILFS_SB (int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int __set_page_dirty_buffers (struct page*) ; 
 int /*<<< orphan*/  nilfs_set_file_dirty (struct nilfs_sb_info*,struct inode*,unsigned int) ; 

__attribute__((used)) static int nilfs_set_page_dirty(struct page *page)
{
	int ret = __set_page_dirty_buffers(page);

	if (ret) {
		struct inode *inode = page->mapping->host;
		struct nilfs_sb_info *sbi = NILFS_SB(inode->i_sb);
		unsigned nr_dirty = 1 << (PAGE_SHIFT - inode->i_blkbits);

		nilfs_set_file_dirty(sbi, inode, nr_dirty);
	}
	return ret;
}