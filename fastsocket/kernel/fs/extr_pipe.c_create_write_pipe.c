#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qstr {char* name; } ;
struct path {TYPE_3__* dentry; int /*<<< orphan*/  mnt; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct file {int f_flags; scalar_t__ f_version; int /*<<< orphan*/  f_mapping; } ;
struct TYPE_6__ {int /*<<< orphan*/  d_flags; int /*<<< orphan*/ * d_op; } ;
struct TYPE_5__ {int /*<<< orphan*/  mnt_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_UNHASHED ; 
 int ENFILE ; 
 int ENOMEM ; 
 struct file* ERR_PTR (int) ; 
 int /*<<< orphan*/  FMODE_WRITE ; 
 int O_NONBLOCK ; 
 int O_WRONLY ; 
 struct file* alloc_file (struct path*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* d_alloc_pseudo (int /*<<< orphan*/ ,struct qstr*) ; 
 int /*<<< orphan*/  d_instantiate (TYPE_3__*,struct inode*) ; 
 int /*<<< orphan*/  free_pipe_info (struct inode*) ; 
 struct inode* get_pipe_inode () ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mntget (TYPE_1__*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 TYPE_1__* pipe_mnt ; 
 int /*<<< orphan*/  pipefs_dentry_operations ; 
 int /*<<< orphan*/  write_pipefifo_fops ; 

struct file *create_write_pipe(int flags)
{
	int err;
	struct inode *inode;
	struct file *f;
	struct path path;
	struct qstr name = { .name = "" };

	err = -ENFILE;
	inode = get_pipe_inode();
	if (!inode)
		goto err;

	err = -ENOMEM;
	path.dentry = d_alloc_pseudo(pipe_mnt->mnt_sb, &name);
	if (!path.dentry)
		goto err_inode;
	path.mnt = mntget(pipe_mnt);

	path.dentry->d_op = &pipefs_dentry_operations;
	/*
	 * We dont want to publish this dentry into global dentry hash table.
	 * We pretend dentry is already hashed, by unsetting DCACHE_UNHASHED
	 * This permits a working /proc/$pid/fd/XXX on pipes
	 */
	path.dentry->d_flags &= ~DCACHE_UNHASHED;
	d_instantiate(path.dentry, inode);

	err = -ENFILE;
	f = alloc_file(&path, FMODE_WRITE, &write_pipefifo_fops);
	if (!f)
		goto err_dentry;
	f->f_mapping = inode->i_mapping;

	f->f_flags = O_WRONLY | (flags & O_NONBLOCK);
	f->f_version = 0;

	return f;

 err_dentry:
	free_pipe_info(inode);
	path_put(&path);
	return ERR_PTR(err);

 err_inode:
	free_pipe_info(inode);
	iput(inode);
 err:
	return ERR_PTR(err);
}