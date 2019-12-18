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
typedef  scalar_t__ u64 ;
struct ufs_sb_private_info {scalar_t__ s_apbshift; scalar_t__ s_apb; int /*<<< orphan*/  s_fpb; int /*<<< orphan*/  s_bsize; } ;
struct ufs_buffer_head {int dummy; } ;
struct super_block {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; struct super_block* i_sb; } ;
struct TYPE_2__ {struct ufs_sb_private_info* s_uspi; } ;

/* Variables and functions */
 scalar_t__ DIRECT_BLOCK ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int /*<<< orphan*/  UFSD (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* UFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  ubh_bforget (struct ufs_buffer_head*) ; 
 struct ufs_buffer_head* ubh_bread (struct super_block*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubh_brelse (struct ufs_buffer_head*) ; 
 scalar_t__ ubh_buffer_dirty (struct ufs_buffer_head*) ; 
 void* ubh_get_data_ptr (struct ufs_sb_private_info*,struct ufs_buffer_head*,scalar_t__) ; 
 int /*<<< orphan*/  ubh_mark_buffer_dirty (struct ufs_buffer_head*) ; 
 int /*<<< orphan*/  ubh_sync_block (struct ufs_buffer_head*) ; 
 int /*<<< orphan*/  ufs_data_ptr_clear (struct ufs_sb_private_info*,void*) ; 
 scalar_t__ ufs_data_ptr_to_cpu (struct super_block*,void*) ; 
 int /*<<< orphan*/  ufs_free_blocks (struct inode*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufs_is_data_ptr_zero (struct ufs_sb_private_info*,void*) ; 
 int ufs_trunc_indirect (struct inode*,scalar_t__,void*) ; 

__attribute__((used)) static int ufs_trunc_dindirect(struct inode *inode, u64 offset, void *p)
{
	struct super_block * sb;
	struct ufs_sb_private_info * uspi;
	struct ufs_buffer_head *dind_bh;
	u64 i, tmp, dindirect_block;
	void *dind;
	int retry = 0;
	
	UFSD("ENTER: ino %lu\n", inode->i_ino);
	
	sb = inode->i_sb;
	uspi = UFS_SB(sb)->s_uspi;

	dindirect_block = (DIRECT_BLOCK > offset) 
		? ((DIRECT_BLOCK - offset) >> uspi->s_apbshift) : 0;
	retry = 0;
	
	tmp = ufs_data_ptr_to_cpu(sb, p);
	if (!tmp)
		return 0;
	dind_bh = ubh_bread(sb, tmp, uspi->s_bsize);
	if (tmp != ufs_data_ptr_to_cpu(sb, p)) {
		ubh_brelse (dind_bh);
		return 1;
	}
	if (!dind_bh) {
		ufs_data_ptr_clear(uspi, p);
		return 0;
	}

	for (i = dindirect_block ; i < uspi->s_apb ; i++) {
		dind = ubh_get_data_ptr(uspi, dind_bh, i);
		tmp = ufs_data_ptr_to_cpu(sb, dind);
		if (!tmp)
			continue;
		retry |= ufs_trunc_indirect (inode, offset + (i << uspi->s_apbshift), dind);
		ubh_mark_buffer_dirty(dind_bh);
	}

	for (i = 0; i < uspi->s_apb; i++)
		if (!ufs_is_data_ptr_zero(uspi,
					  ubh_get_data_ptr(uspi, dind_bh, i)))
			break;
	if (i >= uspi->s_apb) {
		tmp = ufs_data_ptr_to_cpu(sb, p);
		ufs_data_ptr_clear(uspi, p);

		ufs_free_blocks(inode, tmp, uspi->s_fpb);
		mark_inode_dirty(inode);
		ubh_bforget(dind_bh);
		dind_bh = NULL;
	}
	if (IS_SYNC(inode) && dind_bh && ubh_buffer_dirty(dind_bh))
		ubh_sync_block(dind_bh);
	ubh_brelse (dind_bh);
	
	UFSD("EXIT: ino %lu\n", inode->i_ino);
	
	return retry;
}