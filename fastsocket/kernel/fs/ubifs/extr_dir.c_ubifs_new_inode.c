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
struct ubifs_inode {scalar_t__ creat_sqnum; scalar_t__ synced_i_size; int /*<<< orphan*/  compr_type; int /*<<< orphan*/  flags; int /*<<< orphan*/  ui_size; } ;
struct ubifs_info {scalar_t__ highest_inum; int /*<<< orphan*/  cnt_lock; scalar_t__ max_sqnum; int /*<<< orphan*/  default_compr; int /*<<< orphan*/  bdi; int /*<<< orphan*/  vfs_sb; } ;
struct inode {int i_mode; scalar_t__ i_ino; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_size; int /*<<< orphan*/ * i_fop; TYPE_1__* i_mapping; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; int /*<<< orphan*/ * backing_dev_info; scalar_t__ nrpages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ INUM_WARN_WATERMARK ; 
 scalar_t__ INUM_WATERMARK ; 
#define  S_IFBLK 134 
#define  S_IFCHR 133 
#define  S_IFDIR 132 
#define  S_IFIFO 131 
#define  S_IFLNK 130 
 int S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 
 scalar_t__ S_ISDIR (int) ; 
 int S_ISGID ; 
 scalar_t__ S_ISREG (int) ; 
 int /*<<< orphan*/  S_NOCMTIME ; 
 int /*<<< orphan*/  UBIFS_COMPR_NONE ; 
 int /*<<< orphan*/  UBIFS_INO_NODE_SZ ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  inherit_flags (struct inode const*,int) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 struct inode* new_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_current_time (struct inode*) ; 
 int /*<<< orphan*/  ubifs_dir_inode_operations ; 
 int /*<<< orphan*/  ubifs_dir_operations ; 
 int /*<<< orphan*/  ubifs_err (char*) ; 
 int /*<<< orphan*/  ubifs_file_address_operations ; 
 int /*<<< orphan*/  ubifs_file_inode_operations ; 
 int /*<<< orphan*/  ubifs_file_operations ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 int /*<<< orphan*/  ubifs_set_inode_flags (struct inode*) ; 
 int /*<<< orphan*/  ubifs_symlink_inode_operations ; 
 int /*<<< orphan*/  ubifs_warn (char*,unsigned long,scalar_t__) ; 

struct inode *ubifs_new_inode(struct ubifs_info *c, const struct inode *dir,
			      int mode)
{
	struct inode *inode;
	struct ubifs_inode *ui;

	inode = new_inode(c->vfs_sb);
	ui = ubifs_inode(inode);
	if (!inode)
		return ERR_PTR(-ENOMEM);

	/*
	 * Set 'S_NOCMTIME' to prevent VFS form updating [mc]time of inodes and
	 * marking them dirty in file write path (see 'file_update_time()').
	 * UBIFS has to fully control "clean <-> dirty" transitions of inodes
	 * to make budgeting work.
	 */
	inode->i_flags |= (S_NOCMTIME);

	inode->i_uid = current_fsuid();
	if (dir->i_mode & S_ISGID) {
		inode->i_gid = dir->i_gid;
		if (S_ISDIR(mode))
			mode |= S_ISGID;
	} else
		inode->i_gid = current_fsgid();
	inode->i_mode = mode;
	inode->i_mtime = inode->i_atime = inode->i_ctime =
			 ubifs_current_time(inode);
	inode->i_mapping->nrpages = 0;
	/* Disable readahead */
	inode->i_mapping->backing_dev_info = &c->bdi;

	switch (mode & S_IFMT) {
	case S_IFREG:
		inode->i_mapping->a_ops = &ubifs_file_address_operations;
		inode->i_op = &ubifs_file_inode_operations;
		inode->i_fop = &ubifs_file_operations;
		break;
	case S_IFDIR:
		inode->i_op  = &ubifs_dir_inode_operations;
		inode->i_fop = &ubifs_dir_operations;
		inode->i_size = ui->ui_size = UBIFS_INO_NODE_SZ;
		break;
	case S_IFLNK:
		inode->i_op = &ubifs_symlink_inode_operations;
		break;
	case S_IFSOCK:
	case S_IFIFO:
	case S_IFBLK:
	case S_IFCHR:
		inode->i_op  = &ubifs_file_inode_operations;
		break;
	default:
		BUG();
	}

	ui->flags = inherit_flags(dir, mode);
	ubifs_set_inode_flags(inode);
	if (S_ISREG(mode))
		ui->compr_type = c->default_compr;
	else
		ui->compr_type = UBIFS_COMPR_NONE;
	ui->synced_i_size = 0;

	spin_lock(&c->cnt_lock);
	/* Inode number overflow is currently not supported */
	if (c->highest_inum >= INUM_WARN_WATERMARK) {
		if (c->highest_inum >= INUM_WATERMARK) {
			spin_unlock(&c->cnt_lock);
			ubifs_err("out of inode numbers");
			make_bad_inode(inode);
			iput(inode);
			return ERR_PTR(-EINVAL);
		}
		ubifs_warn("running out of inode numbers (current %lu, max %d)",
			   (unsigned long)c->highest_inum, INUM_WATERMARK);
	}

	inode->i_ino = ++c->highest_inum;
	/*
	 * The creation sequence number remains with this inode for its
	 * lifetime. All nodes for this inode have a greater sequence number,
	 * and so it is possible to distinguish obsolete nodes belonging to a
	 * previous incarnation of the same inode number - for example, for the
	 * purpose of rebuilding the index.
	 */
	ui->creat_sqnum = ++c->max_sqnum;
	spin_unlock(&c->cnt_lock);
	return inode;
}