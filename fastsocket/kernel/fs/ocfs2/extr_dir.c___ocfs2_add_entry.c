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
typedef  scalar_t__ u64 ;
struct super_block {unsigned int s_blocksize; } ;
struct ocfs2_dir_lookup_result {struct buffer_head* dl_prev_leaf_bh; struct buffer_head* dl_dx_root_bh; struct buffer_head* dl_leaf_bh; } ;
struct ocfs2_dir_entry {int name_len; void* rec_len; int /*<<< orphan*/  name; scalar_t__ inode; int /*<<< orphan*/  file_type; } ;
struct TYPE_4__ {char* id_data; } ;
struct TYPE_5__ {TYPE_1__ i_data; } ;
struct ocfs2_dinode {TYPE_2__ id2; } ;
struct inode {int /*<<< orphan*/  i_version; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; struct super_block* i_sb; } ;
struct buffer_head {char* b_data; scalar_t__ b_blocknr; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_6__ {int ip_dyn_features; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CURRENT_TIME ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOSPC ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int OCFS2_DIR_REC_LEN (int) ; 
 int /*<<< orphan*/  OCFS2_FT_UNKNOWN ; 
 TYPE_3__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 void* cpu_to_le16 (int) ; 
 scalar_t__ cpu_to_le64 (scalar_t__) ; 
 unsigned int i_size_read (struct inode*) ; 
 int le16_to_cpu (void*) ; 
 scalar_t__ le64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  mlog_bug_on_msg (int /*<<< orphan*/ ,char*,int,char const*,int,unsigned long long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_check_dir_entry (struct inode*,struct ocfs2_dir_entry*,struct buffer_head*,unsigned long) ; 
 scalar_t__ ocfs2_dir_indexed (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_dir_trailer_blk_off (struct super_block*) ; 
 scalar_t__ ocfs2_dirent_would_fit (struct ocfs2_dir_entry*,unsigned short) ; 
 int ocfs2_dx_dir_insert (struct inode*,int /*<<< orphan*/ *,struct ocfs2_dir_lookup_result*) ; 
 scalar_t__ ocfs2_free_list_at_root (struct ocfs2_dir_lookup_result*) ; 
 int ocfs2_journal_access_db (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_access_dr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 scalar_t__ ocfs2_match (int,char const*,struct ocfs2_dir_entry*) ; 
 int /*<<< orphan*/  ocfs2_recalc_free_list (struct inode*,int /*<<< orphan*/ *,struct ocfs2_dir_lookup_result*) ; 
 int /*<<< orphan*/  ocfs2_set_de_type (struct ocfs2_dir_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_skip_dir_trailer (struct inode*,struct ocfs2_dir_entry*,unsigned long,unsigned int) ; 

int __ocfs2_add_entry(handle_t *handle,
		      struct inode *dir,
		      const char *name, int namelen,
		      struct inode *inode, u64 blkno,
		      struct buffer_head *parent_fe_bh,
		      struct ocfs2_dir_lookup_result *lookup)
{
	unsigned long offset;
	unsigned short rec_len;
	struct ocfs2_dir_entry *de, *de1;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)parent_fe_bh->b_data;
	struct super_block *sb = dir->i_sb;
	int retval, status;
	unsigned int size = sb->s_blocksize;
	struct buffer_head *insert_bh = lookup->dl_leaf_bh;
	char *data_start = insert_bh->b_data;

	mlog_entry_void();

	if (!namelen)
		return -EINVAL;

	if (ocfs2_dir_indexed(dir)) {
		struct buffer_head *bh;

		/*
		 * An indexed dir may require that we update the free space
		 * list. Reserve a write to the previous node in the list so
		 * that we don't fail later.
		 *
		 * XXX: This can be either a dx_root_block, or an unindexed
		 * directory tree leaf block.
		 */
		if (ocfs2_free_list_at_root(lookup)) {
			bh = lookup->dl_dx_root_bh;
			retval = ocfs2_journal_access_dr(handle,
						 INODE_CACHE(dir), bh,
						 OCFS2_JOURNAL_ACCESS_WRITE);
		} else {
			bh = lookup->dl_prev_leaf_bh;
			retval = ocfs2_journal_access_db(handle,
						 INODE_CACHE(dir), bh,
						 OCFS2_JOURNAL_ACCESS_WRITE);
		}
		if (retval) {
			mlog_errno(retval);
			return retval;
		}
	} else if (OCFS2_I(dir)->ip_dyn_features & OCFS2_INLINE_DATA_FL) {
		data_start = di->id2.i_data.id_data;
		size = i_size_read(dir);

		BUG_ON(insert_bh != parent_fe_bh);
	}

	rec_len = OCFS2_DIR_REC_LEN(namelen);
	offset = 0;
	de = (struct ocfs2_dir_entry *) data_start;
	while (1) {
		BUG_ON((char *)de >= (size + data_start));

		/* These checks should've already been passed by the
		 * prepare function, but I guess we can leave them
		 * here anyway. */
		if (!ocfs2_check_dir_entry(dir, de, insert_bh, offset)) {
			retval = -ENOENT;
			goto bail;
		}
		if (ocfs2_match(namelen, name, de)) {
			retval = -EEXIST;
			goto bail;
		}

		/* We're guaranteed that we should have space, so we
		 * can't possibly have hit the trailer...right? */
		mlog_bug_on_msg(ocfs2_skip_dir_trailer(dir, de, offset, size),
				"Hit dir trailer trying to insert %.*s "
			        "(namelen %d) into directory %llu.  "
				"offset is %lu, trailer offset is %d\n",
				namelen, name, namelen,
				(unsigned long long)parent_fe_bh->b_blocknr,
				offset, ocfs2_dir_trailer_blk_off(dir->i_sb));

		if (ocfs2_dirent_would_fit(de, rec_len)) {
			dir->i_mtime = dir->i_ctime = CURRENT_TIME;
			retval = ocfs2_mark_inode_dirty(handle, dir, parent_fe_bh);
			if (retval < 0) {
				mlog_errno(retval);
				goto bail;
			}

			if (insert_bh == parent_fe_bh)
				status = ocfs2_journal_access_di(handle,
								 INODE_CACHE(dir),
								 insert_bh,
								 OCFS2_JOURNAL_ACCESS_WRITE);
			else {
				status = ocfs2_journal_access_db(handle,
								 INODE_CACHE(dir),
								 insert_bh,
					      OCFS2_JOURNAL_ACCESS_WRITE);

				if (ocfs2_dir_indexed(dir)) {
					status = ocfs2_dx_dir_insert(dir,
								handle,
								lookup);
					if (status) {
						mlog_errno(status);
						goto bail;
					}
				}
			}

			/* By now the buffer is marked for journaling */
			offset += le16_to_cpu(de->rec_len);
			if (le64_to_cpu(de->inode)) {
				de1 = (struct ocfs2_dir_entry *)((char *) de +
					OCFS2_DIR_REC_LEN(de->name_len));
				de1->rec_len =
					cpu_to_le16(le16_to_cpu(de->rec_len) -
					OCFS2_DIR_REC_LEN(de->name_len));
				de->rec_len = cpu_to_le16(OCFS2_DIR_REC_LEN(de->name_len));
				de = de1;
			}
			de->file_type = OCFS2_FT_UNKNOWN;
			if (blkno) {
				de->inode = cpu_to_le64(blkno);
				ocfs2_set_de_type(de, inode->i_mode);
			} else
				de->inode = 0;
			de->name_len = namelen;
			memcpy(de->name, name, namelen);

			if (ocfs2_dir_indexed(dir))
				ocfs2_recalc_free_list(dir, handle, lookup);

			dir->i_version++;
			status = ocfs2_journal_dirty(handle, insert_bh);
			retval = 0;
			goto bail;
		}

		offset += le16_to_cpu(de->rec_len);
		de = (struct ocfs2_dir_entry *) ((char *) de + le16_to_cpu(de->rec_len));
	}

	/* when you think about it, the assert above should prevent us
	 * from ever getting here. */
	retval = -ENOSPC;
bail:

	mlog_exit(retval);
	return retval;
}