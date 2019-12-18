#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct dentry {int d_flags; TYPE_4__* d_sb; int /*<<< orphan*/ * d_inode; TYPE_3__ d_name; TYPE_2__* d_parent; } ;
struct TYPE_8__ {int s_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_1__ d_name; } ;

/* Variables and functions */
 int DCACHE_NFSFS_RENAMED ; 
 int MS_ACTIVE ; 
 scalar_t__ NFS_STALE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nfs_dentry_delete(struct dentry *dentry)
{
	dfprintk(VFS, "NFS: dentry_delete(%s/%s, %x)\n",
		dentry->d_parent->d_name.name, dentry->d_name.name,
		dentry->d_flags);

	/* Unhash any dentry with a stale inode */
	if (dentry->d_inode != NULL && NFS_STALE(dentry->d_inode))
		return 1;

	if (dentry->d_flags & DCACHE_NFSFS_RENAMED) {
		/* Unhash it, so that ->d_iput() would be called */
		return 1;
	}
	if (!(dentry->d_sb->s_flags & MS_ACTIVE)) {
		/* Unhash it, so that ancestors of killed async unlink
		 * files will be cleaned up during umount */
		return 1;
	}
	return 0;

}