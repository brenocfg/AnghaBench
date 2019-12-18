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
struct tty_struct {int index; struct inode* driver_data; struct tty_driver* driver; } ;
struct tty_driver {scalar_t__ type; scalar_t__ subtype; scalar_t__ minor_start; int /*<<< orphan*/  major; } ;
struct super_block {struct dentry* s_root; } ;
struct pts_mount_opts {int mode; int /*<<< orphan*/  gid; scalar_t__ setgid; int /*<<< orphan*/  uid; scalar_t__ setuid; } ;
struct pts_fs_info {struct pts_mount_opts mount_opts; } ;
struct inode {int i_ino; struct tty_struct* i_private; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct dentry {TYPE_1__* d_inode; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CURRENT_TIME ; 
 struct pts_fs_info* DEVPTS_SB (struct super_block*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PTY_TYPE_SLAVE ; 
 int S_IFCHR ; 
 scalar_t__ TTY_DRIVER_TYPE_PTY ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 struct dentry* d_alloc_name (struct dentry*,char*) ; 
 int /*<<< orphan*/  fsnotify_create (TYPE_1__*,struct dentry*) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct inode* new_inode (struct super_block*) ; 
 struct super_block* pts_sb_from_inode (struct inode*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int devpts_pty_new(struct inode *ptmx_inode, struct tty_struct *tty)
{
	/* tty layer puts index from devpts_new_index() in here */
	int number = tty->index;
	struct tty_driver *driver = tty->driver;
	dev_t device = MKDEV(driver->major, driver->minor_start+number);
	struct dentry *dentry;
	struct super_block *sb = pts_sb_from_inode(ptmx_inode);
	struct inode *inode = new_inode(sb);
	struct dentry *root = sb->s_root;
	struct pts_fs_info *fsi = DEVPTS_SB(sb);
	struct pts_mount_opts *opts = &fsi->mount_opts;
	char s[12];

	/* We're supposed to be given the slave end of a pty */
	BUG_ON(driver->type != TTY_DRIVER_TYPE_PTY);
	BUG_ON(driver->subtype != PTY_TYPE_SLAVE);

	if (!inode)
		return -ENOMEM;

	inode->i_ino = number + 3;
	inode->i_uid = opts->setuid ? opts->uid : current_fsuid();
	inode->i_gid = opts->setgid ? opts->gid : current_fsgid();
	inode->i_mtime = inode->i_atime = inode->i_ctime = CURRENT_TIME;
	init_special_inode(inode, S_IFCHR|opts->mode, device);
	inode->i_private = tty;
	tty->driver_data = inode;

	sprintf(s, "%d", number);

	mutex_lock(&root->d_inode->i_mutex);

	dentry = d_alloc_name(root, s);
	if (!IS_ERR(dentry)) {
		d_add(dentry, inode);
		fsnotify_create(root->d_inode, dentry);
	}

	mutex_unlock(&root->d_inode->i_mutex);

	return 0;
}