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
struct svc_rqst {int dummy; } ;
struct nfsd4_compound_state {int dummy; } ;
struct nfs4_client {int /*<<< orphan*/  cl_cb_set; int /*<<< orphan*/  cl_delegations; } ;
struct TYPE_5__ {int /*<<< orphan*/  cl_id; int /*<<< orphan*/  cl_boot; } ;
typedef  TYPE_1__ clientid_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ STALE_CLIENTID (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 struct nfs4_client* find_confirmed_client (TYPE_1__*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_lock_state () ; 
 int /*<<< orphan*/  nfs4_unlock_state () ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_cb_path_down ; 
 int /*<<< orphan*/  nfserr_expired ; 
 int /*<<< orphan*/  nfserr_stale_clientid ; 
 int /*<<< orphan*/  renew_client (struct nfs4_client*) ; 

__be32
nfsd4_renew(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	    clientid_t *clid)
{
	struct nfs4_client *clp;
	__be32 status;

	nfs4_lock_state();
	dprintk("process_renew(%08x/%08x): starting\n", 
			clid->cl_boot, clid->cl_id);
	status = nfserr_stale_clientid;
	if (STALE_CLIENTID(clid))
		goto out;
	clp = find_confirmed_client(clid);
	status = nfserr_expired;
	if (clp == NULL) {
		/* We assume the client took too long to RENEW. */
		dprintk("nfsd4_renew: clientid not found!\n");
		goto out;
	}
	renew_client(clp);
	status = nfserr_cb_path_down;
	if (!list_empty(&clp->cl_delegations)
			&& !atomic_read(&clp->cl_cb_set))
		goto out;
	status = nfs_ok;
out:
	nfs4_unlock_state();
	return status;
}