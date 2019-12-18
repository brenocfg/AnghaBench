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
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (struct inode*) ; 
 int nilfs_mdt_read_block (struct inode*,unsigned long,struct buffer_head**) ; 
 scalar_t__ unlikely (int) ; 

int nilfs_mdt_mark_block_dirty(struct inode *inode, unsigned long block)
{
	struct buffer_head *bh;
	int err;

	err = nilfs_mdt_read_block(inode, block, &bh);
	if (unlikely(err))
		return err;
	nilfs_mark_buffer_dirty(bh);
	nilfs_mdt_mark_dirty(inode);
	brelse(bh);
	return 0;
}