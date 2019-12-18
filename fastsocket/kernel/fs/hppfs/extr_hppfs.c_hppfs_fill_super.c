#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {TYPE_1__* mnt_sb; } ;
struct super_block {int s_blocksize; int s_blocksize_bits; int /*<<< orphan*/  s_root; struct vfsmount* s_fs_info; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_root; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HPPFS_SUPER_MAGIC ; 
 scalar_t__ IS_ERR (struct vfsmount*) ; 
 int /*<<< orphan*/  d_alloc_root (struct inode*) ; 
 struct vfsmount* do_kern_mount (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct inode* get_inode (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hppfs_sbops ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 

__attribute__((used)) static int hppfs_fill_super(struct super_block *sb, void *d, int silent)
{
	struct inode *root_inode;
	struct vfsmount *proc_mnt;
	int err = -ENOENT;

	proc_mnt = do_kern_mount("proc", 0, "proc", NULL);
	if (IS_ERR(proc_mnt))
		goto out;

	sb->s_blocksize = 1024;
	sb->s_blocksize_bits = 10;
	sb->s_magic = HPPFS_SUPER_MAGIC;
	sb->s_op = &hppfs_sbops;
	sb->s_fs_info = proc_mnt;

	err = -ENOMEM;
	root_inode = get_inode(sb, proc_mnt->mnt_sb->s_root);
	if (!root_inode)
		goto out_mntput;

	sb->s_root = d_alloc_root(root_inode);
	if (!sb->s_root)
		goto out_iput;

	return 0;

 out_iput:
	iput(root_inode);
 out_mntput:
	mntput(proc_mnt);
 out:
	return(err);
}