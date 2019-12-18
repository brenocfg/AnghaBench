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
struct vfsmount {int dummy; } ;
struct super_operations {int dummy; } ;
struct super_block {unsigned long s_magic; int s_time_gran; int /*<<< orphan*/  s_flags; struct dentry* s_root; struct super_operations const* s_op; int /*<<< orphan*/  s_blocksize_bits; int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_maxbytes; } ;
struct qstr {char* name; int /*<<< orphan*/  len; } ;
struct inode {int i_ino; int i_mode; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; } ;
struct file_system_type {int dummy; } ;
struct dentry {struct dentry* d_parent; struct super_block* d_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int /*<<< orphan*/  MS_ACTIVE ; 
 int /*<<< orphan*/  MS_NOUSER ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (struct super_block*) ; 
 int S_IFDIR ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 struct dentry* d_alloc (int /*<<< orphan*/ *,struct qstr*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  set_anon_super ; 
 struct super_block* sget (struct file_system_type*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_set_mnt (struct vfsmount*,struct super_block*) ; 
 struct super_operations const simple_super_operations ; 
 int /*<<< orphan*/  strlen (char*) ; 

int get_sb_pseudo(struct file_system_type *fs_type, char *name,
	const struct super_operations *ops, unsigned long magic,
	struct vfsmount *mnt)
{
	struct super_block *s = sget(fs_type, NULL, set_anon_super, NULL);
	struct dentry *dentry;
	struct inode *root;
	struct qstr d_name = {.name = name, .len = strlen(name)};

	if (IS_ERR(s))
		return PTR_ERR(s);

	s->s_flags = MS_NOUSER;
	s->s_maxbytes = MAX_LFS_FILESIZE;
	s->s_blocksize = PAGE_SIZE;
	s->s_blocksize_bits = PAGE_SHIFT;
	s->s_magic = magic;
	s->s_op = ops ? ops : &simple_super_operations;
	s->s_time_gran = 1;
	root = new_inode(s);
	if (!root)
		goto Enomem;
	/*
	 * since this is the first inode, make it number 1. New inodes created
	 * after this must take care not to collide with it (by passing
	 * max_reserved of 1 to iunique).
	 */
	root->i_ino = 1;
	root->i_mode = S_IFDIR | S_IRUSR | S_IWUSR;
	root->i_atime = root->i_mtime = root->i_ctime = CURRENT_TIME;
	dentry = d_alloc(NULL, &d_name);
	if (!dentry) {
		iput(root);
		goto Enomem;
	}
	dentry->d_sb = s;
	dentry->d_parent = dentry;
	d_instantiate(dentry, root);
	s->s_root = dentry;
	s->s_flags |= MS_ACTIVE;
	simple_set_mnt(mnt, s);
	return 0;

Enomem:
	deactivate_locked_super(s);
	return -ENOMEM;
}