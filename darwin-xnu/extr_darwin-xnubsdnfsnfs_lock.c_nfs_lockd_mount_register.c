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
struct nfsmount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct nfsmount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_lock_mutex ; 
 int /*<<< orphan*/  nfs_lockd_mount_list ; 
 int /*<<< orphan*/  nfs_lockd_mounts ; 
 int /*<<< orphan*/  nm_ldlink ; 

void
nfs_lockd_mount_register(struct nfsmount *nmp)
{
	lck_mtx_lock(nfs_lock_mutex);
	TAILQ_INSERT_HEAD(&nfs_lockd_mount_list, nmp, nm_ldlink);
	nfs_lockd_mounts++;
	lck_mtx_unlock(nfs_lock_mutex);
}