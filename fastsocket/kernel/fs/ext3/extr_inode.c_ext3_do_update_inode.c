#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_15__ {int tv_sec; } ;
struct TYPE_14__ {int tv_sec; } ;
struct TYPE_13__ {int tv_sec; } ;
struct inode {int i_blocks; int i_generation; struct super_block* i_sb; int /*<<< orphan*/  i_rdev; scalar_t__ i_mode; TYPE_4__ i_mtime; TYPE_3__ i_ctime; TYPE_2__ i_atime; scalar_t__ i_nlink; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct ext3_inode_info {int i_state; int i_dtime; int i_disksize; int i_flags; int i_faddr; int i_file_acl; int i_dir_acl; int /*<<< orphan*/  i_sync_tid; scalar_t__ i_extra_isize; void** i_data; int /*<<< orphan*/  i_frag_size; int /*<<< orphan*/  i_frag_no; } ;
struct ext3_inode {void* i_extra_isize; void** i_block; void* i_generation; void* i_size_high; void* i_dir_acl; void* i_file_acl; int /*<<< orphan*/  i_fsize; int /*<<< orphan*/  i_frag; void* i_faddr; void* i_flags; void* i_dtime; void* i_blocks; void* i_mtime; void* i_ctime; void* i_atime; void* i_size; void* i_links_count; void* i_gid_high; void* i_uid_high; void* i_gid_low; void* i_uid_low; void* i_mode; } ;
struct ext3_iloc {struct buffer_head* bh; } ;
struct buffer_head {int dummy; } ;
struct TYPE_17__ {int h_sync; TYPE_1__* h_transaction; } ;
typedef  TYPE_6__ handle_t ;
struct TYPE_16__ {void* s_rev_level; } ;
struct TYPE_12__ {int /*<<< orphan*/  t_tid; } ;
struct TYPE_11__ {struct buffer_head* s_sbh; TYPE_5__* s_es; int /*<<< orphan*/  s_inode_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int /*<<< orphan*/  EXT3_FEATURE_RO_COMPAT_LARGE_FILE ; 
 int EXT3_GOOD_OLD_REV ; 
 int /*<<< orphan*/  EXT3_HAS_RO_COMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 struct ext3_inode_info* EXT3_I (struct inode*) ; 
 int EXT3_N_BLOCKS ; 
 TYPE_10__* EXT3_SB (struct super_block*) ; 
 int /*<<< orphan*/  EXT3_SET_RO_COMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 int EXT3_STATE_NEW ; 
 int /*<<< orphan*/  NO_UID32 ; 
 scalar_t__ S_ISBLK (scalar_t__) ; 
 scalar_t__ S_ISCHR (scalar_t__) ; 
 int /*<<< orphan*/  S_ISREG (scalar_t__) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ext3_get_inode_flags (struct ext3_inode_info*) ; 
 int ext3_journal_dirty_metadata (TYPE_6__*,struct buffer_head*) ; 
 int ext3_journal_get_write_access (TYPE_6__*,struct buffer_head*) ; 
 struct ext3_inode* ext3_raw_inode (struct ext3_iloc*) ; 
 int /*<<< orphan*/  ext3_std_error (struct super_block*,int) ; 
 int /*<<< orphan*/  ext3_update_dynamic_rev (struct super_block*) ; 
 scalar_t__ fs_high2lowgid (int /*<<< orphan*/ ) ; 
 scalar_t__ fs_high2lowuid (int /*<<< orphan*/ ) ; 
 scalar_t__ high_16_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 scalar_t__ low_16_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ext3_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int new_encode_dev (int /*<<< orphan*/ ) ; 
 int old_encode_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ old_valid_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_opt (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static int ext3_do_update_inode(handle_t *handle,
				struct inode *inode,
				struct ext3_iloc *iloc)
{
	struct ext3_inode *raw_inode = ext3_raw_inode(iloc);
	struct ext3_inode_info *ei = EXT3_I(inode);
	struct buffer_head *bh = iloc->bh;
	int err = 0, rc, block;

again:
	/* we can't allow multiple procs in here at once, its a bit racey */
	lock_buffer(bh);

	/* For fields not not tracking in the in-memory inode,
	 * initialise them to zero for new inodes. */
	if (ei->i_state & EXT3_STATE_NEW)
		memset(raw_inode, 0, EXT3_SB(inode->i_sb)->s_inode_size);

	ext3_get_inode_flags(ei);
	raw_inode->i_mode = cpu_to_le16(inode->i_mode);
	if(!(test_opt(inode->i_sb, NO_UID32))) {
		raw_inode->i_uid_low = cpu_to_le16(low_16_bits(inode->i_uid));
		raw_inode->i_gid_low = cpu_to_le16(low_16_bits(inode->i_gid));
/*
 * Fix up interoperability with old kernels. Otherwise, old inodes get
 * re-used with the upper 16 bits of the uid/gid intact
 */
		if(!ei->i_dtime) {
			raw_inode->i_uid_high =
				cpu_to_le16(high_16_bits(inode->i_uid));
			raw_inode->i_gid_high =
				cpu_to_le16(high_16_bits(inode->i_gid));
		} else {
			raw_inode->i_uid_high = 0;
			raw_inode->i_gid_high = 0;
		}
	} else {
		raw_inode->i_uid_low =
			cpu_to_le16(fs_high2lowuid(inode->i_uid));
		raw_inode->i_gid_low =
			cpu_to_le16(fs_high2lowgid(inode->i_gid));
		raw_inode->i_uid_high = 0;
		raw_inode->i_gid_high = 0;
	}
	raw_inode->i_links_count = cpu_to_le16(inode->i_nlink);
	raw_inode->i_size = cpu_to_le32(ei->i_disksize);
	raw_inode->i_atime = cpu_to_le32(inode->i_atime.tv_sec);
	raw_inode->i_ctime = cpu_to_le32(inode->i_ctime.tv_sec);
	raw_inode->i_mtime = cpu_to_le32(inode->i_mtime.tv_sec);
	raw_inode->i_blocks = cpu_to_le32(inode->i_blocks);
	raw_inode->i_dtime = cpu_to_le32(ei->i_dtime);
	raw_inode->i_flags = cpu_to_le32(ei->i_flags);
#ifdef EXT3_FRAGMENTS
	raw_inode->i_faddr = cpu_to_le32(ei->i_faddr);
	raw_inode->i_frag = ei->i_frag_no;
	raw_inode->i_fsize = ei->i_frag_size;
#endif
	raw_inode->i_file_acl = cpu_to_le32(ei->i_file_acl);
	if (!S_ISREG(inode->i_mode)) {
		raw_inode->i_dir_acl = cpu_to_le32(ei->i_dir_acl);
	} else {
		raw_inode->i_size_high =
			cpu_to_le32(ei->i_disksize >> 32);
		if (ei->i_disksize > 0x7fffffffULL) {
			struct super_block *sb = inode->i_sb;
			if (!EXT3_HAS_RO_COMPAT_FEATURE(sb,
					EXT3_FEATURE_RO_COMPAT_LARGE_FILE) ||
			    EXT3_SB(sb)->s_es->s_rev_level ==
					cpu_to_le32(EXT3_GOOD_OLD_REV)) {
			       /* If this is the first large file
				* created, add a flag to the superblock.
				*/
				unlock_buffer(bh);
				err = ext3_journal_get_write_access(handle,
						EXT3_SB(sb)->s_sbh);
				if (err)
					goto out_brelse;

				ext3_update_dynamic_rev(sb);
				EXT3_SET_RO_COMPAT_FEATURE(sb,
					EXT3_FEATURE_RO_COMPAT_LARGE_FILE);
				handle->h_sync = 1;
				err = ext3_journal_dirty_metadata(handle,
						EXT3_SB(sb)->s_sbh);
				/* get our lock and start over */
				goto again;
			}
		}
	}
	raw_inode->i_generation = cpu_to_le32(inode->i_generation);
	if (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode)) {
		if (old_valid_dev(inode->i_rdev)) {
			raw_inode->i_block[0] =
				cpu_to_le32(old_encode_dev(inode->i_rdev));
			raw_inode->i_block[1] = 0;
		} else {
			raw_inode->i_block[0] = 0;
			raw_inode->i_block[1] =
				cpu_to_le32(new_encode_dev(inode->i_rdev));
			raw_inode->i_block[2] = 0;
		}
	} else for (block = 0; block < EXT3_N_BLOCKS; block++)
		raw_inode->i_block[block] = ei->i_data[block];

	if (ei->i_extra_isize)
		raw_inode->i_extra_isize = cpu_to_le16(ei->i_extra_isize);

	BUFFER_TRACE(bh, "call ext3_journal_dirty_metadata");
	unlock_buffer(bh);
	rc = ext3_journal_dirty_metadata(handle, bh);
	if (!err)
		err = rc;
	ei->i_state &= ~EXT3_STATE_NEW;

	atomic_set(&ei->i_sync_tid, handle->h_transaction->t_tid);
out_brelse:
	brelse (bh);
	ext3_std_error(inode->i_sb, err);
	return err;
}