#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nfsmount {scalar_t__ nm_vers; scalar_t__ nm_fh; int /*<<< orphan*/  nm_lock; scalar_t__ nm_args; scalar_t__ nm_sprinc; scalar_t__ nm_principal; scalar_t__ nm_realm; int /*<<< orphan*/  nm_locations; int /*<<< orphan*/  nm_mcred; scalar_t__ nm_rqsaddr; scalar_t__ nm_saddr; scalar_t__ nm_state; scalar_t__ nm_ref; TYPE_2__* nm_mountp; scalar_t__ nm_sockflags; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_5__ {scalar_t__ mnt_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  f_mntonname; int /*<<< orphan*/  f_mntfromname; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FREE_ZONE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NFSMNT ; 
 int /*<<< orphan*/  M_SONAME ; 
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ NFS_VER4 ; 
 int /*<<< orphan*/  NFS_VFS_DBG (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_fs_locations_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_mount_grp ; 
 int /*<<< orphan*/  nfs_mount_zombie (struct nfsmount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vfs_setfsprivate (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* vfs_statfs (TYPE_2__*) ; 
 int /*<<< orphan*/  xb_free (scalar_t__) ; 

void
nfs_mount_cleanup(struct nfsmount *nmp)
{
	if (!nmp)
		return;

	nfs_mount_zombie(nmp, 0);

	NFS_VFS_DBG("Unmounting %s from %s\n",
		    vfs_statfs(nmp->nm_mountp)->f_mntfromname,
		    vfs_statfs(nmp->nm_mountp)->f_mntonname);
	NFS_VFS_DBG("nfs state = 0x%8.8x\n", nmp->nm_state);
	NFS_VFS_DBG("nfs socket flags = 0x%8.8x\n", nmp->nm_sockflags);
	NFS_VFS_DBG("nfs mount ref count is %d\n", nmp->nm_ref);
	NFS_VFS_DBG("mount ref count is %d\n", nmp->nm_mountp->mnt_count);
	
	if (nmp->nm_mountp)
		vfs_setfsprivate(nmp->nm_mountp, NULL);

	lck_mtx_lock(&nmp->nm_lock);
	if (nmp->nm_ref)
		panic("Some one has grabbed a ref %d state flags = 0x%8.8x\n", nmp->nm_ref, nmp->nm_state);

	if (nmp->nm_saddr)
		FREE(nmp->nm_saddr, M_SONAME);
	if ((nmp->nm_vers < NFS_VER4) && nmp->nm_rqsaddr)
		FREE(nmp->nm_rqsaddr, M_SONAME);

	if (IS_VALID_CRED(nmp->nm_mcred))
		kauth_cred_unref(&nmp->nm_mcred);

	nfs_fs_locations_cleanup(&nmp->nm_locations);

	if (nmp->nm_realm)
		FREE(nmp->nm_realm, M_TEMP);
	if (nmp->nm_principal)
		FREE(nmp->nm_principal, M_TEMP);
	if (nmp->nm_sprinc)
		FREE(nmp->nm_sprinc, M_TEMP);
	
	if (nmp->nm_args)
		xb_free(nmp->nm_args);

	lck_mtx_unlock(&nmp->nm_lock);
	
	lck_mtx_destroy(&nmp->nm_lock, nfs_mount_grp);
	if (nmp->nm_fh)
		FREE(nmp->nm_fh, M_TEMP);
	FREE_ZONE((caddr_t)nmp, sizeof (struct nfsmount), M_NFSMNT);
}