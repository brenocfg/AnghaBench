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
struct inode {int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; TYPE_1__* i_sb; } ;
struct exofs_sb_info {int /*<<< orphan*/  s_numfiles; } ;
struct exofs_dir_entry {scalar_t__ rec_len; scalar_t__ inode_no; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {struct exofs_sb_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int EIO ; 
 int /*<<< orphan*/  EXOFS_ERR (char*,...) ; 
 scalar_t__ cpu_to_le16 (unsigned int) ; 
 int exofs_chunk_size (struct inode*) ; 
 int exofs_commit_chunk (struct page*,scalar_t__,unsigned int) ; 
 struct exofs_dir_entry* exofs_next_entry (struct exofs_dir_entry*) ; 
 int /*<<< orphan*/  exofs_put_page (struct page*) ; 
 int exofs_write_begin (int /*<<< orphan*/ *,struct address_space*,scalar_t__,unsigned int,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *) ; 
 int le16_to_cpu (scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 char* page_address (struct page*) ; 
 scalar_t__ page_offset (struct page*) ; 

int exofs_delete_entry(struct exofs_dir_entry *dir, struct page *page)
{
	struct address_space *mapping = page->mapping;
	struct inode *inode = mapping->host;
	struct exofs_sb_info *sbi = inode->i_sb->s_fs_info;
	char *kaddr = page_address(page);
	unsigned from = ((char *)dir - kaddr) & ~(exofs_chunk_size(inode)-1);
	unsigned to = ((char *)dir - kaddr) + le16_to_cpu(dir->rec_len);
	loff_t pos;
	struct exofs_dir_entry *pde = NULL;
	struct exofs_dir_entry *de = (struct exofs_dir_entry *) (kaddr + from);
	int err;

	while (de < dir) {
		if (de->rec_len == 0) {
			EXOFS_ERR("ERROR: exofs_delete_entry:"
				"zero-length directory entry");
			err = -EIO;
			goto out;
		}
		pde = de;
		de = exofs_next_entry(de);
	}
	if (pde)
		from = (char *)pde - (char *)page_address(page);
	pos = page_offset(page) + from;
	lock_page(page);
	err = exofs_write_begin(NULL, page->mapping, pos, to - from, 0,
							&page, NULL);
	if (err)
		EXOFS_ERR("exofs_delete_entry: exofs_write_begin FAILD => %d\n",
			  err);
	if (pde)
		pde->rec_len = cpu_to_le16(to - from);
	dir->inode_no = 0;
	if (likely(!err))
		err = exofs_commit_chunk(page, pos, to - from);
	inode->i_ctime = inode->i_mtime = CURRENT_TIME;
	mark_inode_dirty(inode);
	sbi->s_numfiles--;
out:
	exofs_put_page(page);
	return err;
}