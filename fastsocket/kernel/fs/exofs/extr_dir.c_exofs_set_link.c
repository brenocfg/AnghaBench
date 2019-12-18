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
struct page {int /*<<< orphan*/  mapping; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ino; } ;
struct exofs_dir_entry {int /*<<< orphan*/  inode_no; int /*<<< orphan*/  rec_len; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOP_FLAG_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  CURRENT_TIME ; 
 int /*<<< orphan*/  EXOFS_ERR (char*,int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int exofs_commit_chunk (struct page*,int,unsigned int) ; 
 int /*<<< orphan*/  exofs_put_page (struct page*) ; 
 int /*<<< orphan*/  exofs_set_de_type (struct exofs_dir_entry*,struct inode*) ; 
 int exofs_write_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 scalar_t__ page_address (struct page*) ; 
 int page_offset (struct page*) ; 

int exofs_set_link(struct inode *dir, struct exofs_dir_entry *de,
			struct page *page, struct inode *inode)
{
	loff_t pos = page_offset(page) +
			(char *) de - (char *) page_address(page);
	unsigned len = le16_to_cpu(de->rec_len);
	int err;

	lock_page(page);
	err = exofs_write_begin(NULL, page->mapping, pos, len,
				AOP_FLAG_UNINTERRUPTIBLE, &page, NULL);
	if (err)
		EXOFS_ERR("exofs_set_link: exofs_write_begin FAILD => %d\n",
			  err);

	de->inode_no = cpu_to_le64(inode->i_ino);
	exofs_set_de_type(de, inode);
	if (likely(!err))
		err = exofs_commit_chunk(page, pos, len);
	exofs_put_page(page);
	dir->i_mtime = dir->i_ctime = CURRENT_TIME;
	mark_inode_dirty(dir);
	return err;
}