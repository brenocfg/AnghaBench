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
struct vfsmount {int mnt_flags; } ;
struct kstat {int /*<<< orphan*/  ino; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_mapping; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_2__ {int cache_validity; } ;

/* Variables and functions */
 int MNT_NOATIME ; 
 int MNT_NODIRATIME ; 
 int /*<<< orphan*/  NFS_FILEID (struct inode*) ; 
 TYPE_1__* NFS_I (struct inode*) ; 
 int NFS_INO_INVALID_ATIME ; 
 int /*<<< orphan*/  NFS_SERVER (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int __nfs_revalidate_inode (int /*<<< orphan*/ ,struct inode*) ; 
 int filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 
 int /*<<< orphan*/  nfs_compat_user_ino64 (int /*<<< orphan*/ ) ; 
 int nfs_revalidate_inode (int /*<<< orphan*/ ,struct inode*) ; 

int nfs_getattr(struct vfsmount *mnt, struct dentry *dentry, struct kstat *stat)
{
	struct inode *inode = dentry->d_inode;
	int need_atime = NFS_I(inode)->cache_validity & NFS_INO_INVALID_ATIME;
	int err;

	/* Flush out writes to the server in order to update c/mtime.  */
	if (S_ISREG(inode->i_mode)) {
		err = filemap_write_and_wait(inode->i_mapping);
		if (err)
			goto out;
	}

	/*
	 * We may force a getattr if the user cares about atime.
	 *
	 * Note that we only have to check the vfsmount flags here:
	 *  - NFS always sets S_NOATIME by so checking it would give a
	 *    bogus result
	 *  - NFS never sets MS_NOATIME or MS_NODIRATIME so there is
	 *    no point in checking those.
	 */
 	if ((mnt->mnt_flags & MNT_NOATIME) ||
 	    ((mnt->mnt_flags & MNT_NODIRATIME) && S_ISDIR(inode->i_mode)))
		need_atime = 0;

	if (need_atime)
		err = __nfs_revalidate_inode(NFS_SERVER(inode), inode);
	else
		err = nfs_revalidate_inode(NFS_SERVER(inode), inode);
	if (!err) {
		generic_fillattr(inode, stat);
		stat->ino = nfs_compat_user_ino64(NFS_FILEID(inode));
	}
out:
	return err;
}