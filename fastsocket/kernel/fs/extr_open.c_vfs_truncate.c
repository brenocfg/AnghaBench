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
struct path {int /*<<< orphan*/  mnt; TYPE_1__* dentry; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 long EINVAL ; 
 long EISDIR ; 
 long EPERM ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 int /*<<< orphan*/  O_WRONLY ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 long break_lease (struct inode*,int /*<<< orphan*/ ) ; 
 long do_truncate (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 long get_write_access (struct inode*) ; 
 long inode_permission (struct inode*,int /*<<< orphan*/ ) ; 
 long locks_verify_truncate (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_drop_write (int /*<<< orphan*/ ) ; 
 long mnt_want_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_write_access (struct inode*) ; 
 long security_path_truncate (struct path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_dq_init (struct inode*) ; 

long vfs_truncate(struct path *path, loff_t length)
{
	struct inode *inode;
	long error;

	inode = path->dentry->d_inode;

	/* For directories it's -EISDIR, for other non-regulars - -EINVAL */
	if (S_ISDIR(inode->i_mode))
		return -EISDIR;
	if (!S_ISREG(inode->i_mode))
		return -EINVAL;

	error = mnt_want_write(path->mnt);
	if (error)
		goto out;

	error = inode_permission(inode, MAY_WRITE);
	if (error)
		goto mnt_drop_write_and_out;

	error = -EPERM;
	if (IS_APPEND(inode))
		goto mnt_drop_write_and_out;

	error = get_write_access(inode);
	if (error)
		goto mnt_drop_write_and_out;

	/*
	 * Make sure that there are no leases.  get_write_access() protects
	 * against the truncate racing with a lease-granting setlease().
	 */
	error = break_lease(inode, O_WRONLY);
	if (error)
		goto put_write_and_out;

	error = locks_verify_truncate(inode, NULL, length);
	if (!error)
		error = security_path_truncate(path, length, 0);
	if (!error) {
		vfs_dq_init(inode);
		error = do_truncate(path->dentry, length, 0, NULL);
	}

put_write_and_out:
	put_write_access(inode);
mnt_drop_write_and_out:
	mnt_drop_write(path->mnt);
out:
	return error;
}