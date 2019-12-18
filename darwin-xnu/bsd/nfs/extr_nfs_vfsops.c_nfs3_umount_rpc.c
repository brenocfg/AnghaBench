#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {void* sin6_port; } ;
struct sockaddr_in {void* sin_port; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct nfsmount {scalar_t__ nm_vers; scalar_t__ nm_sotype; scalar_t__ nm_mountport; int /*<<< orphan*/  nm_mountp; TYPE_2__* nm_saddr; } ;
struct nfsm_chain {int /*<<< orphan*/ * nmc_mhead; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_4__ {int /*<<< orphan*/  sa_len; } ;
struct TYPE_3__ {char* f_mntfromname; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int /*<<< orphan*/  MNTUDP ; 
 scalar_t__ NFSX_UNSIGNED ; 
 scalar_t__ NFS_VER2 ; 
 scalar_t__ NM_OMFLAG (struct nfsmount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPCAUTH_SYS ; 
 int /*<<< orphan*/  RPCMNT_UMOUNT ; 
 scalar_t__ RPCMNT_VER1 ; 
 scalar_t__ RPCMNT_VER3 ; 
 int /*<<< orphan*/  RPCPROG_MNT ; 
 int /*<<< orphan*/  R_XID32 (int /*<<< orphan*/ ) ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  bcopy (TYPE_2__*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 void* htons (scalar_t__) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int nfs_aux_request (struct nfsmount*,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct nfsm_chain*) ; 
 int nfs_portmap_lookup (struct nfsmount*,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_name (int,struct nfsm_chain*,char*,int,struct nfsmount*) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,scalar_t__) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 scalar_t__ nfsm_rndup (int) ; 
 int nfsm_rpchead2 (struct nfsmount*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 
 scalar_t__ ntohs (void*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 TYPE_1__* vfs_statfs (int /*<<< orphan*/ ) ; 

void
nfs3_umount_rpc(struct nfsmount *nmp, vfs_context_t ctx, int timeo)
{
	int error = 0, slen, mntproto;
	thread_t thd = vfs_context_thread(ctx);
	kauth_cred_t cred = vfs_context_ucred(ctx);
	char *path;
	uint64_t xid = 0;
	struct nfsm_chain nmreq, nmrep;
	mbuf_t mreq;
	uint32_t mntvers, mntport;
	struct sockaddr_storage ss;
	struct sockaddr *saddr = (struct sockaddr*)&ss;

	if (!nmp->nm_saddr)
		return;

	nfsm_chain_null(&nmreq);
	nfsm_chain_null(&nmrep);

	mntvers = (nmp->nm_vers == NFS_VER2) ? RPCMNT_VER1 : RPCMNT_VER3;
	mntproto = (NM_OMFLAG(nmp, MNTUDP) || (nmp->nm_sotype == SOCK_DGRAM)) ? IPPROTO_UDP : IPPROTO_TCP;
	mntport = nmp->nm_mountport;

	bcopy(nmp->nm_saddr, saddr, min(sizeof(ss), nmp->nm_saddr->sa_len));
	if (saddr->sa_family == AF_INET)
		((struct sockaddr_in*)saddr)->sin_port = htons(mntport);
	else
		((struct sockaddr_in6*)saddr)->sin6_port = htons(mntport);

	while (!mntport) {
		error = nfs_portmap_lookup(nmp, ctx, saddr, NULL, RPCPROG_MNT, mntvers, mntproto, timeo);
  		nfsmout_if(error);
		if (saddr->sa_family == AF_INET)
			mntport = ntohs(((struct sockaddr_in*)saddr)->sin_port);
		else
			mntport = ntohs(((struct sockaddr_in6*)saddr)->sin6_port);
		/* if not found and mntvers > VER1, then retry with VER1 */
		if (!mntport) {
			if (mntvers > RPCMNT_VER1) {
				mntvers = RPCMNT_VER1;
			} else if (mntproto == IPPROTO_TCP) {
				mntproto = IPPROTO_UDP;
				mntvers = (nmp->nm_vers == NFS_VER2) ? RPCMNT_VER1 : RPCMNT_VER3;
			} else {
				break;
			}
			bcopy(nmp->nm_saddr, saddr, min(sizeof(ss), nmp->nm_saddr->sa_len));
		}
	}
	nfsmout_if(!mntport);

	/* MOUNT protocol UNMOUNT request */
	path = &vfs_statfs(nmp->nm_mountp)->f_mntfromname[0];
	while (*path && (*path != '/'))
		path++;
	slen = strlen(path);
	nfsm_chain_build_alloc_init(error, &nmreq, NFSX_UNSIGNED + nfsm_rndup(slen));
	nfsm_chain_add_name(error, &nmreq, path, slen, nmp);
	nfsm_chain_build_done(error, &nmreq);
	nfsmout_if(error);
	error = nfsm_rpchead2(nmp, (mntproto == IPPROTO_UDP) ? SOCK_DGRAM : SOCK_STREAM,
			RPCPROG_MNT, RPCMNT_VER1, RPCMNT_UMOUNT,
			RPCAUTH_SYS, cred, NULL, nmreq.nmc_mhead, &xid, &mreq);
	nfsmout_if(error);
	nmreq.nmc_mhead = NULL;
	error = nfs_aux_request(nmp, thd, saddr, NULL,
		((mntproto == IPPROTO_UDP) ? SOCK_DGRAM : SOCK_STREAM),
		mreq, R_XID32(xid), 1, timeo, &nmrep);
nfsmout:
	nfsm_chain_cleanup(&nmreq);
	nfsm_chain_cleanup(&nmrep);
}