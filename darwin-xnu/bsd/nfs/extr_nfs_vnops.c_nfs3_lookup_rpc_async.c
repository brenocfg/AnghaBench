#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
struct nfsreq {int dummy; } ;
struct nfsmount {int nm_vers; } ;
struct nfsm_chain {int dummy; } ;
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_5__ {int /*<<< orphan*/  n_fhsize; int /*<<< orphan*/  n_fhp; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  NFSPROC_LOOKUP ; 
 struct nfsmount* NFSTONMP (TYPE_1__*) ; 
 scalar_t__ NFSX_FH (int) ; 
 scalar_t__ NFSX_UNSIGNED ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int nfs_request_async (TYPE_1__*,int /*<<< orphan*/ *,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfsreq**) ; 
 int /*<<< orphan*/  nfsm_chain_add_fh (int,struct nfsm_chain*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_name (int,struct nfsm_chain*,char*,int,struct nfsmount*) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,scalar_t__) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 scalar_t__ nfsm_rndup (int) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 

int
nfs3_lookup_rpc_async(
	nfsnode_t dnp,
	char *name,
	int namelen,
	vfs_context_t ctx,
	struct nfsreq **reqp)
{
	struct nfsmount *nmp;
	struct nfsm_chain nmreq;
	int error = 0, nfsvers;

	nmp = NFSTONMP(dnp);
	if (nfs_mount_gone(nmp))
		return (ENXIO);
	nfsvers = nmp->nm_vers;

	nfsm_chain_null(&nmreq);

	nfsm_chain_build_alloc_init(error, &nmreq,
		NFSX_FH(nfsvers) + NFSX_UNSIGNED + nfsm_rndup(namelen));
	nfsm_chain_add_fh(error, &nmreq, nfsvers, dnp->n_fhp, dnp->n_fhsize);
	nfsm_chain_add_name(error, &nmreq, name, namelen, nmp);
	nfsm_chain_build_done(error, &nmreq);
	nfsmout_if(error);
	error = nfs_request_async(dnp, NULL, &nmreq, NFSPROC_LOOKUP,
			vfs_context_thread(ctx), vfs_context_ucred(ctx), NULL, 0, NULL, reqp);
nfsmout:
	nfsm_chain_cleanup(&nmreq);
	return (error);
}