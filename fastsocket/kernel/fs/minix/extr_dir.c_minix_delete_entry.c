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
struct page {struct address_space* mapping; } ;
struct minix_sb_info {unsigned int s_dirsize; scalar_t__ s_version; } ;
struct minix_dir_entry {scalar_t__ inode; } ;
struct inode {int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_sb; } ;
struct address_space {scalar_t__ host; } ;
struct TYPE_2__ {scalar_t__ inode; } ;
typedef  TYPE_1__ minix3_dirent ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOP_FLAG_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 scalar_t__ MINIX_V3 ; 
 int __minix_write_begin (int /*<<< orphan*/ *,struct address_space*,int,unsigned int,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *) ; 
 int dir_commit_chunk (struct page*,int,unsigned int) ; 
 int /*<<< orphan*/  dir_put_page (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 struct minix_sb_info* minix_sb (int /*<<< orphan*/ ) ; 
 char* page_address (struct page*) ; 
 int page_offset (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int minix_delete_entry(struct minix_dir_entry *de, struct page *page)
{
	struct address_space *mapping = page->mapping;
	struct inode *inode = (struct inode*)mapping->host;
	char *kaddr = page_address(page);
	loff_t pos = page_offset(page) + (char*)de - kaddr;
	struct minix_sb_info *sbi = minix_sb(inode->i_sb);
	unsigned len = sbi->s_dirsize;
	int err;

	lock_page(page);
	err = __minix_write_begin(NULL, mapping, pos, len,
					AOP_FLAG_UNINTERRUPTIBLE, &page, NULL);
	if (err == 0) {
		if (sbi->s_version == MINIX_V3)
			((minix3_dirent *) de)->inode = 0;
		else
			de->inode = 0;
		err = dir_commit_chunk(page, pos, len);
	} else {
		unlock_page(page);
	}
	dir_put_page(page);
	inode->i_ctime = inode->i_mtime = CURRENT_TIME_SEC;
	mark_inode_dirty(inode);
	return err;
}