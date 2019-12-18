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
struct super_block {int dummy; } ;
struct pts_fs_info {int /*<<< orphan*/  allocated_ptys; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct pts_fs_info* DEVPTS_SB (struct super_block*) ; 
 int EAGAIN ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  allocated_ptys_lock ; 
 int ida_get_new (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ida_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct super_block* pts_sb_from_inode (struct inode*) ; 
 int pty_limit ; 

int devpts_new_index(struct inode *ptmx_inode)
{
	struct super_block *sb = pts_sb_from_inode(ptmx_inode);
	struct pts_fs_info *fsi = DEVPTS_SB(sb);
	int index;
	int ida_ret;

retry:
	if (!ida_pre_get(&fsi->allocated_ptys, GFP_KERNEL))
		return -ENOMEM;

	mutex_lock(&allocated_ptys_lock);
	ida_ret = ida_get_new(&fsi->allocated_ptys, &index);
	if (ida_ret < 0) {
		mutex_unlock(&allocated_ptys_lock);
		if (ida_ret == -EAGAIN)
			goto retry;
		return -EIO;
	}

	if (index >= pty_limit) {
		ida_remove(&fsi->allocated_ptys, index);
		mutex_unlock(&allocated_ptys_lock);
		return -EIO;
	}
	mutex_unlock(&allocated_ptys_lock);
	return index;
}