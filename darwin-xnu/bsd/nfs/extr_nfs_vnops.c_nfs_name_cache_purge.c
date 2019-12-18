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
struct componentname {int dummy; } ;
typedef  int /*<<< orphan*/  nfsnode_t ;

/* Variables and functions */
 struct nfsmount* NFSTONMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSTOV (int /*<<< orphan*/ ) ; 
 scalar_t__ NFS_VER2 ; 
 scalar_t__ NMFLAG (struct nfsmount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDIRPLUS ; 
 int /*<<< orphan*/  cache_purge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_dir_buf_cache_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct componentname*,int /*<<< orphan*/ ,int) ; 

void
nfs_name_cache_purge(nfsnode_t dnp, nfsnode_t np, struct componentname *cnp, vfs_context_t ctx)
{
	struct nfsmount *nmp = NFSTONMP(dnp);

	cache_purge(NFSTOV(np));
	if (nmp && (nmp->nm_vers > NFS_VER2) && NMFLAG(nmp, RDIRPLUS))
		nfs_dir_buf_cache_lookup(dnp, NULL, cnp, ctx, 1);
}