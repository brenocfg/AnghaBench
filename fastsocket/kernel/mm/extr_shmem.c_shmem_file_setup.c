#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qstr {char const* name; scalar_t__ hash; int /*<<< orphan*/  len; } ;
struct path {int /*<<< orphan*/  dentry; int /*<<< orphan*/  mnt; } ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_size; } ;
typedef  void file ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {struct dentry* mnt_root; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENFILE ; 
 int ENOMEM ; 
 int ENOSPC ; 
 void* ERR_PTR (int) ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  MAX_LFS_FILESIZE ; 
 int S_IFREG ; 
 int S_IRWXUGO ; 
 void* alloc_file (struct path*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_alloc (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  d_instantiate (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  mntget (TYPE_1__*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int ramfs_nommu_expand_for_mapping (struct inode*,int /*<<< orphan*/ ) ; 
 TYPE_1__* shm_mnt ; 
 scalar_t__ shmem_acct_size (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmem_file_operations ; 
 struct inode* shmem_get_inode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  shmem_unacct_size (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

struct file *shmem_file_setup(const char *name, loff_t size, unsigned long flags)
{
	int error;
	struct file *file;
	struct inode *inode;
	struct path path;
	struct dentry *root;
	struct qstr this;

	if (IS_ERR(shm_mnt))
		return (void *)shm_mnt;

	if (size < 0 || size > MAX_LFS_FILESIZE)
		return ERR_PTR(-EINVAL);

	if (shmem_acct_size(flags, size))
		return ERR_PTR(-ENOMEM);

	error = -ENOMEM;
	this.name = name;
	this.len = strlen(name);
	this.hash = 0; /* will go */
	root = shm_mnt->mnt_root;
	path.dentry = d_alloc(root, &this);
	if (!path.dentry)
		goto put_memory;
	path.mnt = mntget(shm_mnt);

	error = -ENOSPC;
	inode = shmem_get_inode(root->d_sb, S_IFREG | S_IRWXUGO, 0, flags);
	if (!inode)
		goto put_dentry;

	d_instantiate(path.dentry, inode);
	inode->i_size = size;
	inode->i_nlink = 0;	/* It is unlinked */
#ifndef CONFIG_MMU
	error = ramfs_nommu_expand_for_mapping(inode, size);
	if (error)
		goto put_dentry;
#endif

	error = -ENFILE;
	file = alloc_file(&path, FMODE_WRITE | FMODE_READ,
		  &shmem_file_operations);
	if (!file)
		goto put_dentry;

	return file;

put_dentry:
	path_put(&path);
put_memory:
	shmem_unacct_size(flags, size);
	return ERR_PTR(error);
}