#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file_lock {int dummy; } ;
struct file {TYPE_1__* f_mapping; } ;
struct TYPE_7__ {int (* lock ) (struct file*,int,struct file_lock*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  time_delta; } ;
struct TYPE_5__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_READ ; 
 TYPE_4__* NFS_PROTO (struct inode*) ; 
 TYPE_2__* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  __nfs_revalidate_inode (TYPE_2__*,struct inode*) ; 
 int do_vfs_lock (struct file*,struct file_lock*) ; 
 scalar_t__ is_time_granular (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_have_delegation (struct inode*,int /*<<< orphan*/ ) ; 
 int nfs_sync_mapping (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_zap_caches (struct inode*) ; 
 int stub1 (struct file*,int,struct file_lock*) ; 

__attribute__((used)) static int
do_setlk(struct file *filp, int cmd, struct file_lock *fl, int is_local)
{
	struct inode *inode = filp->f_mapping->host;
	int status;

	/*
	 * Flush all pending writes before doing anything
	 * with locks..
	 */
	status = nfs_sync_mapping(filp->f_mapping);
	if (status != 0)
		goto out;

	/*
	 * Use local locking if mounted with "-onolock" or with appropriate
	 * "-olocal_lock="
	 */
	if (!is_local)
		status = NFS_PROTO(inode)->lock(filp, cmd, fl);
	else
		status = do_vfs_lock(filp, fl);
	if (status < 0)
		goto out;

	/*
	 * Revalidate the cache if the server has time stamps granular
	 * enough to detect subsecond changes.  Otherwise, clear the
	 * cache to prevent missing any changes.
	 *
	 * This makes locking act as a cache coherency point.
	 */
	nfs_sync_mapping(filp->f_mapping);
	if (!nfs_have_delegation(inode, FMODE_READ)) {
		if (is_time_granular(&NFS_SERVER(inode)->time_delta))
			__nfs_revalidate_inode(NFS_SERVER(inode), inode);
		else
			nfs_zap_caches(inode);
	}
out:
	return status;
}