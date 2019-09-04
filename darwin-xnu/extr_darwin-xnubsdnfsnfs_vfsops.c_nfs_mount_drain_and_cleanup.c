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
struct nfsmount {scalar_t__ nm_ref; int /*<<< orphan*/  nm_lock; int /*<<< orphan*/  nm_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSSTA_MOUNT_DRAIN ; 
 scalar_t__ PZERO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_mount_cleanup (struct nfsmount*) ; 

void
nfs_mount_drain_and_cleanup(struct nfsmount *nmp)
{
	lck_mtx_lock(&nmp->nm_lock);
	nmp->nm_state |= NFSSTA_MOUNT_DRAIN;
	while (nmp->nm_ref > 0) {
		msleep(&nmp->nm_ref, &nmp->nm_lock, PZERO-1, "nfs_mount_drain", NULL);
	}
	assert(nmp->nm_ref == 0);
	lck_mtx_unlock(&nmp->nm_lock);
	nfs_mount_cleanup(nmp);
}