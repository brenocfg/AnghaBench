#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_blocksize; } ;
struct ocfs2_super {struct super_block* sb; } ;
struct ocfs2_extent_tree {int dummy; } ;
struct ocfs2_extent_list {int dummy; } ;
struct ocfs2_dir_lookup_result {struct buffer_head* dl_dx_root_bh; } ;
struct ocfs2_dir_entry {void* rec_len; scalar_t__ inode; } ;
struct TYPE_4__ {struct ocfs2_extent_list i_list; } ;
struct ocfs2_dinode {TYPE_1__ id2; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_blocks; TYPE_2__* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  scalar_t__ loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_6__ {int ip_dyn_features; int /*<<< orphan*/  ip_alloc_sem; int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  ip_clusters; scalar_t__ ip_blkno; } ;
struct TYPE_5__ {scalar_t__ s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct buffer_head*) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 TYPE_3__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_CREATE ; 
 int OCFS2_SIMPLE_DIR_EXTEND_CREDITS ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  le16_to_cpu (void*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,scalar_t__) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_calc_extend_credits (struct super_block*,struct ocfs2_extent_list*,int) ; 
 scalar_t__ ocfs2_clusters_to_bytes (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 scalar_t__ ocfs2_dir_indexed (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_dir_trailer_blk_off (struct super_block*) ; 
 int ocfs2_do_extend_dir (struct super_block*,int /*<<< orphan*/ *,struct inode*,struct buffer_head*,struct ocfs2_alloc_context*,struct ocfs2_alloc_context*,struct buffer_head**) ; 
 int ocfs2_dx_dir_link_trailer (struct inode*,int /*<<< orphan*/ *,struct buffer_head*,struct buffer_head*) ; 
 int ocfs2_expand_inline_dir (struct inode*,struct buffer_head*,unsigned int,struct ocfs2_dir_lookup_result*,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_init_dinode_extent_tree (struct ocfs2_extent_tree*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_init_dir_trailer (struct inode*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_sector_count (struct inode*) ; 
 int ocfs2_journal_access_db (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 int ocfs2_num_free_extents (struct ocfs2_super*,struct ocfs2_extent_tree*) ; 
 int ocfs2_reserve_clusters (struct ocfs2_super*,int,struct ocfs2_alloc_context**) ; 
 int ocfs2_reserve_new_metadata (struct ocfs2_super*,struct ocfs2_extent_list*,struct ocfs2_alloc_context**) ; 
 int /*<<< orphan*/  ocfs2_set_new_buffer_uptodate (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int) ; 
 scalar_t__ ocfs2_supports_dir_trailer (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_extend_dir(struct ocfs2_super *osb,
			    struct inode *dir,
			    struct buffer_head *parent_fe_bh,
			    unsigned int blocks_wanted,
			    struct ocfs2_dir_lookup_result *lookup,
			    struct buffer_head **new_de_bh)
{
	int status = 0;
	int credits, num_free_extents, drop_alloc_sem = 0;
	loff_t dir_i_size;
	struct ocfs2_dinode *fe = (struct ocfs2_dinode *) parent_fe_bh->b_data;
	struct ocfs2_extent_list *el = &fe->id2.i_list;
	struct ocfs2_alloc_context *data_ac = NULL;
	struct ocfs2_alloc_context *meta_ac = NULL;
	handle_t *handle = NULL;
	struct buffer_head *new_bh = NULL;
	struct ocfs2_dir_entry * de;
	struct super_block *sb = osb->sb;
	struct ocfs2_extent_tree et;
	struct buffer_head *dx_root_bh = lookup->dl_dx_root_bh;

	mlog_entry_void();

	if (OCFS2_I(dir)->ip_dyn_features & OCFS2_INLINE_DATA_FL) {
		/*
		 * This would be a code error as an inline directory should
		 * never have an index root.
		 */
		BUG_ON(dx_root_bh);

		status = ocfs2_expand_inline_dir(dir, parent_fe_bh,
						 blocks_wanted, lookup,
						 &new_bh);
		if (status) {
			mlog_errno(status);
			goto bail;
		}

		/* Expansion from inline to an indexed directory will
		 * have given us this. */
		dx_root_bh = lookup->dl_dx_root_bh;

		if (blocks_wanted == 1) {
			/*
			 * If the new dirent will fit inside the space
			 * created by pushing out to one block, then
			 * we can complete the operation
			 * here. Otherwise we have to expand i_size
			 * and format the 2nd block below.
			 */
			BUG_ON(new_bh == NULL);
			goto bail_bh;
		}

		/*
		 * Get rid of 'new_bh' - we want to format the 2nd
		 * data block and return that instead.
		 */
		brelse(new_bh);
		new_bh = NULL;

		down_write(&OCFS2_I(dir)->ip_alloc_sem);
		drop_alloc_sem = 1;
		dir_i_size = i_size_read(dir);
		credits = OCFS2_SIMPLE_DIR_EXTEND_CREDITS;
		goto do_extend;
	}

	down_write(&OCFS2_I(dir)->ip_alloc_sem);
	drop_alloc_sem = 1;
	dir_i_size = i_size_read(dir);
	mlog(0, "extending dir %llu (i_size = %lld)\n",
	     (unsigned long long)OCFS2_I(dir)->ip_blkno, dir_i_size);

	/* dir->i_size is always block aligned. */
	spin_lock(&OCFS2_I(dir)->ip_lock);
	if (dir_i_size == ocfs2_clusters_to_bytes(sb, OCFS2_I(dir)->ip_clusters)) {
		spin_unlock(&OCFS2_I(dir)->ip_lock);
		ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(dir),
					      parent_fe_bh);
		num_free_extents = ocfs2_num_free_extents(osb, &et);
		if (num_free_extents < 0) {
			status = num_free_extents;
			mlog_errno(status);
			goto bail;
		}

		if (!num_free_extents) {
			status = ocfs2_reserve_new_metadata(osb, el, &meta_ac);
			if (status < 0) {
				if (status != -ENOSPC)
					mlog_errno(status);
				goto bail;
			}
		}

		status = ocfs2_reserve_clusters(osb, 1, &data_ac);
		if (status < 0) {
			if (status != -ENOSPC)
				mlog_errno(status);
			goto bail;
		}

		credits = ocfs2_calc_extend_credits(sb, el, 1);
	} else {
		spin_unlock(&OCFS2_I(dir)->ip_lock);
		credits = OCFS2_SIMPLE_DIR_EXTEND_CREDITS;
	}

do_extend:
	if (ocfs2_dir_indexed(dir))
		credits++; /* For attaching the new dirent block to the
			    * dx_root */

	handle = ocfs2_start_trans(osb, credits);
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		handle = NULL;
		mlog_errno(status);
		goto bail;
	}

	status = ocfs2_do_extend_dir(osb->sb, handle, dir, parent_fe_bh,
				     data_ac, meta_ac, &new_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	ocfs2_set_new_buffer_uptodate(INODE_CACHE(dir), new_bh);

	status = ocfs2_journal_access_db(handle, INODE_CACHE(dir), new_bh,
					 OCFS2_JOURNAL_ACCESS_CREATE);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}
	memset(new_bh->b_data, 0, sb->s_blocksize);

	de = (struct ocfs2_dir_entry *) new_bh->b_data;
	de->inode = 0;
	if (ocfs2_supports_dir_trailer(dir)) {
		de->rec_len = cpu_to_le16(ocfs2_dir_trailer_blk_off(sb));

		ocfs2_init_dir_trailer(dir, new_bh, le16_to_cpu(de->rec_len));

		if (ocfs2_dir_indexed(dir)) {
			status = ocfs2_dx_dir_link_trailer(dir, handle,
							   dx_root_bh, new_bh);
			if (status) {
				mlog_errno(status);
				goto bail;
			}
		}
	} else {
		de->rec_len = cpu_to_le16(sb->s_blocksize);
	}
	status = ocfs2_journal_dirty(handle, new_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	dir_i_size += dir->i_sb->s_blocksize;
	i_size_write(dir, dir_i_size);
	dir->i_blocks = ocfs2_inode_sector_count(dir);
	status = ocfs2_mark_inode_dirty(handle, dir, parent_fe_bh);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

bail_bh:
	*new_de_bh = new_bh;
	get_bh(*new_de_bh);
bail:
	if (handle)
		ocfs2_commit_trans(osb, handle);
	if (drop_alloc_sem)
		up_write(&OCFS2_I(dir)->ip_alloc_sem);

	if (data_ac)
		ocfs2_free_alloc_context(data_ac);
	if (meta_ac)
		ocfs2_free_alloc_context(meta_ac);

	brelse(new_bh);

	mlog_exit(status);
	return status;
}