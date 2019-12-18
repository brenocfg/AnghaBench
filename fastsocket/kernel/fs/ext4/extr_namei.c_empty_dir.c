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
struct super_block {unsigned int s_blocksize; } ;
struct inode {unsigned int i_size; scalar_t__ i_ino; struct super_block* i_sb; } ;
struct ext4_dir_entry_2 {int /*<<< orphan*/  rec_len; int /*<<< orphan*/  inode; int /*<<< orphan*/  name; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 unsigned int EXT4_BLOCK_SIZE_BITS (struct super_block*) ; 
 unsigned int EXT4_DIR_REC_LEN (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct buffer_head* ext4_bread (int /*<<< orphan*/ *,struct inode*,unsigned int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ext4_check_dir_entry (char*,struct inode*,struct ext4_dir_entry_2*,struct buffer_head*,unsigned int) ; 
 int /*<<< orphan*/  ext4_error (struct super_block*,char*,int,scalar_t__,...) ; 
 struct ext4_dir_entry_2* ext4_next_entry (struct ext4_dir_entry_2*,unsigned int) ; 
 unsigned int ext4_rec_len_from_disk (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ext4_warning (struct super_block*,char*,scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int empty_dir(struct inode *inode)
{
	unsigned int offset;
	struct buffer_head *bh;
	struct ext4_dir_entry_2 *de, *de1;
	struct super_block *sb;
	int err = 0;

	sb = inode->i_sb;
	if (inode->i_size < EXT4_DIR_REC_LEN(1) + EXT4_DIR_REC_LEN(2) ||
	    !(bh = ext4_bread(NULL, inode, 0, 0, &err))) {
		if (err)
			ext4_error(inode->i_sb,
				   "error %d reading directory #%lu offset 0",
				   err, inode->i_ino);
		else
			ext4_warning(inode->i_sb,
				     "bad directory (dir #%lu) - no data block",
				     inode->i_ino);
		return 1;
	}
	de = (struct ext4_dir_entry_2 *) bh->b_data;
	de1 = ext4_next_entry(de, sb->s_blocksize);
	if (le32_to_cpu(de->inode) != inode->i_ino ||
			!le32_to_cpu(de1->inode) ||
			strcmp(".", de->name) ||
			strcmp("..", de1->name)) {
		ext4_warning(inode->i_sb,
			     "bad directory (dir #%lu) - no `.' or `..'",
			     inode->i_ino);
		brelse(bh);
		return 1;
	}
	offset = ext4_rec_len_from_disk(de->rec_len, sb->s_blocksize) +
		 ext4_rec_len_from_disk(de1->rec_len, sb->s_blocksize);
	de = ext4_next_entry(de1, sb->s_blocksize);
	while (offset < inode->i_size) {
		if (!bh ||
			(void *) de >= (void *) (bh->b_data+sb->s_blocksize)) {
			err = 0;
			brelse(bh);
			bh = ext4_bread(NULL, inode,
				offset >> EXT4_BLOCK_SIZE_BITS(sb), 0, &err);
			if (!bh) {
				if (err)
					ext4_error(sb,
						   "error %d reading directory"
						   " #%lu offset %u",
						   err, inode->i_ino, offset);
				offset += sb->s_blocksize;
				continue;
			}
			de = (struct ext4_dir_entry_2 *) bh->b_data;
		}
		if (!ext4_check_dir_entry("empty_dir", inode, de, bh, offset)) {
			de = (struct ext4_dir_entry_2 *)(bh->b_data +
							 sb->s_blocksize);
			offset = (offset | (sb->s_blocksize - 1)) + 1;
			continue;
		}
		if (le32_to_cpu(de->inode)) {
			brelse(bh);
			return 0;
		}
		offset += ext4_rec_len_from_disk(de->rec_len, sb->s_blocksize);
		de = ext4_next_entry(de, sb->s_blocksize);
	}
	brelse(bh);
	return 1;
}