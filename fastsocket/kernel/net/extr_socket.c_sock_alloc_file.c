#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct socket {struct file* file; } ;
struct qstr {char* name; } ;
struct path {TYPE_4__* dentry; int /*<<< orphan*/  mnt; } ;
struct file {int f_flags; struct socket* private_data; scalar_t__ f_pos; } ;
struct TYPE_11__ {int /*<<< orphan*/ * i_fop; } ;
struct TYPE_10__ {TYPE_1__* d_inode; int /*<<< orphan*/  d_flags; int /*<<< orphan*/ * d_op; } ;
struct TYPE_9__ {int /*<<< orphan*/  mnt_sb; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_UNHASHED ; 
 int ENFILE ; 
 int ENOMEM ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 TYPE_5__* SOCK_INODE (struct socket*) ; 
 struct file* alloc_file (struct path*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_4__* d_alloc_pseudo (int /*<<< orphan*/ ,struct qstr*) ; 
 int /*<<< orphan*/  d_instantiate (TYPE_4__*,TYPE_5__*) ; 
 int get_unused_fd_flags (int) ; 
 int /*<<< orphan*/  mntget (TYPE_2__*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 
 TYPE_2__* sock_mnt ; 
 int /*<<< orphan*/  socket_file_ops ; 
 int /*<<< orphan*/  sockfs_dentry_operations ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sock_alloc_file(struct socket *sock, struct file **f, int flags)
{
	struct qstr name = { .name = "" };
	struct path path;
	struct file *file;
	int fd;

	fd = get_unused_fd_flags(flags);
	if (unlikely(fd < 0))
		return fd;

	path.dentry = d_alloc_pseudo(sock_mnt->mnt_sb, &name);
	if (unlikely(!path.dentry)) {
		put_unused_fd(fd);
		return -ENOMEM;
	}
	path.mnt = mntget(sock_mnt);

	path.dentry->d_op = &sockfs_dentry_operations;
	/*
	 * We dont want to push this dentry into global dentry hash table.
	 * We pretend dentry is already hashed, by unsetting DCACHE_UNHASHED
	 * This permits a working /proc/$pid/fd/XXX on sockets
	 */
	path.dentry->d_flags &= ~DCACHE_UNHASHED;
	d_instantiate(path.dentry, SOCK_INODE(sock));
	SOCK_INODE(sock)->i_fop = &socket_file_ops;

	file = alloc_file(&path, FMODE_READ | FMODE_WRITE,
		  &socket_file_ops);
	if (unlikely(!file)) {
		/* drop dentry, keep inode */
		atomic_inc(&path.dentry->d_inode->i_count);
		path_put(&path);
		put_unused_fd(fd);
		return -ENFILE;
	}

	sock->file = file;
	file->f_flags = O_RDWR | (flags & O_NONBLOCK);
	file->f_pos = 0;
	file->private_data = sock;

	*f = file;
	return fd;
}