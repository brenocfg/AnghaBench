#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uaddr ;
typedef  int /*<<< orphan*/  thread_t ;
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct nfsmount {int /*<<< orphan*/  nm_lock; int /*<<< orphan*/  nm_fsattr; int /*<<< orphan*/  nm_mountp; TYPE_1__* nm_dnp; int /*<<< orphan*/  nm_vers; int /*<<< orphan*/  nm_minor_vers; int /*<<< orphan*/  nm_state; int /*<<< orphan*/  nm_clientid; int /*<<< orphan*/  nm_cbid; TYPE_3__* nm_nso; TYPE_2__* nm_longid; int /*<<< orphan*/  nm_mounttime; int /*<<< orphan*/  nm_mcred; } ;
struct nfsm_chain {int dummy; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int /*<<< orphan*/  raddr ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int in_port_t ;
struct TYPE_6__ {int /*<<< orphan*/  nso_so; } ;
struct TYPE_5__ {int /*<<< orphan*/  nci_idlen; int /*<<< orphan*/  nci_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  n_fhsize; int /*<<< orphan*/  n_fhp; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  EPROTO ; 
 scalar_t__ IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 int MAX_IPv6_STR_LEN ; 
 int /*<<< orphan*/  NFS4_CALLBACK_PROG ; 
 int /*<<< orphan*/  NFS4_PER_FS_ATTRIBUTES (int /*<<< orphan*/ *) ; 
 int NFSERR_CLID_INUSE ; 
 int /*<<< orphan*/  NFSPROC4_COMPOUND ; 
 int /*<<< orphan*/  NFSSTA_CLIENTID ; 
 int NFSX_UNSIGNED ; 
 int NFS_ATTR_BITMAP_LEN ; 
 int /*<<< orphan*/  NFS_CLEAR_ATTRIBUTES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFS_OP_GETATTR ; 
 int /*<<< orphan*/  NFS_OP_PUTFH ; 
 int /*<<< orphan*/  NFS_OP_SETCLIENTID ; 
 int /*<<< orphan*/  NFS_OP_SETCLIENTID_CONFIRM ; 
 int /*<<< orphan*/  NMFLAG (struct nfsmount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOCALLBACK ; 
 int /*<<< orphan*/  R_SETUP ; 
 int /*<<< orphan*/  current_thread () ; 
 char* inet_ntop (scalar_t__,void*,char*,int) ; 
 int /*<<< orphan*/  kauth_cred_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int nfs4_cb_port ; 
 int nfs4_cb_port6 ; 
 int nfs4_init_clientid (struct nfsmount*) ; 
 int nfs4_parsefattr (struct nfsm_chain*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nfs_request2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nfsm_chain*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nfsm_assert (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_32 (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_64 (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_bitmap (int,struct nfsm_chain*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_compound_header (int,struct nfsm_chain*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfsm_chain_add_fh (int,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_opaque (int,struct nfsm_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_add_string (int,struct nfsm_chain*,char*,int) ; 
 int /*<<< orphan*/  nfsm_chain_build_alloc_init (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_build_done (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_cleanup (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_get_32 (int,struct nfsm_chain*,int) ; 
 int /*<<< orphan*/  nfsm_chain_get_64 (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_null (struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsm_chain_op_check (int,struct nfsm_chain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsm_chain_skip_tag (int,struct nfsm_chain*) ; 
 int /*<<< orphan*/  nfsmout_if (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int snprintf (char*,int,char*,char*,int,int) ; 
 int /*<<< orphan*/  sock_getsockname (int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  vfs_context_kernel () ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 

int
nfs4_setclientid(struct nfsmount *nmp)
{
	uint64_t verifier, xid;
	int error = 0, status, numops;
	uint32_t bitmap[NFS_ATTR_BITMAP_LEN];
	thread_t thd;
	kauth_cred_t cred;
	struct nfsm_chain nmreq, nmrep;
	struct sockaddr_storage ss;
	void *sinaddr = NULL;
	char raddr[MAX_IPv6_STR_LEN];
	char uaddr[MAX_IPv6_STR_LEN+16];
	int ualen = 0;
	in_port_t port;

	thd = current_thread();
	cred = IS_VALID_CRED(nmp->nm_mcred) ? nmp->nm_mcred : vfs_context_ucred(vfs_context_kernel());
	kauth_cred_ref(cred);

	nfsm_chain_null(&nmreq);
	nfsm_chain_null(&nmrep);

	if (!nmp->nm_longid)
		error = nfs4_init_clientid(nmp);

	// SETCLIENTID
	numops = 1;
	nfsm_chain_build_alloc_init(error, &nmreq, 14 * NFSX_UNSIGNED + nmp->nm_longid->nci_idlen);
	nfsm_chain_add_compound_header(error, &nmreq, "setclid", nmp->nm_minor_vers, numops);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_SETCLIENTID);
	/* nfs_client_id4  client; */
	nfsm_chain_add_64(error, &nmreq, nmp->nm_mounttime);
	nfsm_chain_add_32(error, &nmreq, nmp->nm_longid->nci_idlen);
	nfsm_chain_add_opaque(error, &nmreq, nmp->nm_longid->nci_id, nmp->nm_longid->nci_idlen);
	nfsmout_if(error);
	/* cb_client4      callback; */
	if (!NMFLAG(nmp, NOCALLBACK) && nmp->nm_cbid && nfs4_cb_port &&
	    !sock_getsockname(nmp->nm_nso->nso_so, (struct sockaddr*)&ss, sizeof(ss))) {
		if (ss.ss_family == AF_INET) {
			sinaddr = &((struct sockaddr_in*)&ss)->sin_addr;
			port = nfs4_cb_port;
		} else if (ss.ss_family == AF_INET6) {
			sinaddr = &((struct sockaddr_in6*)&ss)->sin6_addr;
			port = nfs4_cb_port6;
		}
		if (sinaddr && port && (inet_ntop(ss.ss_family, sinaddr, raddr, sizeof(raddr)) == raddr)) {
			/* assemble r_addr = universal address (nmp->nm_nso->nso_so source IP addr + port) */
			ualen = snprintf(uaddr, sizeof(uaddr), "%s.%d.%d", raddr,
					((port >> 8) & 0xff),
					(port & 0xff));
			/* make sure it fit, give up if it didn't */
			if (ualen >= (int)sizeof(uaddr))
				ualen = 0;
		}
	}
	if (ualen > 0) {
		/* add callback info */
		nfsm_chain_add_32(error, &nmreq, NFS4_CALLBACK_PROG); /* callback program */
		if (ss.ss_family == AF_INET)
			nfsm_chain_add_string(error, &nmreq, "tcp", 3); /* callback r_netid */
		else if (ss.ss_family == AF_INET6)
			nfsm_chain_add_string(error, &nmreq, "tcp6", 4); /* callback r_netid */
		nfsm_chain_add_string(error, &nmreq, uaddr, ualen); /* callback r_addr */
		nfsm_chain_add_32(error, &nmreq, nmp->nm_cbid); /* callback_ident */
	} else {
		/* don't provide valid callback info */
		nfsm_chain_add_32(error, &nmreq, 0); /* callback program */
		nfsm_chain_add_string(error, &nmreq, "", 0); /* callback r_netid */
		nfsm_chain_add_string(error, &nmreq, "", 0); /* callback r_addr */
		nfsm_chain_add_32(error, &nmreq, 0); /* callback_ident */
	}
	nfsm_chain_build_done(error, &nmreq);
	nfsm_assert(error, (numops == 0), EPROTO);
	nfsmout_if(error);
	error = nfs_request2(NULL, nmp->nm_mountp, &nmreq, NFSPROC4_COMPOUND, thd, cred, NULL, R_SETUP, &nmrep, &xid, &status);
	nfsm_chain_skip_tag(error, &nmrep);
	nfsm_chain_get_32(error, &nmrep, numops);
	if (!error && (numops != 1) && status)
		error = status;
	nfsm_chain_op_check(error, &nmrep, NFS_OP_SETCLIENTID);
	if (error == NFSERR_CLID_INUSE)
		printf("nfs4_setclientid: client ID in use?\n");
	nfsmout_if(error);
	nfsm_chain_get_64(error, &nmrep, nmp->nm_clientid);
	nfsm_chain_get_64(error, &nmrep, verifier);
	nfsm_chain_cleanup(&nmreq);
	nfsm_chain_cleanup(&nmrep);

	// SETCLIENTID_CONFIRM
	numops = 1;
	nfsm_chain_build_alloc_init(error, &nmreq, 15 * NFSX_UNSIGNED);
	nfsm_chain_add_compound_header(error, &nmreq, "setclid_conf", nmp->nm_minor_vers, numops);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_SETCLIENTID_CONFIRM);
	nfsm_chain_add_64(error, &nmreq, nmp->nm_clientid);
	nfsm_chain_add_64(error, &nmreq, verifier);
	nfsm_chain_build_done(error, &nmreq);
	nfsm_assert(error, (numops == 0), EPROTO);
	nfsmout_if(error);
	error = nfs_request2(NULL, nmp->nm_mountp, &nmreq, NFSPROC4_COMPOUND, thd, cred, NULL, R_SETUP, &nmrep, &xid, &status);
	nfsm_chain_skip_tag(error, &nmrep);
	nfsm_chain_get_32(error, &nmrep, numops);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_SETCLIENTID_CONFIRM);
	if (error)
		printf("nfs4_setclientid: confirm error %d\n", error);
	lck_mtx_lock(&nmp->nm_lock);
	if (!error)
		nmp->nm_state |= NFSSTA_CLIENTID;
	lck_mtx_unlock(&nmp->nm_lock);

	nfsmout_if(error || !nmp->nm_dnp);

	/* take the opportunity to refresh fs attributes too */
	// PUTFH, GETATTR(FS)
	numops = 2;
	nfsm_chain_build_alloc_init(error, &nmreq, 23 * NFSX_UNSIGNED);
	nfsm_chain_add_compound_header(error, &nmreq, "setclid_attr", nmp->nm_minor_vers, numops);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_PUTFH);
	nfsm_chain_add_fh(error, &nmreq, nmp->nm_vers, nmp->nm_dnp->n_fhp, nmp->nm_dnp->n_fhsize);
	numops--;
	nfsm_chain_add_32(error, &nmreq, NFS_OP_GETATTR);
	NFS_CLEAR_ATTRIBUTES(bitmap);
	NFS4_PER_FS_ATTRIBUTES(bitmap);
	nfsm_chain_add_bitmap(error, &nmreq, bitmap, NFS_ATTR_BITMAP_LEN);
	nfsm_chain_build_done(error, &nmreq);
	nfsm_assert(error, (numops == 0), EPROTO);
	nfsmout_if(error);
	error = nfs_request2(NULL, nmp->nm_mountp, &nmreq, NFSPROC4_COMPOUND, thd, cred, NULL, R_SETUP, &nmrep, &xid, &status);
	nfsm_chain_skip_tag(error, &nmrep);
	nfsm_chain_get_32(error, &nmrep, numops);
	lck_mtx_lock(&nmp->nm_lock);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_PUTFH);
	nfsm_chain_op_check(error, &nmrep, NFS_OP_GETATTR);
	if (!error)
		error = nfs4_parsefattr(&nmrep, &nmp->nm_fsattr, NULL, NULL, NULL, NULL);
	lck_mtx_unlock(&nmp->nm_lock);
	if (error)  /* ignore any error from the getattr */
		error = 0;
nfsmout:
	nfsm_chain_cleanup(&nmreq);
	nfsm_chain_cleanup(&nmrep);
	kauth_cred_unref(&cred);
	if (error)
		printf("nfs4_setclientid failed, %d\n", error);
	return (error);
}