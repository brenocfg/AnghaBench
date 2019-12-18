#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xdr_netobj {int dummy; } ;
struct svc_rqst {int /*<<< orphan*/  rq_cred; int /*<<< orphan*/  rq_flavor; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cb_work; } ;
struct nfs4_client {int /*<<< orphan*/ * cl_cb_session; int /*<<< orphan*/  cl_cred; int /*<<< orphan*/  cl_flavor; int /*<<< orphan*/  cl_addr; int /*<<< orphan*/  cl_cb_waitq; int /*<<< orphan*/  cl_cb_slot_busy; int /*<<< orphan*/  cl_time; TYPE_1__ cl_cb_null; int /*<<< orphan*/  cl_lock; int /*<<< orphan*/  cl_lru; int /*<<< orphan*/  cl_delegations; int /*<<< orphan*/  cl_openowners; int /*<<< orphan*/  cl_strhash; int /*<<< orphan*/  cl_idhash; int /*<<< orphan*/  cl_cb_set; int /*<<< orphan*/  cl_refcount; int /*<<< orphan*/  cl_recdir; int /*<<< orphan*/ * cl_principal; int /*<<< orphan*/  cl_sessions; } ;
typedef  int /*<<< orphan*/  nfs4_verifier ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HEXDIR_LEN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nfs4_client* alloc_client (struct xdr_netobj) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_cred (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_verf (struct nfs4_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_client (struct nfs4_client*) ; 
 int /*<<< orphan*/  gen_confirm (struct nfs4_client*) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int /*<<< orphan*/ * kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd4_do_callback_rpc ; 
 int /*<<< orphan*/  rpc_copy_addr (struct sockaddr*,struct sockaddr*) ; 
 int /*<<< orphan*/  rpc_init_wait_queue (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct sockaddr* svc_addr (struct svc_rqst*) ; 
 char* svc_gss_principal (struct svc_rqst*) ; 

__attribute__((used)) static struct nfs4_client *create_client(struct xdr_netobj name, char *recdir,
		struct svc_rqst *rqstp, nfs4_verifier *verf)
{
	struct nfs4_client *clp;
	struct sockaddr *sa = svc_addr(rqstp);
	char *princ;

	clp = alloc_client(name);
	if (clp == NULL)
		return NULL;

	INIT_LIST_HEAD(&clp->cl_sessions);

	princ = svc_gss_principal(rqstp);
	if (princ) {
		clp->cl_principal = kstrdup(princ, GFP_KERNEL);
		if (clp->cl_principal == NULL) {
			free_client(clp);
			return NULL;
		}
	}

	memcpy(clp->cl_recdir, recdir, HEXDIR_LEN);
	atomic_set(&clp->cl_refcount, 0);
	atomic_set(&clp->cl_cb_set, 0);
	INIT_LIST_HEAD(&clp->cl_idhash);
	INIT_LIST_HEAD(&clp->cl_strhash);
	INIT_LIST_HEAD(&clp->cl_openowners);
	INIT_LIST_HEAD(&clp->cl_delegations);
	INIT_LIST_HEAD(&clp->cl_lru);
	spin_lock_init(&clp->cl_lock);
	INIT_WORK(&clp->cl_cb_null.cb_work, nfsd4_do_callback_rpc);
	clp->cl_time = get_seconds();
	clear_bit(0, &clp->cl_cb_slot_busy);
	rpc_init_wait_queue(&clp->cl_cb_waitq, "Backchannel slot table");
	copy_verf(clp, verf);
	rpc_copy_addr((struct sockaddr *) &clp->cl_addr, sa);
	clp->cl_flavor = rqstp->rq_flavor;
	copy_cred(&clp->cl_cred, &rqstp->rq_cred);
	gen_confirm(clp);
	clp->cl_cb_session = NULL;
	return clp;
}