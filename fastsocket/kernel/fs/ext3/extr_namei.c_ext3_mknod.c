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
struct inode {int h_sync; int /*<<< orphan*/  i_sb; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_mode; } ;
struct dentry {int dummy; } ;
typedef  struct inode handle_t ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 scalar_t__ EXT3_DATA_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 scalar_t__ EXT3_INDEX_EXTRA_TRANS_BLOCKS ; 
 int EXT3_QUOTA_INIT_BLOCKS (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int ext3_add_nondir (struct inode*,struct dentry*,struct inode*) ; 
 struct inode* ext3_journal_start (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  ext3_journal_stop (struct inode*) ; 
 struct inode* ext3_new_inode (struct inode*,struct inode*,int) ; 
 scalar_t__ ext3_should_retry_alloc (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ext3_special_inode_operations ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_valid_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext3_mknod (struct inode * dir, struct dentry *dentry,
			int mode, dev_t rdev)
{
	handle_t *handle;
	struct inode *inode;
	int err, retries = 0;

	if (!new_valid_dev(rdev))
		return -EINVAL;

retry:
	handle = ext3_journal_start(dir, EXT3_DATA_TRANS_BLOCKS(dir->i_sb) +
					EXT3_INDEX_EXTRA_TRANS_BLOCKS + 3 +
					2*EXT3_QUOTA_INIT_BLOCKS(dir->i_sb));
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	if (IS_DIRSYNC(dir))
		handle->h_sync = 1;

	inode = ext3_new_inode (handle, dir, mode);
	err = PTR_ERR(inode);
	if (!IS_ERR(inode)) {
		init_special_inode(inode, inode->i_mode, rdev);
#ifdef CONFIG_EXT3_FS_XATTR
		inode->i_op = &ext3_special_inode_operations;
#endif
		err = ext3_add_nondir(handle, dentry, inode);
	}
	ext3_journal_stop(handle);
	if (err == -ENOSPC && ext3_should_retry_alloc(dir->i_sb, &retries))
		goto retry;
	return err;
}