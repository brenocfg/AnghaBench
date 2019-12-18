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
struct inode {int dummy; } ;
struct ext4_allocation_request {unsigned long len; unsigned int flags; int /*<<< orphan*/  goal; struct inode* inode; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  ext4_fsblk_t ;
typedef  int /*<<< orphan*/  ar ;
struct TYPE_2__ {unsigned long i_allocated_meta_blocks; int /*<<< orphan*/  i_block_reservation_lock; scalar_t__ i_delalloc_reserved_flag; } ;

/* Variables and functions */
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  ext4_mb_new_blocks (int /*<<< orphan*/ *,struct ext4_allocation_request*,int*) ; 
 int /*<<< orphan*/  memset (struct ext4_allocation_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_dq_alloc_block_nofail (struct inode*,unsigned long) ; 

ext4_fsblk_t ext4_new_meta_blocks(handle_t *handle, struct inode *inode,
				  ext4_fsblk_t goal, unsigned int flags,
				  unsigned long *count, int *errp)
{
	struct ext4_allocation_request ar;
	ext4_fsblk_t ret;

	memset(&ar, 0, sizeof(ar));
	/* Fill with neighbour allocated blocks */
	ar.inode = inode;
	ar.goal = goal;
	ar.len = count ? *count : 1;
	ar.flags = flags;

	ret = ext4_mb_new_blocks(handle, &ar, errp);
	if (count)
		*count = ar.len;
	/*
	 * Account for the allocated meta blocks.  We will never
	 * fail EDQUOT for metdata, but we do account for it.
	 */
	if (!(*errp) && EXT4_I(inode)->i_delalloc_reserved_flag) {
		spin_lock(&EXT4_I(inode)->i_block_reservation_lock);
		EXT4_I(inode)->i_allocated_meta_blocks += ar.len;
		spin_unlock(&EXT4_I(inode)->i_block_reservation_lock);
		vfs_dq_alloc_block_nofail(inode, ar.len);
	}
	return ret;
}