#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uid_t ;
struct TYPE_5__ {void* t_tid; } ;
typedef  TYPE_1__ transaction_t ;
typedef  void* tid_t ;
struct super_block {int dummy; } ;
struct inode {int i_state; int i_mode; int i_uid; int i_gid; int i_nlink; int i_version; int /*<<< orphan*/  i_ino; struct super_block* i_sb; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_size; int /*<<< orphan*/ * i_fop; void* i_generation; int /*<<< orphan*/  i_blocks; } ;
struct ext4_inode_info {int i_file_acl; int i_extra_isize; scalar_t__* i_data; void* i_datasync_tid; void* i_sync_tid; int /*<<< orphan*/  i_orphan; int /*<<< orphan*/  i_last_alloc_group; int /*<<< orphan*/  i_block_group; scalar_t__ i_reserved_quota; int /*<<< orphan*/  i_disksize; void* i_flags; void* i_dtime; scalar_t__ i_dir_start_lookup; scalar_t__ i_state_flags; } ;
struct ext4_inode {scalar_t__* i_block; scalar_t__ i_version_hi; scalar_t__ i_disk_version; int /*<<< orphan*/  i_extra_isize; scalar_t__ i_generation; int /*<<< orphan*/  i_file_acl_high; scalar_t__ i_file_acl_lo; scalar_t__ i_flags; scalar_t__ i_dtime; int /*<<< orphan*/  i_links_count; int /*<<< orphan*/  i_gid_high; int /*<<< orphan*/  i_uid_high; int /*<<< orphan*/  i_gid_low; int /*<<< orphan*/  i_uid_low; int /*<<< orphan*/  i_mode; } ;
struct ext4_iloc {scalar_t__ bh; int /*<<< orphan*/  block_group; } ;
struct TYPE_6__ {int /*<<< orphan*/  j_state_lock; void* j_commit_sequence; TYPE_1__* j_committing_transaction; TYPE_1__* j_running_transaction; } ;
typedef  TYPE_2__ journal_t ;
typedef  int gid_t ;
typedef  int __u64 ;
typedef  scalar_t__ __le32 ;
struct TYPE_7__ {int s_mount_state; TYPE_2__* s_journal; } ;

