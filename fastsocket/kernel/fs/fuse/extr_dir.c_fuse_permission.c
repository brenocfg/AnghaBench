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
struct inode {int i_mode; } ;
struct fuse_conn {int flags; } ;

/* Variables and functions */
 int EACCES ; 
 int FUSE_DEFAULT_PERMISSIONS ; 
 int MAY_ACCESS ; 
 int MAY_EXEC ; 
 scalar_t__ S_ISREG (int) ; 
 int S_IXUGO ; 
 int fuse_access (struct inode*,int) ; 
 int /*<<< orphan*/  fuse_allow_current_process (struct fuse_conn*) ; 
 int fuse_do_getattr (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fuse_update_attributes (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int generic_permission (struct inode*,int,int /*<<< orphan*/ *) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 

__attribute__((used)) static int fuse_permission(struct inode *inode, int mask)
{
	struct fuse_conn *fc = get_fuse_conn(inode);
	bool refreshed = false;
	int err = 0;

	if (!fuse_allow_current_process(fc))
		return -EACCES;

	/*
	 * If attributes are needed, refresh them before proceeding
	 */
	if ((fc->flags & FUSE_DEFAULT_PERMISSIONS) ||
	    ((mask & MAY_EXEC) && S_ISREG(inode->i_mode))) {
		err = fuse_update_attributes(inode, NULL, NULL, &refreshed);
		if (err)
			return err;
	}

	if (fc->flags & FUSE_DEFAULT_PERMISSIONS) {
		err = generic_permission(inode, mask, NULL);

		/* If permission is denied, try to refresh file
		   attributes.  This is also needed, because the root
		   node will at first have no permissions */
		if (err == -EACCES && !refreshed) {
			err = fuse_do_getattr(inode, NULL, NULL);
			if (!err)
				err = generic_permission(inode, mask, NULL);
		}

		/* Note: the opposite of the above test does not
		   exist.  So if permissions are revoked this won't be
		   noticed immediately, only after the attribute
		   timeout has expired */
	} else if (mask & MAY_ACCESS) {
		err = fuse_access(inode, mask);
	} else if ((mask & MAY_EXEC) && S_ISREG(inode->i_mode)) {
		if (!(inode->i_mode & S_IXUGO)) {
			if (refreshed)
				return -EACCES;

			err = fuse_do_getattr(inode, NULL, NULL);
			if (!err && !(inode->i_mode & S_IXUGO))
				return -EACCES;
		}
	}
	return err;
}