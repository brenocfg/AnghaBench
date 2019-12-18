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
struct page {int dummy; } ;
struct nilfs_sb_info {int dummy; } ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_sb; } ;
struct address_space {struct inode* host; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 struct nilfs_sb_info* NILFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NILFS_TI_SYNC ; 
 unsigned int block_write_end (int /*<<< orphan*/ *,struct address_space*,scalar_t__,unsigned int,unsigned int,struct page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 unsigned int nilfs_page_count_clean_buffers (struct page*,unsigned int,unsigned int) ; 
 int nilfs_set_file_dirty (struct nilfs_sb_info*,struct inode*,unsigned int) ; 
 int /*<<< orphan*/  nilfs_set_transaction_flag (int /*<<< orphan*/ ) ; 
 unsigned int page_offset (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int nilfs_commit_chunk(struct page *page,
			      struct address_space *mapping,
			      unsigned from, unsigned to)
{
	struct inode *dir = mapping->host;
	struct nilfs_sb_info *sbi = NILFS_SB(dir->i_sb);
	loff_t pos = page_offset(page) + from;
	unsigned len = to - from;
	unsigned nr_dirty, copied;
	int err;

	nr_dirty = nilfs_page_count_clean_buffers(page, from, to);
	copied = block_write_end(NULL, mapping, pos, len, len, page, NULL);
	if (pos + copied > dir->i_size) {
		i_size_write(dir, pos + copied);
		mark_inode_dirty(dir);
	}
	if (IS_DIRSYNC(dir))
		nilfs_set_transaction_flag(NILFS_TI_SYNC);
	err = nilfs_set_file_dirty(sbi, dir, nr_dirty);
	unlock_page(page);
	return err;
}