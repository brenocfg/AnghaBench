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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  NILFS_SB (int /*<<< orphan*/ ) ; 
 int PAGE_CACHE_SIZE ; 
 unsigned int generic_write_end (struct file*,struct address_space*,int,unsigned int,unsigned int,struct page*,void*) ; 
 unsigned int nilfs_page_count_clean_buffers (struct page*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  nilfs_set_file_dirty (int /*<<< orphan*/ ,struct inode*,unsigned int) ; 
 int nilfs_transaction_commit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_write_end(struct file *file, struct address_space *mapping,
			   loff_t pos, unsigned len, unsigned copied,
			   struct page *page, void *fsdata)
{
	struct inode *inode = mapping->host;
	unsigned start = pos & (PAGE_CACHE_SIZE - 1);
	unsigned nr_dirty;
	int err;

	nr_dirty = nilfs_page_count_clean_buffers(page, start,
						  start + copied);
	copied = generic_write_end(file, mapping, pos, len, copied, page,
				   fsdata);
	nilfs_set_file_dirty(NILFS_SB(inode->i_sb), inode, nr_dirty);
	err = nilfs_transaction_commit(inode->i_sb);
	return err ? : copied;
}