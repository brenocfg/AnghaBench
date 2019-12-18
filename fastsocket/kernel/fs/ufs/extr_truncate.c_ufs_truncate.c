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
struct ufs_sb_private_info {scalar_t__ s_apb; } ;
struct ufs_inode_info {int /*<<< orphan*/  i_lastfrag; } ;
struct super_block {int dummy; } ;
struct inode {int i_state; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {struct ufs_sb_private_info* s_uspi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int /*<<< orphan*/  DIRECT_FRAGMENT ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int I_DIRTY ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UFSD (char*,int,...) ; 
 scalar_t__ UFS_DIND_BLOCK ; 
 struct ufs_inode_info* UFS_I (struct inode*) ; 
 scalar_t__ UFS_IND_BLOCK ; 
 TYPE_1__* UFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  blk_run_address_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_truncate_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int ufs_alloc_lastblock (struct inode*) ; 
 int /*<<< orphan*/  ufs_get_direct_data_ptr (struct ufs_sb_private_info*,struct ufs_inode_info*,scalar_t__) ; 
 int /*<<< orphan*/  ufs_getfrag_block ; 
 int /*<<< orphan*/  ufs_sync_inode (struct inode*) ; 
 int ufs_trunc_dindirect (struct inode*,scalar_t__,int /*<<< orphan*/ ) ; 
 int ufs_trunc_direct (struct inode*) ; 
 int ufs_trunc_indirect (struct inode*,scalar_t__,int /*<<< orphan*/ ) ; 
 int ufs_trunc_tindirect (struct inode*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int /*<<< orphan*/  yield () ; 

int ufs_truncate(struct inode *inode, loff_t old_i_size)
{
	struct ufs_inode_info *ufsi = UFS_I(inode);
	struct super_block *sb = inode->i_sb;
	struct ufs_sb_private_info *uspi = UFS_SB(sb)->s_uspi;
	int retry, err = 0;
	
	UFSD("ENTER: ino %lu, i_size: %llu, old_i_size: %llu\n",
	     inode->i_ino, (unsigned long long)i_size_read(inode),
	     (unsigned long long)old_i_size);

	if (!(S_ISREG(inode->i_mode) || S_ISDIR(inode->i_mode) ||
	      S_ISLNK(inode->i_mode)))
		return -EINVAL;
	if (IS_APPEND(inode) || IS_IMMUTABLE(inode))
		return -EPERM;

	err = ufs_alloc_lastblock(inode);

	if (err) {
		i_size_write(inode, old_i_size);
		goto out;
	}

	block_truncate_page(inode->i_mapping, inode->i_size, ufs_getfrag_block);

	lock_kernel();
	while (1) {
		retry = ufs_trunc_direct(inode);
		retry |= ufs_trunc_indirect(inode, UFS_IND_BLOCK,
					    ufs_get_direct_data_ptr(uspi, ufsi,
								    UFS_IND_BLOCK));
		retry |= ufs_trunc_dindirect(inode, UFS_IND_BLOCK + uspi->s_apb,
					     ufs_get_direct_data_ptr(uspi, ufsi,
								     UFS_DIND_BLOCK));
		retry |= ufs_trunc_tindirect (inode);
		if (!retry)
			break;
		if (IS_SYNC(inode) && (inode->i_state & I_DIRTY))
			ufs_sync_inode (inode);
		blk_run_address_space(inode->i_mapping);
		yield();
	}

	inode->i_mtime = inode->i_ctime = CURRENT_TIME_SEC;
	ufsi->i_lastfrag = DIRECT_FRAGMENT;
	unlock_kernel();
	mark_inode_dirty(inode);
out:
	UFSD("EXIT: err %d\n", err);
	return err;
}