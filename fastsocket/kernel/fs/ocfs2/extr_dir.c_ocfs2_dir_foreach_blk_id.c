#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct ocfs2_inline_data {scalar_t__ id_data; } ;
struct ocfs2_dir_entry {size_t file_type; int /*<<< orphan*/  rec_len; int /*<<< orphan*/  inode; int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {struct ocfs2_inline_data i_data; } ;
struct ocfs2_dinode {TYPE_1__ id2; } ;
struct inode {scalar_t__ i_version; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int loff_t ;
typedef  int (* filldir_t ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,unsigned char) ;
struct TYPE_4__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 unsigned char DT_UNKNOWN ; 
 int /*<<< orphan*/  ML_ERROR ; 
 scalar_t__ OCFS2_DIR_REC_LEN (int) ; 
 size_t OCFS2_FT_MAX ; 
 TYPE_2__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int i_size_read (struct inode*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  ocfs2_check_dir_entry (struct inode*,struct ocfs2_dir_entry*,struct buffer_head*,int) ; 
 unsigned char* ocfs2_filetype_table ; 
 int ocfs2_read_inode_block (struct inode*,struct buffer_head**) ; 

__attribute__((used)) static int ocfs2_dir_foreach_blk_id(struct inode *inode,
				    u64 *f_version,
				    loff_t *f_pos, void *priv,
				    filldir_t filldir, int *filldir_err)
{
	int ret, i, filldir_ret;
	unsigned long offset = *f_pos;
	struct buffer_head *di_bh = NULL;
	struct ocfs2_dinode *di;
	struct ocfs2_inline_data *data;
	struct ocfs2_dir_entry *de;

	ret = ocfs2_read_inode_block(inode, &di_bh);
	if (ret) {
		mlog(ML_ERROR, "Unable to read inode block for dir %llu\n",
		     (unsigned long long)OCFS2_I(inode)->ip_blkno);
		goto out;
	}

	di = (struct ocfs2_dinode *)di_bh->b_data;
	data = &di->id2.i_data;

	while (*f_pos < i_size_read(inode)) {
revalidate:
		/* If the dir block has changed since the last call to
		 * readdir(2), then we might be pointing to an invalid
		 * dirent right now.  Scan from the start of the block
		 * to make sure. */
		if (*f_version != inode->i_version) {
			for (i = 0; i < i_size_read(inode) && i < offset; ) {
				de = (struct ocfs2_dir_entry *)
					(data->id_data + i);
				/* It's too expensive to do a full
				 * dirent test each time round this
				 * loop, but we do have to test at
				 * least that it is non-zero.  A
				 * failure will be detected in the
				 * dirent test below. */
				if (le16_to_cpu(de->rec_len) <
				    OCFS2_DIR_REC_LEN(1))
					break;
				i += le16_to_cpu(de->rec_len);
			}
			*f_pos = offset = i;
			*f_version = inode->i_version;
		}

		de = (struct ocfs2_dir_entry *) (data->id_data + *f_pos);
		if (!ocfs2_check_dir_entry(inode, de, di_bh, *f_pos)) {
			/* On error, skip the f_pos to the end. */
			*f_pos = i_size_read(inode);
			goto out;
		}
		offset += le16_to_cpu(de->rec_len);
		if (le64_to_cpu(de->inode)) {
			/* We might block in the next section
			 * if the data destination is
			 * currently swapped out.  So, use a
			 * version stamp to detect whether or
			 * not the directory has been modified
			 * during the copy operation.
			 */
			u64 version = *f_version;
			unsigned char d_type = DT_UNKNOWN;

			if (de->file_type < OCFS2_FT_MAX)
				d_type = ocfs2_filetype_table[de->file_type];

			filldir_ret = filldir(priv, de->name,
					      de->name_len,
					      *f_pos,
					      le64_to_cpu(de->inode),
					      d_type);
			if (filldir_ret) {
				if (filldir_err)
					*filldir_err = filldir_ret;
				break;
			}
			if (version != *f_version)
				goto revalidate;
		}
		*f_pos += le16_to_cpu(de->rec_len);
	}

out:
	brelse(di_bh);

	return 0;
}