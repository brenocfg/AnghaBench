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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {void* sin6_port; } ;
struct sockaddr_in {void* sin_port; } ;
struct sockaddr {scalar_t__ sa_family; int /*<<< orphan*/  sa_len; } ;
struct nfsmount {scalar_t__ nm_mountport; } ;
struct nfsm_chain {int /*<<< orphan*/ * nmc_mhead; } ;
struct nfs_sec {int /*<<< orphan*/  count; int /*<<< orphan*/ * flavors; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int /*<<< orphan*/  fhandle_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EPROGUNAVAIL ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int /*<<< orphan*/  MNTUDP ; 
 scalar_t__ NFSX_UNSIGNED ; 
 int NFS_VER2 ; 
 scalar_t__ NM_OMFLAG (struct nfsmount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NX_MAX_SEC_FLAVORS ; 
 int /*<<< orphan*/  RPCAUTH_SYS ; 
 int /*<<< orphan*/  RPCMNT_MOUNT ; 
 int RPCMNT_VER1 ; 
 int RPCMNT_VER3 ; 
 int /*<<< orphan*/  RPCPROG_MNT ; 
 int /*<<< orphan*/  R_XID32 (int /*<<< orphan*/ ) ; 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  bcopy (struct sockaddr*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 void* htons (scalar_t__) ; 
 int /*<<< orphan*/  min (int,int /*<<< orphan*/ ) ; 
 int nfs_aux_request (struct nfsmount*,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct nfsm_chain*) ; 
 int nfs_portmap_lookup (struct nfsmount*,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_name (int,struct nfsm_chain*,char*,int,struct nfsmount*) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,scalar_t__) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_get_fh (int,struct nfsm_chain*,int,int /*<<< orphan*/ *) ; 
 int nfsm_chain_get_secinfo (struct nfsm_chain*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 scalar_t__ nfsm_rndup (int) ; 
 int nfsm_rpchead2 (struct nfsmount*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 
 int ntohs (void*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  vfs_context_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 

int
nfs3_mount_rpc(struct nfsmount *nmp, struct sockaddr *sa, int sotype, int nfsvers, char *path, vfs_context_t ctx, int timeo, fhandle_t *fh, struct nfs_sec *sec)
{
	int error = 0, slen, mntproto;
	thread_t thd = vfs_context_thread(ctx);
	kauth_cred_t cred = vfs_context_ucred(ctx);
	uint64_t xid = 0;
	struct nfsm_chain nmreq, nmrep;
	mbuf_t mreq;
	uint32_t mntvers, mntport, val;
	struct sockaddr_storage ss;
	struct sockaddr *saddr = (struct sockaddr*)&ss;

	nfsm_chain_null(&nmreq);
	nfsm_chain_null(&nmrep);

	mntvers = (nfsvers == NFS_VER2) ? RPCMNT_VER1 : RPCMNT_VER3;
	mntproto = (NM_OMFLAG(nmp, MNTUDP) || (sotype == SOCK_DGRAM)) ? IPPROTO_UDP : IPPROTO_TCP;
	sec->count = 0;

	bcopy(sa, saddr, min(sizeof(ss), sa->sa_len));
	if (saddr->sa_family == AF_INET) {
		if (nmp->nm_mountport)
			((struct sockaddr_in*)saddr)->sin_port = htons(nmp->nm_mountport);
		mntport = ntohs(((struct sockaddr_in*)saddr)->sin_port);
	} else {
		if (nmp->nm_mountport)
			((struct sockaddr_in6*)saddr)->sin6_port = htons(nmp->nm_mountport);
		mntport = ntohs(((struct sockaddr_in6*)saddr)->sin6_port);
	}

	while (!mntport) {
		error = nfs_portmap_lookup(nmp, ctx, saddr, NULL, RPCPROG_MNT, mntvers, mntproto, timeo);
		nfsmout_if(error);
		if (saddr->sa_family == AF_INET)
			mntport = ntohs(((struct sockaddr_in*)saddr)->sin_port);
		else
			mntport = ntohs(((struct sockaddr_in6*)saddr)->sin6_port);
		if (!mntport) {
			/* if not found and TCP, then retry with UDP */
			if (mntproto == IPPROTO_UDP) {
				error = EPROGUNAVAIL;
				break;
			}
			mntproto = IPPROTO_UDP;
			bcopy(sa, saddr, min(sizeof(ss), sa->sa_len));
		}
	}
	nfsmout_if(error || !mntport);

	/* MOUNT protocol MOUNT request */
	slen = strlen(path);
	nfsm_chain_build_alloc_init(error, &nmreq, NFSX_UNSIGNED + nfsm_rndup(slen));
	nfsm_chain_add_name(error, &nmreq, path, slen, nmp);
	nfsm_chain_build_done(error, &nmreq);
	nfsmout_if(error);
	error = nfsm_rpchead2(nmp, (mntproto == IPPROTO_UDP) ? SOCK_DGRAM : SOCK_STREAM,
			RPCPROG_MNT, mntvers, RPCMNT_MOUNT,
			RPCAUTH_SYS, cred, NULL, nmreq.nmc_mhead, &xid, &mreq);
	nfsmout_if(error);
	nmreq.nmc_mhead = NULL;
	error = nfs_aux_request(nmp, thd, saddr, NULL,
			((mntproto == IPPROTO_UDP) ? SOCK_DGRAM : SOCK_STREAM),
			mreq, R_XID32(xid), 1, timeo, &nmrep);
	nfsmout_if(error);
	nfsm_chain_get_32(error, &nmrep, val);
	if (!error && val)
		error = val;
	nfsm_chain_get_fh(error, &nmrep, nfsvers, fh);
	if (!error && (nfsvers > NFS_VER2)) {
		sec->count = NX_MAX_SEC_FLAVORS;
		error = nfsm_chain_get_secinfo(&nmrep, &sec->flavors[0], &sec->count);
	}
nfsmout:
	nfsm_chain_cleanup(&nmreq);
	nfsm_chain_cleanup(&nmrep);
	return (error);
}