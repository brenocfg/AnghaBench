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
typedef  int /*<<< orphan*/  vfs_context_t ;
struct nfsmount {scalar_t__ nm_vers; } ;
struct nfsbuf {int nb_error; int /*<<< orphan*/  nb_flags; int /*<<< orphan*/  nb_np; } ;
typedef  int /*<<< orphan*/  nfsnode_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  NB_ERROR ; 
 int NFSERR_DIRBUFDROPPED ; 
 struct nfsmount* NFSTONMP (int /*<<< orphan*/ ) ; 
 scalar_t__ NFS_VER4 ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nfs3_readdir_rpc (int /*<<< orphan*/ ,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 int nfs4_readdir_rpc (int /*<<< orphan*/ ,struct nfsbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 

int
nfs_buf_readdir(struct nfsbuf *bp, vfs_context_t ctx)
{
	nfsnode_t np = bp->nb_np;
	struct nfsmount *nmp = NFSTONMP(np);
	int error = 0;

	if (nfs_mount_gone(nmp))
		return (ENXIO);

	if (nmp->nm_vers < NFS_VER4)
		error = nfs3_readdir_rpc(np, bp, ctx);
	else
		error = nfs4_readdir_rpc(np, bp, ctx);

	if (error && (error != NFSERR_DIRBUFDROPPED)) {
		SET(bp->nb_flags, NB_ERROR);
		bp->nb_error = error;
	}
	return (error);
}