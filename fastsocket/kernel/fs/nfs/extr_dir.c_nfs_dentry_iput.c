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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct dentry {int d_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  cache_validity; } ;

/* Variables and functions */
 int DCACHE_NFSFS_RENAMED ; 
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_INVALID_DATA ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  nfs_complete_unlink (struct dentry*,struct inode*) ; 

__attribute__((used)) static void nfs_dentry_iput(struct dentry *dentry, struct inode *inode)
{
	if (S_ISDIR(inode->i_mode))
		/* drop any readdir cache as it could easily be old */
		NFS_I(inode)->cache_validity |= NFS_INO_INVALID_DATA;

	if (dentry->d_flags & DCACHE_NFSFS_RENAMED) {
		drop_nlink(inode);
		nfs_complete_unlink(dentry, inode);
	}
	iput(inode);
}