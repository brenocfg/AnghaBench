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
struct ufs_dir_entry {int /*<<< orphan*/  d_ino; int /*<<< orphan*/  d_reclen; } ;
struct page {int /*<<< orphan*/  mapping; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOP_FLAG_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int __ufs_write_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_fs32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int fs16_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 scalar_t__ page_address (struct page*) ; 
 int page_offset (struct page*) ; 
 int ufs_commit_chunk (struct page*,int,unsigned int) ; 
 int /*<<< orphan*/  ufs_put_page (struct page*) ; 
 int /*<<< orphan*/  ufs_set_de_type (int /*<<< orphan*/ ,struct ufs_dir_entry*,int /*<<< orphan*/ ) ; 

void ufs_set_link(struct inode *dir, struct ufs_dir_entry *de,
		  struct page *page, struct inode *inode)
{
	loff_t pos = page_offset(page) +
			(char *) de - (char *) page_address(page);
	unsigned len = fs16_to_cpu(dir->i_sb, de->d_reclen);
	int err;

	lock_page(page);
	err = __ufs_write_begin(NULL, page->mapping, pos, len,
				AOP_FLAG_UNINTERRUPTIBLE, &page, NULL);
	BUG_ON(err);

	de->d_ino = cpu_to_fs32(dir->i_sb, inode->i_ino);
	ufs_set_de_type(dir->i_sb, de, inode->i_mode);

	err = ufs_commit_chunk(page, pos, len);
	ufs_put_page(page);
	dir->i_mtime = dir->i_ctime = CURRENT_TIME_SEC;
	mark_inode_dirty(dir);
}