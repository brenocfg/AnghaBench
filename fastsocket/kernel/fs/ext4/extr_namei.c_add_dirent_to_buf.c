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
struct inode {TYPE_3__* i_sb; int /*<<< orphan*/  i_version; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; } ;
struct ext4_dir_entry_2 {int name_len; int /*<<< orphan*/  name; scalar_t__ inode; int /*<<< orphan*/  file_type; void* rec_len; } ;
struct TYPE_6__ {char* name; int len; } ;
struct dentry {TYPE_2__ d_name; TYPE_1__* d_parent; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_7__ {unsigned int s_blocksize; } ;
struct TYPE_5__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int EEXIST ; 
 int EIO ; 
 int ENOSPC ; 
 void* EXT4_DIR_REC_LEN (int) ; 
 int /*<<< orphan*/  EXT4_FT_UNKNOWN ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_check_dir_entry (char*,struct inode*,struct ext4_dir_entry_2*,struct buffer_head*,unsigned int) ; 
 int /*<<< orphan*/  ext4_current_time (struct inode*) ; 
 int ext4_handle_dirty_metadata (int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext4_match (int,char const*,struct ext4_dir_entry_2*) ; 
 int ext4_rec_len_from_disk (void*,unsigned int) ; 
 void* ext4_rec_len_to_disk (int,unsigned int) ; 
 int /*<<< orphan*/  ext4_set_de_type (TYPE_3__*,struct ext4_dir_entry_2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_std_error (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ext4_update_dx_flag (struct inode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int add_dirent_to_buf(handle_t *handle, struct dentry *dentry,
			     struct inode *inode, struct ext4_dir_entry_2 *de,
			     struct buffer_head *bh)
{
	struct inode	*dir = dentry->d_parent->d_inode;
	const char	*name = dentry->d_name.name;
	int		namelen = dentry->d_name.len;
	unsigned int	offset = 0;
	unsigned int	blocksize = dir->i_sb->s_blocksize;
	unsigned short	reclen;
	int		nlen, rlen, err;
	char		*top;

	reclen = EXT4_DIR_REC_LEN(namelen);
	if (!de) {
		de = (struct ext4_dir_entry_2 *)bh->b_data;
		top = bh->b_data + blocksize - reclen;
		while ((char *) de <= top) {
			if (!ext4_check_dir_entry("ext4_add_entry", dir, de,
						  bh, offset))
				return -EIO;
			if (ext4_match(namelen, name, de))
				return -EEXIST;
			nlen = EXT4_DIR_REC_LEN(de->name_len);
			rlen = ext4_rec_len_from_disk(de->rec_len, blocksize);
			if ((de->inode? rlen - nlen: rlen) >= reclen)
				break;
			de = (struct ext4_dir_entry_2 *)((char *)de + rlen);
			offset += rlen;
		}
		if ((char *) de > top)
			return -ENOSPC;
	}
	BUFFER_TRACE(bh, "get_write_access");
	err = ext4_journal_get_write_access(handle, bh);
	if (err) {
		ext4_std_error(dir->i_sb, err);
		return err;
	}

	/* By now the buffer is marked for journaling */
	nlen = EXT4_DIR_REC_LEN(de->name_len);
	rlen = ext4_rec_len_from_disk(de->rec_len, blocksize);
	if (de->inode) {
		struct ext4_dir_entry_2 *de1 = (struct ext4_dir_entry_2 *)((char *)de + nlen);
		de1->rec_len = ext4_rec_len_to_disk(rlen - nlen, blocksize);
		de->rec_len = ext4_rec_len_to_disk(nlen, blocksize);
		de = de1;
	}
	de->file_type = EXT4_FT_UNKNOWN;
	if (inode) {
		de->inode = cpu_to_le32(inode->i_ino);
		ext4_set_de_type(dir->i_sb, de, inode->i_mode);
	} else
		de->inode = 0;
	de->name_len = namelen;
	memcpy(de->name, name, namelen);
	/*
	 * XXX shouldn't update any times until successful
	 * completion of syscall, but too many callers depend
	 * on this.
	 *
	 * XXX similarly, too many callers depend on
	 * ext4_new_inode() setting the times, but error
	 * recovery deletes the inode, so the worst that can
	 * happen is that the times are slightly out of date
	 * and/or different from the directory change time.
	 */
	dir->i_mtime = dir->i_ctime = ext4_current_time(dir);
	ext4_update_dx_flag(dir);
	dir->i_version++;
	ext4_mark_inode_dirty(handle, dir);
	BUFFER_TRACE(bh, "call ext4_handle_dirty_metadata");
	err = ext4_handle_dirty_metadata(handle, dir, bh);
	if (err)
		ext4_std_error(dir->i_sb, err);
	return 0;
}