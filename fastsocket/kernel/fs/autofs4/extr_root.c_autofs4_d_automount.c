#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct path {struct dentry* dentry; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {TYPE_2__* d_inode; TYPE_1__ d_name; int /*<<< orphan*/  d_sb; } ;
struct autofs_sb_info {int version; int /*<<< orphan*/  fs_lock; } ;
struct autofs_info {int flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int AUTOFS_INF_PENDING ; 
 int /*<<< orphan*/  DPRINTK (char*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ENOENT ; 
 struct vfsmount* ERR_PTR (int) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 struct autofs_info* autofs4_dentry_ino (struct dentry*) ; 
 int autofs4_mount_wait (struct dentry*) ; 
 struct dentry* autofs4_mountpoint_changed (struct path*) ; 
 scalar_t__ autofs4_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs4_sbi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_mountpoint (struct dentry*) ; 
 int do_expire_wait (struct dentry*) ; 
 scalar_t__ have_submounts (struct dentry*) ; 
 int /*<<< orphan*/  simple_empty (struct dentry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct vfsmount *autofs4_d_automount(struct path *path)
{
	struct dentry *dentry = path->dentry;
	struct autofs_sb_info *sbi = autofs4_sbi(dentry->d_sb);
	struct autofs_info *ino = autofs4_dentry_ino(dentry);
	int status;

	DPRINTK("dentry=%p %.*s",
		dentry, dentry->d_name.len, dentry->d_name.name);

	/* The daemon never triggers a mount. */
	if (autofs4_oz_mode(sbi))
		return NULL;

	/*
	 * If an expire request is pending everyone must wait.
	 * If the expire fails we're still mounted so continue
	 * the follow and return. A return of -EAGAIN (which only
	 * happens with indirect mounts) means the expire completed
	 * and the directory was removed, so just go ahead and try
	 * the mount.
	 */
	status = do_expire_wait(dentry);
	if (status && status != -EAGAIN)
		return NULL;

	/* Callback to the daemon to perform the mount or wait */
	spin_lock(&sbi->fs_lock);
	if (ino->flags & AUTOFS_INF_PENDING) {
		spin_unlock(&sbi->fs_lock);
		status = autofs4_mount_wait(dentry);
		if (status)
			return ERR_PTR(status);
		goto done;
	}

	/*
	 * If the dentry is a symlink it's equivalent to a directory
	 * having d_mountpoint() true, so there's no need to call back
	 * to the daemon.
	 */
	if (dentry->d_inode && S_ISLNK(dentry->d_inode->i_mode)) {
		spin_unlock(&sbi->fs_lock);
		goto done;
	}

	if (!d_mountpoint(dentry)) {
		/*
		 * It's possible that user space hasn't removed directories
		 * after umounting a rootless multi-mount, although it
		 * should. For v5 have_submounts() is sufficient to handle
		 * this because the leaves of the directory tree under the
		 * mount never trigger mounts themselves (they have an autofs
		 * trigger mount mounted on them). But v4 pseudo direct mounts
		 * do need the leaves to to trigger mounts. In this case we
		 * have no choice but to use the list_empty() check and
		 * require user space behave.
		 */
		if (sbi->version > 4) {
			if (have_submounts(dentry)) {
				spin_unlock(&sbi->fs_lock);
				goto done;
			}
		} else {
			if (!simple_empty(dentry)) {
				spin_unlock(&sbi->fs_lock);
				goto done;
			}
		}
		ino->flags |= AUTOFS_INF_PENDING;
		spin_unlock(&sbi->fs_lock);
		status = autofs4_mount_wait(dentry);
		spin_lock(&sbi->fs_lock);
		ino->flags &= ~AUTOFS_INF_PENDING;
		if (status) {
			spin_unlock(&sbi->fs_lock);
			return ERR_PTR(status);
		}
	}
	spin_unlock(&sbi->fs_lock);
done:
	/* Mount succeeded, check if we ended up with a new dentry */
	dentry = autofs4_mountpoint_changed(path);
	if (!dentry)
		return ERR_PTR(-ENOENT);

	return NULL;
}