#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {int i_mode; unsigned long i_ino; scalar_t__ i_nlink; int /*<<< orphan*/  i_flags; scalar_t__ i_generation; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; scalar_t__ i_blocks; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; struct super_block* i_sb; } ;
struct ext3_super_block {int /*<<< orphan*/  s_inodes_count; } ;
struct ext3_sb_info {int s_groups_count; int /*<<< orphan*/  s_next_gen_lock; int /*<<< orphan*/  s_next_generation; int /*<<< orphan*/  s_dirs_counter; int /*<<< orphan*/  s_freeinodes_counter; struct ext3_super_block* s_es; } ;
struct ext3_inode_info {int i_flags; int i_block_group; scalar_t__ i_extra_isize; int /*<<< orphan*/  i_state; int /*<<< orphan*/ * i_block_alloc_info; scalar_t__ i_dtime; scalar_t__ i_dir_acl; scalar_t__ i_file_acl; scalar_t__ i_frag_size; scalar_t__ i_frag_no; scalar_t__ i_faddr; scalar_t__ i_disksize; scalar_t__ i_dir_start_lookup; int /*<<< orphan*/  i_data; } ;
struct ext3_inode {int dummy; } ;
struct ext3_group_desc {int /*<<< orphan*/  bg_used_dirs_count; int /*<<< orphan*/  bg_free_inodes_count; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_9__ {int h_sync; } ;
typedef  TYPE_1__ handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 int EDQUOT ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int EPERM ; 
 struct inode* ERR_PTR (int) ; 
 int EXT3_FIRST_INO (struct super_block*) ; 
 int EXT3_FL_INHERITED ; 
 scalar_t__ EXT3_GOOD_OLD_INODE_SIZE ; 
 struct ext3_inode_info* EXT3_I (struct inode*) ; 
 int EXT3_INODES_PER_GROUP (struct super_block*) ; 
 scalar_t__ EXT3_INODE_SIZE (struct super_block*) ; 
 struct ext3_sb_info* EXT3_SB (struct super_block*) ; 
 int /*<<< orphan*/  EXT3_STATE_NEW ; 
 int /*<<< orphan*/  GRPID ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 int /*<<< orphan*/  OLDALLOC ; 
 scalar_t__ S_ISDIR (int) ; 
 int S_ISGID ; 
 int /*<<< orphan*/  S_NOQUOTA ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  ext3_debug (char*,unsigned long) ; 
 int /*<<< orphan*/  ext3_error (struct super_block*,char*,char*,int,unsigned long) ; 
 unsigned long ext3_find_next_zero_bit (unsigned long*,int,unsigned long) ; 
 struct ext3_group_desc* ext3_get_group_desc (struct super_block*,int,struct buffer_head**) ; 
 int ext3_init_acl (TYPE_1__*,struct inode*,struct inode*) ; 
 int ext3_init_security (TYPE_1__*,struct inode*,struct inode*) ; 
 int ext3_journal_dirty_metadata (TYPE_1__*,struct buffer_head*) ; 
 int ext3_journal_get_write_access (TYPE_1__*,struct buffer_head*) ; 
 int ext3_mark_inode_dirty (TYPE_1__*,struct inode*) ; 
 int ext3_mask_flags (int,int) ; 
 int /*<<< orphan*/  ext3_set_bit_atomic (int /*<<< orphan*/ *,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  ext3_set_inode_flags (struct inode*) ; 
 int /*<<< orphan*/  ext3_std_error (struct super_block*,int) ; 
 int find_group_dir (struct super_block*,struct inode*) ; 
 int find_group_orlov (struct super_block*,struct inode*) ; 
 int find_group_other (struct super_block*,struct inode*) ; 
 scalar_t__ insert_inode_locked (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  journal_release_buffer (TYPE_1__*,struct buffer_head*) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  percpu_counter_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_counter_inc (int /*<<< orphan*/ *) ; 
 struct buffer_head* read_inode_bitmap (struct super_block*,int) ; 
 int /*<<< orphan*/ * sb_bgl_lock (struct ext3_sb_info*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_opt (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext3_allocate_inode (struct inode*,struct inode*,int) ; 
 int /*<<< orphan*/  trace_ext3_request_inode (struct inode*,int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 
 scalar_t__ vfs_dq_alloc_inode (struct inode*) ; 
 int /*<<< orphan*/  vfs_dq_drop (struct inode*) ; 
 int /*<<< orphan*/  vfs_dq_free_inode (struct inode*) ; 

struct inode *ext3_new_inode(handle_t *handle, struct inode * dir, int mode)
{
	struct super_block *sb;
	struct buffer_head *bitmap_bh = NULL;
	struct buffer_head *bh2;
	int group;
	unsigned long ino = 0;
	struct inode * inode;
	struct ext3_group_desc * gdp = NULL;
	struct ext3_super_block * es;
	struct ext3_inode_info *ei;
	struct ext3_sb_info *sbi;
	int err = 0;
	struct inode *ret;
	int i;

	/* Cannot create files in a deleted directory */
	if (!dir || !dir->i_nlink)
		return ERR_PTR(-EPERM);

	sb = dir->i_sb;
	trace_ext3_request_inode(dir, mode);
	inode = new_inode(sb);
	if (!inode)
		return ERR_PTR(-ENOMEM);
	ei = EXT3_I(inode);

	sbi = EXT3_SB(sb);
	es = sbi->s_es;
	if (S_ISDIR(mode)) {
		if (test_opt (sb, OLDALLOC))
			group = find_group_dir(sb, dir);
		else
			group = find_group_orlov(sb, dir);
	} else
		group = find_group_other(sb, dir);

	err = -ENOSPC;
	if (group == -1)
		goto out;

	for (i = 0; i < sbi->s_groups_count; i++) {
		err = -EIO;

		gdp = ext3_get_group_desc(sb, group, &bh2);
		if (!gdp)
			goto fail;

		brelse(bitmap_bh);
		bitmap_bh = read_inode_bitmap(sb, group);
		if (!bitmap_bh)
			goto fail;

		ino = 0;

repeat_in_this_group:
		ino = ext3_find_next_zero_bit((unsigned long *)
				bitmap_bh->b_data, EXT3_INODES_PER_GROUP(sb), ino);
		if (ino < EXT3_INODES_PER_GROUP(sb)) {

			BUFFER_TRACE(bitmap_bh, "get_write_access");
			err = ext3_journal_get_write_access(handle, bitmap_bh);
			if (err)
				goto fail;

			if (!ext3_set_bit_atomic(sb_bgl_lock(sbi, group),
						ino, bitmap_bh->b_data)) {
				/* we won it */
				BUFFER_TRACE(bitmap_bh,
					"call ext3_journal_dirty_metadata");
				err = ext3_journal_dirty_metadata(handle,
								bitmap_bh);
				if (err)
					goto fail;
				goto got;
			}
			/* we lost it */
			journal_release_buffer(handle, bitmap_bh);

			if (++ino < EXT3_INODES_PER_GROUP(sb))
				goto repeat_in_this_group;
		}

		/*
		 * This case is possible in concurrent environment.  It is very
		 * rare.  We cannot repeat the find_group_xxx() call because
		 * that will simply return the same blockgroup, because the
		 * group descriptor metadata has not yet been updated.
		 * So we just go onto the next blockgroup.
		 */
		if (++group == sbi->s_groups_count)
			group = 0;
	}
	err = -ENOSPC;
	goto out;

got:
	ino += group * EXT3_INODES_PER_GROUP(sb) + 1;
	if (ino < EXT3_FIRST_INO(sb) || ino > le32_to_cpu(es->s_inodes_count)) {
		ext3_error (sb, "ext3_new_inode",
			    "reserved inode or inode > inodes count - "
			    "block_group = %d, inode=%lu", group, ino);
		err = -EIO;
		goto fail;
	}

	BUFFER_TRACE(bh2, "get_write_access");
	err = ext3_journal_get_write_access(handle, bh2);
	if (err) goto fail;
	spin_lock(sb_bgl_lock(sbi, group));
	le16_add_cpu(&gdp->bg_free_inodes_count, -1);
	if (S_ISDIR(mode)) {
		le16_add_cpu(&gdp->bg_used_dirs_count, 1);
	}
	spin_unlock(sb_bgl_lock(sbi, group));
	BUFFER_TRACE(bh2, "call ext3_journal_dirty_metadata");
	err = ext3_journal_dirty_metadata(handle, bh2);
	if (err) goto fail;

	percpu_counter_dec(&sbi->s_freeinodes_counter);
	if (S_ISDIR(mode))
		percpu_counter_inc(&sbi->s_dirs_counter);

	inode->i_uid = current_fsuid();
	if (test_opt (sb, GRPID))
		inode->i_gid = dir->i_gid;
	else if (dir->i_mode & S_ISGID) {
		inode->i_gid = dir->i_gid;
		if (S_ISDIR(mode))
			mode |= S_ISGID;
	} else
		inode->i_gid = current_fsgid();
	inode->i_mode = mode;

	inode->i_ino = ino;
	/* This is the optimal IO size (for stat), not the fs block size */
	inode->i_blocks = 0;
	inode->i_mtime = inode->i_atime = inode->i_ctime = CURRENT_TIME_SEC;

	memset(ei->i_data, 0, sizeof(ei->i_data));
	ei->i_dir_start_lookup = 0;
	ei->i_disksize = 0;

	ei->i_flags =
		ext3_mask_flags(mode, EXT3_I(dir)->i_flags & EXT3_FL_INHERITED);
#ifdef EXT3_FRAGMENTS
	ei->i_faddr = 0;
	ei->i_frag_no = 0;
	ei->i_frag_size = 0;
#endif
	ei->i_file_acl = 0;
	ei->i_dir_acl = 0;
	ei->i_dtime = 0;
	ei->i_block_alloc_info = NULL;
	ei->i_block_group = group;

	ext3_set_inode_flags(inode);
	if (IS_DIRSYNC(inode))
		handle->h_sync = 1;
	if (insert_inode_locked(inode) < 0) {
		err = -EINVAL;
		goto fail_drop;
	}
	spin_lock(&sbi->s_next_gen_lock);
	inode->i_generation = sbi->s_next_generation++;
	spin_unlock(&sbi->s_next_gen_lock);

	ei->i_state = EXT3_STATE_NEW;
	/* See comment in ext3_iget for explanation */
	if (ino >= EXT3_FIRST_INO(sb) + 1 &&
	    EXT3_INODE_SIZE(sb) > EXT3_GOOD_OLD_INODE_SIZE) {
		ei->i_extra_isize =
			sizeof(struct ext3_inode) - EXT3_GOOD_OLD_INODE_SIZE;
	} else {
		ei->i_extra_isize = 0;
	}

	ret = inode;
	if (vfs_dq_alloc_inode(inode)) {
		err = -EDQUOT;
		goto fail_drop;
	}

	err = ext3_init_acl(handle, inode, dir);
	if (err)
		goto fail_free_drop;

	err = ext3_init_security(handle,inode, dir);
	if (err)
		goto fail_free_drop;

	err = ext3_mark_inode_dirty(handle, inode);
	if (err) {
		ext3_std_error(sb, err);
		goto fail_free_drop;
	}

	ext3_debug("allocating inode %lu\n", inode->i_ino);
	trace_ext3_allocate_inode(inode, dir, mode);
	goto really_out;
fail:
	ext3_std_error(sb, err);
out:
	iput(inode);
	ret = ERR_PTR(err);
really_out:
	brelse(bitmap_bh);
	return ret;

fail_free_drop:
	vfs_dq_free_inode(inode);

fail_drop:
	vfs_dq_drop(inode);
	inode->i_flags |= S_NOQUOTA;
	inode->i_nlink = 0;
	unlock_new_inode(inode);
	iput(inode);
	brelse(bitmap_bh);
	return ERR_PTR(err);
}