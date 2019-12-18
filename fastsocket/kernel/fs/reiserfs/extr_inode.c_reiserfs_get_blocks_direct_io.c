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
struct inode {int i_blkbits; } ;
struct buffer_head {int b_size; scalar_t__ b_blocknr; int /*<<< orphan*/ * b_page; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int i_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int GET_BLOCK_NO_DANGLE ; 
 TYPE_1__* REISERFS_I (struct inode*) ; 
 scalar_t__ buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_mapped (struct buffer_head*) ; 
 int i_pack_on_close_mask ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int reiserfs_commit_for_inode (struct inode*) ; 
 int reiserfs_get_block (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,int) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int reiserfs_get_blocks_direct_io(struct inode *inode,
					 sector_t iblock,
					 struct buffer_head *bh_result,
					 int create)
{
	int ret;

	bh_result->b_page = NULL;

	/* We set the b_size before reiserfs_get_block call since it is
	   referenced in convert_tail_for_hole() that may be called from
	   reiserfs_get_block() */
	bh_result->b_size = (1 << inode->i_blkbits);

	ret = reiserfs_get_block(inode, iblock, bh_result,
				 create | GET_BLOCK_NO_DANGLE);
	if (ret)
		goto out;

	/* don't allow direct io onto tail pages */
	if (buffer_mapped(bh_result) && bh_result->b_blocknr == 0) {
		/* make sure future calls to the direct io funcs for this offset
		 ** in the file fail by unmapping the buffer
		 */
		clear_buffer_mapped(bh_result);
		ret = -EINVAL;
	}
	/* Possible unpacked tail. Flush the data before pages have
	   disappeared */
	if (REISERFS_I(inode)->i_flags & i_pack_on_close_mask) {
		int err;
		lock_kernel();
		err = reiserfs_commit_for_inode(inode);
		REISERFS_I(inode)->i_flags &= ~i_pack_on_close_mask;
		unlock_kernel();
		if (err < 0)
			ret = err;
	}
      out:
	return ret;
}