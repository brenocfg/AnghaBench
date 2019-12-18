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
struct v9fs_session_info {int dummy; } ;
struct super_block {struct v9fs_session_info* s_fs_info; } ;
struct inode {int i_mode; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; scalar_t__ i_rdev; TYPE_1__* i_mapping; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; scalar_t__ i_blocks; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  P9_DEBUG_ERROR ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  P9_EPRINTK (int /*<<< orphan*/ ,char*) ; 
#define  S_IFBLK 134 
#define  S_IFCHR 133 
#define  S_IFDIR 132 
#define  S_IFIFO 131 
#define  S_IFLNK 130 
 int S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,scalar_t__) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  v9fs_addr_operations ; 
 int /*<<< orphan*/  v9fs_dir_inode_operations ; 
 int /*<<< orphan*/  v9fs_dir_inode_operations_ext ; 
 int /*<<< orphan*/  v9fs_dir_operations ; 
 int /*<<< orphan*/  v9fs_extended (struct v9fs_session_info*) ; 
 int /*<<< orphan*/  v9fs_file_inode_operations ; 
 int /*<<< orphan*/  v9fs_file_operations ; 
 int /*<<< orphan*/  v9fs_symlink_inode_operations ; 

struct inode *v9fs_get_inode(struct super_block *sb, int mode)
{
	int err;
	struct inode *inode;
	struct v9fs_session_info *v9ses = sb->s_fs_info;

	P9_DPRINTK(P9_DEBUG_VFS, "super block: %p mode: %o\n", sb, mode);

	inode = new_inode(sb);
	if (!inode) {
		P9_EPRINTK(KERN_WARNING, "Problem allocating inode\n");
		return ERR_PTR(-ENOMEM);
	}

	inode->i_mode = mode;
	inode->i_uid = current_fsuid();
	inode->i_gid = current_fsgid();
	inode->i_blocks = 0;
	inode->i_rdev = 0;
	inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;
	inode->i_mapping->a_ops = &v9fs_addr_operations;

	switch (mode & S_IFMT) {
	case S_IFIFO:
	case S_IFBLK:
	case S_IFCHR:
	case S_IFSOCK:
		if (!v9fs_extended(v9ses)) {
			P9_DPRINTK(P9_DEBUG_ERROR,
				   "special files without extended mode\n");
			err = -EINVAL;
			goto error;
		}
		init_special_inode(inode, inode->i_mode, inode->i_rdev);
		break;
	case S_IFREG:
		inode->i_op = &v9fs_file_inode_operations;
		inode->i_fop = &v9fs_file_operations;
		break;
	case S_IFLNK:
		if (!v9fs_extended(v9ses)) {
			P9_DPRINTK(P9_DEBUG_ERROR,
				   "extended modes used w/o 9P2000.u\n");
			err = -EINVAL;
			goto error;
		}
		inode->i_op = &v9fs_symlink_inode_operations;
		break;
	case S_IFDIR:
		inc_nlink(inode);
		if (v9fs_extended(v9ses))
			inode->i_op = &v9fs_dir_inode_operations_ext;
		else
			inode->i_op = &v9fs_dir_inode_operations;
		inode->i_fop = &v9fs_dir_operations;
		break;
	default:
		P9_DPRINTK(P9_DEBUG_ERROR, "BAD mode 0x%x S_IFMT 0x%x\n",
			   mode, mode & S_IFMT);
		err = -EINVAL;
		goto error;
	}

	return inode;

error:
	iput(inode);
	return ERR_PTR(err);
}