#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned long u64 ;
struct super_block {int s_blocksize; int s_blocksize_bits; } ;
struct ocfs2_dir_entry {size_t file_type; int /*<<< orphan*/  rec_len; int /*<<< orphan*/  inode; int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; } ;
struct inode {unsigned long i_version; struct super_block* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int loff_t ;
typedef  int (* filldir_t ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,unsigned char) ;

/* Variables and functions */
 unsigned char DT_UNKNOWN ; 
 int /*<<< orphan*/  OCFS2_BH_READAHEAD ; 
 scalar_t__ OCFS2_DIR_REC_LEN (int) ; 
 size_t OCFS2_FT_MAX ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int i_size_read (struct inode*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_check_dir_entry (struct inode*,struct ocfs2_dir_entry*,struct buffer_head*,unsigned long) ; 
 unsigned char* ocfs2_filetype_table ; 
 scalar_t__ ocfs2_read_dir_block (struct inode*,unsigned long,struct buffer_head**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_dir_foreach_blk_el(struct inode *inode,
				    u64 *f_version,
				    loff_t *f_pos, void *priv,
				    filldir_t filldir, int *filldir_err)
{
	int error = 0;
	unsigned long offset, blk, last_ra_blk = 0;
	int i, stored;
	struct buffer_head * bh, * tmp;
	struct ocfs2_dir_entry * de;
	struct super_block * sb = inode->i_sb;
	unsigned int ra_sectors = 16;

	stored = 0;
	bh = NULL;

	offset = (*f_pos) & (sb->s_blocksize - 1);

	while (!error && !stored && *f_pos < i_size_read(inode)) {
		blk = (*f_pos) >> sb->s_blocksize_bits;
		if (ocfs2_read_dir_block(inode, blk, &bh, 0)) {
			/* Skip the corrupt dirblock and keep trying */
			*f_pos += sb->s_blocksize - offset;
			continue;
		}

		/* The idea here is to begin with 8k read-ahead and to stay
		 * 4k ahead of our current position.
		 *
		 * TODO: Use the pagecache for this. We just need to
		 * make sure it's cluster-safe... */
		if (!last_ra_blk
		    || (((last_ra_blk - blk) << 9) <= (ra_sectors / 2))) {
			for (i = ra_sectors >> (sb->s_blocksize_bits - 9);
			     i > 0; i--) {
				tmp = NULL;
				if (!ocfs2_read_dir_block(inode, ++blk, &tmp,
							  OCFS2_BH_READAHEAD))
					brelse(tmp);
			}
			last_ra_blk = blk;
			ra_sectors = 8;
		}

revalidate:
		/* If the dir block has changed since the last call to
		 * readdir(2), then we might be pointing to an invalid
		 * dirent right now.  Scan from the start of the block
		 * to make sure. */
		if (*f_version != inode->i_version) {
			for (i = 0; i < sb->s_blocksize && i < offset; ) {
				de = (struct ocfs2_dir_entry *) (bh->b_data + i);
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
			offset = i;
			*f_pos = ((*f_pos) & ~(sb->s_blocksize - 1))
				| offset;
			*f_version = inode->i_version;
		}

		while (!error && *f_pos < i_size_read(inode)
		       && offset < sb->s_blocksize) {
			de = (struct ocfs2_dir_entry *) (bh->b_data + offset);
			if (!ocfs2_check_dir_entry(inode, de, bh, offset)) {
				/* On error, skip the f_pos to the
				   next block. */
				*f_pos = ((*f_pos) | (sb->s_blocksize - 1)) + 1;
				brelse(bh);
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
				unsigned long version = *f_version;
				unsigned char d_type = DT_UNKNOWN;

				if (de->file_type < OCFS2_FT_MAX)
					d_type = ocfs2_filetype_table[de->file_type];
				error = filldir(priv, de->name,
						de->name_len,
						*f_pos,
						le64_to_cpu(de->inode),
						d_type);
				if (error) {
					if (filldir_err)
						*filldir_err = error;
					break;
				}
				if (version != *f_version)
					goto revalidate;
				stored ++;
			}
			*f_pos += le16_to_cpu(de->rec_len);
		}
		offset = 0;
		brelse(bh);
		bh = NULL;
	}

	stored = 0;
out:
	return stored;
}