/* Variables and functions */
 long EIO ; 
 long ENOMEM ; 
 struct inode* ERR_PTR (long) ; 
 long ESTALE ; 
 int /*<<< orphan*/  EXT4_EINODE_GET_XTIME (int /*<<< orphan*/ ,struct ext4_inode_info*,struct ext4_inode*) ; 
 int /*<<< orphan*/  EXT4_FEATURE_INCOMPAT_64BIT ; 
 scalar_t__ EXT4_FITS_IN_INODE (struct ext4_inode*,struct ext4_inode_info*,int /*<<< orphan*/ ) ; 
 int EXT4_GOOD_OLD_INODE_SIZE ; 
 scalar_t__ EXT4_HAS_INCOMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int /*<<< orphan*/  EXT4_INODE_GET_XTIME (int /*<<< orphan*/ ,struct inode*,struct ext4_inode*) ; 
 int EXT4_INODE_SIZE (struct super_block*) ; 
 int EXT4_N_BLOCKS ; 
 int EXT4_ORPHAN_FS ; 
 TYPE_3__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_STATE_XATTR ; 
 int /*<<< orphan*/  EXT4_XATTR_MAGIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int I_NEW ; 
 int /*<<< orphan*/  NO_UID32 ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISFIFO (int) ; 
 scalar_t__ S_ISLNK (int) ; 
 scalar_t__ S_ISREG (int) ; 
 scalar_t__ S_ISSOCK (int) ; 
 long __ext4_get_inode_loc (struct inode*,struct ext4_iloc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (scalar_t__) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 long ext4_check_inode_blockref (struct inode*) ; 
 int /*<<< orphan*/  ext4_data_block_valid (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  ext4_dir_inode_operations ; 
 int /*<<< orphan*/  ext4_dir_operations ; 
 int /*<<< orphan*/  ext4_error (struct super_block*,char*,int,int /*<<< orphan*/ ) ; 
 long ext4_ext_check_inode (struct inode*) ; 
 int /*<<< orphan*/  ext4_fast_symlink_inode_operations ; 
 int /*<<< orphan*/  ext4_file_inode_operations ; 
 int /*<<< orphan*/  ext4_file_operations ; 
 int /*<<< orphan*/  ext4_inode_blocks (struct ext4_inode*,struct ext4_inode_info*) ; 
 scalar_t__ ext4_inode_is_fast_symlink (struct inode*) ; 
 int /*<<< orphan*/  ext4_isize (struct ext4_inode*) ; 
 struct ext4_inode* ext4_raw_inode (struct ext4_iloc*) ; 
 int /*<<< orphan*/  ext4_set_aops (struct inode*) ; 
 int /*<<< orphan*/  ext4_set_inode_flags (struct inode*) ; 
 int /*<<< orphan*/  ext4_set_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_special_inode_operations ; 
 int /*<<< orphan*/  ext4_symlink_inode_operations ; 
 scalar_t__ ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_atime ; 
 int /*<<< orphan*/  i_crtime ; 
 int /*<<< orphan*/  i_ctime ; 
 int /*<<< orphan*/  i_mtime ; 
 int /*<<< orphan*/  i_version_hi ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 struct inode* iget_locked (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  nd_terminate_link (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  new_decode_dev (void*) ; 
 int /*<<< orphan*/  old_decode_dev (void*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_opt (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *ext4_iget(struct super_block *sb, unsigned long ino)
{
	struct ext4_iloc iloc;
	struct ext4_inode *raw_inode;
	struct ext4_inode_info *ei;
	struct inode *inode;
	journal_t *journal = EXT4_SB(sb)->s_journal;
	long ret;
	int block;

	inode = iget_locked(sb, ino);
	if (!inode)
		return ERR_PTR(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		return inode;

	ei = EXT4_I(inode);
	iloc.bh = 0;

	ret = __ext4_get_inode_loc(inode, &iloc, 0);
	if (ret < 0)
		goto bad_inode;
	raw_inode = ext4_raw_inode(&iloc);
	inode->i_mode = le16_to_cpu(raw_inode->i_mode);
	inode->i_uid = (uid_t)le16_to_cpu(raw_inode->i_uid_low);
	inode->i_gid = (gid_t)le16_to_cpu(raw_inode->i_gid_low);
	if (!(test_opt(inode->i_sb, NO_UID32))) {
		inode->i_uid |= le16_to_cpu(raw_inode->i_uid_high) << 16;
		inode->i_gid |= le16_to_cpu(raw_inode->i_gid_high) << 16;
	}
	inode->i_nlink = le16_to_cpu(raw_inode->i_links_count);

	ei->i_state_flags = 0;
	ei->i_dir_start_lookup = 0;
	ei->i_dtime = le32_to_cpu(raw_inode->i_dtime);
	/* We now have enough fields to check if the inode was active or not.
	 * This is needed because nfsd might try to access dead inodes
	 * the test is that same one that e2fsck uses
	 * NeilBrown 1999oct15
	 */
	if (inode->i_nlink == 0) {
		if (inode->i_mode == 0 ||
		    !(EXT4_SB(inode->i_sb)->s_mount_state & EXT4_ORPHAN_FS)) {
			/* this inode is deleted */
			ret = -ESTALE;
			goto bad_inode;
		}
		/* The only unlinked inodes we let through here have
		 * valid i_mode and are being read by the orphan
		 * recovery code: that's fine, we're about to complete
		 * the process of deleting those. */
	}
	ei->i_flags = le32_to_cpu(raw_inode->i_flags);
	inode->i_blocks = ext4_inode_blocks(raw_inode, ei);
	ei->i_file_acl = le32_to_cpu(raw_inode->i_file_acl_lo);
	if (EXT4_HAS_INCOMPAT_FEATURE(sb, EXT4_FEATURE_INCOMPAT_64BIT))
		ei->i_file_acl |=
			((__u64)le16_to_cpu(raw_inode->i_file_acl_high)) << 32;
	inode->i_size = ext4_isize(raw_inode);
	ei->i_disksize = inode->i_size;
#ifdef CONFIG_QUOTA
	ei->i_reserved_quota = 0;
#endif
	inode->i_generation = le32_to_cpu(raw_inode->i_generation);
	ei->i_block_group = iloc.block_group;
	ei->i_last_alloc_group = ~0;
	/*
	 * NOTE! The in-memory inode i_data array is in little-endian order
	 * even on big-endian machines: we do NOT byteswap the block numbers!
	 */
	for (block = 0; block < EXT4_N_BLOCKS; block++)
		ei->i_data[block] = raw_inode->i_block[block];
	INIT_LIST_HEAD(&ei->i_orphan);

	/*
	 * Set transaction id's of transactions that have to be committed
	 * to finish f[data]sync. We set them to currently running transaction
	 * as we cannot be sure that the inode or some of its metadata isn't
	 * part of the transaction - the inode could have been reclaimed and
	 * now it is reread from disk.
	 */
	if (journal) {
		transaction_t *transaction;
		tid_t tid;

		spin_lock(&journal->j_state_lock);
		if (journal->j_running_transaction)
			transaction = journal->j_running_transaction;
		else
			transaction = journal->j_committing_transaction;
		if (transaction)
			tid = transaction->t_tid;
		else
			tid = journal->j_commit_sequence;
		spin_unlock(&journal->j_state_lock);
		ei->i_sync_tid = tid;
		ei->i_datasync_tid = tid;
	}

	if (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OLD_INODE_SIZE) {
		ei->i_extra_isize = le16_to_cpu(raw_inode->i_extra_isize);
		if (EXT4_GOOD_OLD_INODE_SIZE + ei->i_extra_isize >
		    EXT4_INODE_SIZE(inode->i_sb)) {
			ret = -EIO;
			goto bad_inode;
		}
		if (ei->i_extra_isize == 0) {
			/* The extra space is currently unused. Use it. */
			ei->i_extra_isize = sizeof(struct ext4_inode) -
					    EXT4_GOOD_OLD_INODE_SIZE;
		} else {
			__le32 *magic = (void *)raw_inode +
					EXT4_GOOD_OLD_INODE_SIZE +
					ei->i_extra_isize;
			if (*magic == cpu_to_le32(EXT4_XATTR_MAGIC))
				ext4_set_inode_state(inode, EXT4_STATE_XATTR);
		}
	} else
		ei->i_extra_isize = 0;

	EXT4_INODE_GET_XTIME(i_ctime, inode, raw_inode);
	EXT4_INODE_GET_XTIME(i_mtime, inode, raw_inode);
	EXT4_INODE_GET_XTIME(i_atime, inode, raw_inode);
	EXT4_EINODE_GET_XTIME(i_crtime, ei, raw_inode);

	inode->i_version = le32_to_cpu(raw_inode->i_disk_version);
	if (EXT4_INODE_SIZE(inode->i_sb) > EXT4_GOOD_OLD_INODE_SIZE) {
		if (EXT4_FITS_IN_INODE(raw_inode, ei, i_version_hi))
			inode->i_version |=
			(__u64)(le32_to_cpu(raw_inode->i_version_hi)) << 32;
	}

	ret = 0;
	if (ei->i_file_acl &&
	    !ext4_data_block_valid(EXT4_SB(sb), ei->i_file_acl, 1)) {
		ext4_error(sb, "bad extended attribute block %llu inode #%lu",
			   ei->i_file_acl, inode->i_ino);
		ret = -EIO;
		goto bad_inode;
	} else if (ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS)) {
		if (S_ISREG(inode->i_mode) || S_ISDIR(inode->i_mode) ||
		    (S_ISLNK(inode->i_mode) &&
		     !ext4_inode_is_fast_symlink(inode)))
			/* Validate extent which is part of inode */
			ret = ext4_ext_check_inode(inode);
	} else if (S_ISREG(inode->i_mode) || S_ISDIR(inode->i_mode) ||
		   (S_ISLNK(inode->i_mode) &&
		    !ext4_inode_is_fast_symlink(inode))) {
		/* Validate block references which are part of inode */
		ret = ext4_check_inode_blockref(inode);
	}
	if (ret)
		goto bad_inode;

	if (S_ISREG(inode->i_mode)) {
		inode->i_op = &ext4_file_inode_operations;
		inode->i_fop = &ext4_file_operations;
		ext4_set_aops(inode);
	} else if (S_ISDIR(inode->i_mode)) {
		inode->i_op = &ext4_dir_inode_operations;
		inode->i_fop = &ext4_dir_operations;
	} else if (S_ISLNK(inode->i_mode)) {
		if (ext4_inode_is_fast_symlink(inode)) {
			inode->i_op = &ext4_fast_symlink_inode_operations;
			nd_terminate_link(ei->i_data, inode->i_size,
				sizeof(ei->i_data) - 1);
		} else {
			inode->i_op = &ext4_symlink_inode_operations;
			ext4_set_aops(inode);
		}
	} else if (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode) ||
	      S_ISFIFO(inode->i_mode) || S_ISSOCK(inode->i_mode)) {
		inode->i_op = &ext4_special_inode_operations;
		if (raw_inode->i_block[0])
			init_special_inode(inode, inode->i_mode,
			   old_decode_dev(le32_to_cpu(raw_inode->i_block[0])));
		else
			init_special_inode(inode, inode->i_mode,
			   new_decode_dev(le32_to_cpu(raw_inode->i_block[1])));
	} else {
		ret = -EIO;
		ext4_error(inode->i_sb, "bogus i_mode (%o) for inode=%lu",
			   inode->i_mode, inode->i_ino);
		goto bad_inode;
	}
	brelse(iloc.bh);
	ext4_set_inode_flags(inode);
	unlock_new_inode(inode);
	return inode;

bad_inode:
	brelse(iloc.bh);
	iget_failed(inode);
	return ERR_PTR(ret);
}