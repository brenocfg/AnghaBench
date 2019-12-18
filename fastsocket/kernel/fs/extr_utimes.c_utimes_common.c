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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timespec {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct path {int /*<<< orphan*/  mnt; TYPE_3__* dentry; } ;
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_5__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct iattr {int ia_valid; TYPE_2__ ia_mtime; TYPE_1__ ia_atime; } ;
struct TYPE_6__ {struct inode* d_inode; } ;

/* Variables and functions */
 int ATTR_ATIME ; 
 int ATTR_ATIME_SET ; 
 int ATTR_CTIME ; 
 int ATTR_MTIME ; 
 int ATTR_MTIME_SET ; 
 int ATTR_TIMES_SET ; 
 int EACCES ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 scalar_t__ UTIME_NOW ; 
 scalar_t__ UTIME_OMIT ; 
 int inode_permission (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_owner_or_cap (struct inode*) ; 
 int /*<<< orphan*/  mnt_drop_write (int /*<<< orphan*/ ) ; 
 int mnt_want_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int notify_change (TYPE_3__*,struct iattr*) ; 

__attribute__((used)) static int utimes_common(struct path *path, struct timespec *times)
{
	int error;
	struct iattr newattrs;
	struct inode *inode = path->dentry->d_inode;

	error = mnt_want_write(path->mnt);
	if (error)
		goto out;

	if (times && times[0].tv_nsec == UTIME_NOW &&
		     times[1].tv_nsec == UTIME_NOW)
		times = NULL;

	newattrs.ia_valid = ATTR_CTIME | ATTR_MTIME | ATTR_ATIME;
	if (times) {
		if (times[0].tv_nsec == UTIME_OMIT)
			newattrs.ia_valid &= ~ATTR_ATIME;
		else if (times[0].tv_nsec != UTIME_NOW) {
			newattrs.ia_atime.tv_sec = times[0].tv_sec;
			newattrs.ia_atime.tv_nsec = times[0].tv_nsec;
			newattrs.ia_valid |= ATTR_ATIME_SET;
		}

		if (times[1].tv_nsec == UTIME_OMIT)
			newattrs.ia_valid &= ~ATTR_MTIME;
		else if (times[1].tv_nsec != UTIME_NOW) {
			newattrs.ia_mtime.tv_sec = times[1].tv_sec;
			newattrs.ia_mtime.tv_nsec = times[1].tv_nsec;
			newattrs.ia_valid |= ATTR_MTIME_SET;
		}
		/*
		 * Tell inode_change_ok(), that this is an explicit time
		 * update, even if neither ATTR_ATIME_SET nor ATTR_MTIME_SET
		 * were used.
		 */
		newattrs.ia_valid |= ATTR_TIMES_SET;
	} else {
		/*
		 * If times is NULL (or both times are UTIME_NOW),
		 * then we need to check permissions, because
		 * inode_change_ok() won't do it.
		 */
		error = -EACCES;
                if (IS_IMMUTABLE(inode))
			goto mnt_drop_write_and_out;

		if (!is_owner_or_cap(inode)) {
			error = inode_permission(inode, MAY_WRITE);
			if (error)
				goto mnt_drop_write_and_out;
		}
	}
	mutex_lock(&inode->i_mutex);
	error = notify_change(path->dentry, &newattrs);
	mutex_unlock(&inode->i_mutex);

mnt_drop_write_and_out:
	mnt_drop_write(path->mnt);
out:
	return error;
}