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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int EFBIG ; 
 int /*<<< orphan*/  _get_block_create_0 (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_capable (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reiserfs_bmap(struct inode *inode, sector_t block,
			 struct buffer_head *bh_result, int create)
{
	if (!file_capable(inode, block))
		return -EFBIG;

	reiserfs_write_lock(inode->i_sb);
	/* do not read the direct item */
	_get_block_create_0(inode, block, bh_result, 0);
	reiserfs_write_unlock(inode->i_sb);
	return 0;
}