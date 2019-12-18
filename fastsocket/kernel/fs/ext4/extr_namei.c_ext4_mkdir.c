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
struct inode {unsigned int i_size; int i_nlink; TYPE_1__* i_sb; int /*<<< orphan*/  i_ino; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct ext4_dir_entry_2 {int name_len; int /*<<< orphan*/  name; void* rec_len; void* inode; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  struct inode handle_t ;
struct TYPE_7__ {unsigned int i_disksize; } ;
struct TYPE_6__ {unsigned int s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int EMLINK ; 
 int ENOSPC ; 
 scalar_t__ EXT4_DATA_TRANS_BLOCKS (TYPE_1__*) ; 
 scalar_t__ EXT4_DIR_LINK_MAX (struct inode*) ; 
 int /*<<< orphan*/  EXT4_DIR_REC_LEN (int) ; 
 TYPE_4__* EXT4_I (struct inode*) ; 
 scalar_t__ EXT4_INDEX_EXTRA_TRANS_BLOCKS ; 
 scalar_t__ EXT4_MAXQUOTAS_INIT_BLOCKS (TYPE_1__*) ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int ext4_add_entry (struct inode*,struct dentry*,struct inode*) ; 
 struct buffer_head* ext4_bread (struct inode*,struct inode*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  ext4_dir_inode_operations ; 
 int /*<<< orphan*/  ext4_dir_operations ; 
 int /*<<< orphan*/  ext4_handle_dirty_metadata (struct inode*,struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_handle_sync (struct inode*) ; 
 int /*<<< orphan*/  ext4_inc_count (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  ext4_journal_get_write_access (struct inode*,struct buffer_head*) ; 
 struct inode* ext4_journal_start (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  ext4_journal_stop (struct inode*) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (struct inode*,struct inode*) ; 
 struct inode* ext4_new_inode (struct inode*,struct inode*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ext4_dir_entry_2* ext4_next_entry (struct ext4_dir_entry_2*,unsigned int) ; 
 void* ext4_rec_len_to_disk (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ext4_set_de_type (TYPE_1__*,struct ext4_dir_entry_2*,int) ; 
 scalar_t__ ext4_should_retry_alloc (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  ext4_update_dx_flag (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static int ext4_mkdir(struct inode *dir, struct dentry *dentry, int mode)
{
	handle_t *handle;
	struct inode *inode;
	struct buffer_head *dir_block;
	struct ext4_dir_entry_2 *de;
	unsigned int blocksize = dir->i_sb->s_blocksize;
	int err, retries = 0;

	if (EXT4_DIR_LINK_MAX(dir))
		return -EMLINK;

retry:
	handle = ext4_journal_start(dir, EXT4_DATA_TRANS_BLOCKS(dir->i_sb) +
					EXT4_INDEX_EXTRA_TRANS_BLOCKS + 3 +
					EXT4_MAXQUOTAS_INIT_BLOCKS(dir->i_sb));
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	if (IS_DIRSYNC(dir))
		ext4_handle_sync(handle);

	inode = ext4_new_inode(handle, dir, S_IFDIR | mode,
			       &dentry->d_name, 0);
	err = PTR_ERR(inode);
	if (IS_ERR(inode))
		goto out_stop;

	inode->i_op = &ext4_dir_inode_operations;
	inode->i_fop = &ext4_dir_operations;
	inode->i_size = EXT4_I(inode)->i_disksize = inode->i_sb->s_blocksize;
	dir_block = ext4_bread(handle, inode, 0, 1, &err);
	if (!dir_block)
		goto out_clear_inode;
	BUFFER_TRACE(dir_block, "get_write_access");
	ext4_journal_get_write_access(handle, dir_block);
	de = (struct ext4_dir_entry_2 *) dir_block->b_data;
	de->inode = cpu_to_le32(inode->i_ino);
	de->name_len = 1;
	de->rec_len = ext4_rec_len_to_disk(EXT4_DIR_REC_LEN(de->name_len),
					   blocksize);
	strcpy(de->name, ".");
	ext4_set_de_type(dir->i_sb, de, S_IFDIR);
	de = ext4_next_entry(de, blocksize);
	de->inode = cpu_to_le32(dir->i_ino);
	de->rec_len = ext4_rec_len_to_disk(blocksize - EXT4_DIR_REC_LEN(1),
					   blocksize);
	de->name_len = 2;
	strcpy(de->name, "..");
	ext4_set_de_type(dir->i_sb, de, S_IFDIR);
	inode->i_nlink = 2;
	BUFFER_TRACE(dir_block, "call ext4_handle_dirty_metadata");
	ext4_handle_dirty_metadata(handle, inode, dir_block);
	brelse(dir_block);
	ext4_mark_inode_dirty(handle, inode);
	err = ext4_add_entry(handle, dentry, inode);
	if (err) {
out_clear_inode:
		clear_nlink(inode);
		unlock_new_inode(inode);
		ext4_mark_inode_dirty(handle, inode);
		iput(inode);
		goto out_stop;
	}
	ext4_inc_count(handle, dir);
	ext4_update_dx_flag(dir);
	ext4_mark_inode_dirty(handle, dir);
	d_instantiate(dentry, inode);
	unlock_new_inode(inode);
out_stop:
	ext4_journal_stop(handle);
	if (err == -ENOSPC && ext4_should_retry_alloc(dir->i_sb, &retries))
		goto retry;
	return err;
}