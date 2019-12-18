#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {scalar_t__ i_nlink; int h_sync; TYPE_1__* i_sb; int /*<<< orphan*/  i_ino; scalar_t__ i_size; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct ext3_dir_entry_2 {int name_len; int /*<<< orphan*/  name; void* rec_len; void* inode; } ;
struct dentry {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  struct inode handle_t ;
struct TYPE_7__ {scalar_t__ i_disksize; } ;
struct TYPE_6__ {scalar_t__ s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int EMLINK ; 
 int ENOSPC ; 
 scalar_t__ EXT3_DATA_TRANS_BLOCKS (TYPE_1__*) ; 
 scalar_t__ EXT3_DIR_REC_LEN (int) ; 
 TYPE_4__* EXT3_I (struct inode*) ; 
 scalar_t__ EXT3_INDEX_EXTRA_TRANS_BLOCKS ; 
 scalar_t__ EXT3_LINK_MAX ; 
 int EXT3_QUOTA_INIT_BLOCKS (TYPE_1__*) ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int ext3_add_entry (struct inode*,struct dentry*,struct inode*) ; 
 struct buffer_head* ext3_bread (struct inode*,struct inode*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  ext3_dir_inode_operations ; 
 int /*<<< orphan*/  ext3_dir_operations ; 
 int /*<<< orphan*/  ext3_journal_dirty_metadata (struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/  ext3_journal_get_write_access (struct inode*,struct buffer_head*) ; 
 struct inode* ext3_journal_start (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  ext3_journal_stop (struct inode*) ; 
 int /*<<< orphan*/  ext3_mark_inode_dirty (struct inode*,struct inode*) ; 
 struct inode* ext3_new_inode (struct inode*,struct inode*,int) ; 
 struct ext3_dir_entry_2* ext3_next_entry (struct ext3_dir_entry_2*) ; 
 void* ext3_rec_len_to_disk (scalar_t__) ; 
 int /*<<< orphan*/  ext3_set_de_type (TYPE_1__*,struct ext3_dir_entry_2*,int) ; 
 scalar_t__ ext3_should_retry_alloc (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  ext3_update_dx_flag (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static int ext3_mkdir(struct inode * dir, struct dentry * dentry, int mode)
{
	handle_t *handle;
	struct inode * inode;
	struct buffer_head * dir_block;
	struct ext3_dir_entry_2 * de;
	int err, retries = 0;

	if (dir->i_nlink >= EXT3_LINK_MAX)
		return -EMLINK;

retry:
	handle = ext3_journal_start(dir, EXT3_DATA_TRANS_BLOCKS(dir->i_sb) +
					EXT3_INDEX_EXTRA_TRANS_BLOCKS + 3 +
					2*EXT3_QUOTA_INIT_BLOCKS(dir->i_sb));
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	if (IS_DIRSYNC(dir))
		handle->h_sync = 1;

	inode = ext3_new_inode (handle, dir, S_IFDIR | mode);
	err = PTR_ERR(inode);
	if (IS_ERR(inode))
		goto out_stop;

	inode->i_op = &ext3_dir_inode_operations;
	inode->i_fop = &ext3_dir_operations;
	inode->i_size = EXT3_I(inode)->i_disksize = inode->i_sb->s_blocksize;
	dir_block = ext3_bread (handle, inode, 0, 1, &err);
	if (!dir_block) {
		drop_nlink(inode); /* is this nlink == 0? */
		unlock_new_inode(inode);
		ext3_mark_inode_dirty(handle, inode);
		iput (inode);
		goto out_stop;
	}
	BUFFER_TRACE(dir_block, "get_write_access");
	ext3_journal_get_write_access(handle, dir_block);
	de = (struct ext3_dir_entry_2 *) dir_block->b_data;
	de->inode = cpu_to_le32(inode->i_ino);
	de->name_len = 1;
	de->rec_len = ext3_rec_len_to_disk(EXT3_DIR_REC_LEN(de->name_len));
	strcpy (de->name, ".");
	ext3_set_de_type(dir->i_sb, de, S_IFDIR);
	de = ext3_next_entry(de);
	de->inode = cpu_to_le32(dir->i_ino);
	de->rec_len = ext3_rec_len_to_disk(inode->i_sb->s_blocksize -
					EXT3_DIR_REC_LEN(1));
	de->name_len = 2;
	strcpy (de->name, "..");
	ext3_set_de_type(dir->i_sb, de, S_IFDIR);
	inode->i_nlink = 2;
	BUFFER_TRACE(dir_block, "call ext3_journal_dirty_metadata");
	ext3_journal_dirty_metadata(handle, dir_block);
	brelse (dir_block);
	ext3_mark_inode_dirty(handle, inode);
	err = ext3_add_entry (handle, dentry, inode);
	if (err) {
		inode->i_nlink = 0;
		unlock_new_inode(inode);
		ext3_mark_inode_dirty(handle, inode);
		iput (inode);
		goto out_stop;
	}
	inc_nlink(dir);
	ext3_update_dx_flag(dir);
	ext3_mark_inode_dirty(handle, dir);
	d_instantiate(dentry, inode);
	unlock_new_inode(inode);
out_stop:
	ext3_journal_stop(handle);
	if (err == -ENOSPC && ext3_should_retry_alloc(dir->i_sb, &retries))
		goto retry;
	return err;
}