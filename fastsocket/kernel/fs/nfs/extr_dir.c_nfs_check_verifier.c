#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_time; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 scalar_t__ IS_ROOT (struct dentry*) ; 
 int NFS_MOUNT_LOOKUP_CACHE_NONE ; 
 TYPE_1__* NFS_SERVER (struct inode*) ; 
 scalar_t__ nfs_revalidate_inode (TYPE_1__*,struct inode*) ; 
 int /*<<< orphan*/  nfs_verify_change_attribute (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs_check_verifier(struct inode *dir, struct dentry *dentry)
{
	if (IS_ROOT(dentry))
		return 1;
	if (NFS_SERVER(dir)->flags & NFS_MOUNT_LOOKUP_CACHE_NONE)
		return 0;
	if (!nfs_verify_change_attribute(dir, dentry->d_time))
		return 0;
	/* Revalidate nfsi->cache_change_attribute before we declare a match */
	if (nfs_revalidate_inode(NFS_SERVER(dir), dir) < 0)
		return 0;
	if (!nfs_verify_change_attribute(dir, dentry->d_time))
		return 0;
	return 1;
}