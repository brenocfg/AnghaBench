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
struct svc_rqst {int /*<<< orphan*/  rq_cred; } ;
struct sockaddr {int dummy; } ;
struct nfsd4_setclientid_confirm {int /*<<< orphan*/  sc_clientid; int /*<<< orphan*/  sc_confirm; } ;
struct nfsd4_compound_state {int dummy; } ;
struct nfs4_client {int /*<<< orphan*/  cl_confirm; int /*<<< orphan*/  cl_recdir; int /*<<< orphan*/  cl_cred; int /*<<< orphan*/  cl_cb_conn; int /*<<< orphan*/  cl_cb_set; int /*<<< orphan*/  cl_addr; } ;
typedef  int /*<<< orphan*/  nfs4_verifier ;
typedef  int /*<<< orphan*/  clientid_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ STALE_CLIENTID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int clientstr_hashval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expire_client (struct nfs4_client*) ; 
 struct nfs4_client* find_confirmed_client (int /*<<< orphan*/ *) ; 
 struct nfs4_client* find_confirmed_client_by_str (int /*<<< orphan*/ ,unsigned int,int) ; 
 struct nfs4_client* find_unconfirmed_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  move_to_confirmed (struct nfs4_client*) ; 
 int /*<<< orphan*/  nfs4_lock_state () ; 
 int /*<<< orphan*/  nfs4_unlock_state () ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfsd4_change_callback (struct nfs4_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_probe_callback (struct nfs4_client*) ; 
 int /*<<< orphan*/  nfsd4_remove_clid_dir (struct nfs4_client*) ; 
 int /*<<< orphan*/  nfserr_clid_inuse ; 
 int /*<<< orphan*/  nfserr_stale_clientid ; 
 int /*<<< orphan*/  rpc_cmp_addr (struct sockaddr*,struct sockaddr*) ; 
 int /*<<< orphan*/  same_creds (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ same_verf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sockaddr* svc_addr (struct svc_rqst*) ; 

__be32
nfsd4_setclientid_confirm(struct svc_rqst *rqstp,
			 struct nfsd4_compound_state *cstate,
			 struct nfsd4_setclientid_confirm *setclientid_confirm)
{
	struct sockaddr *sa = svc_addr(rqstp);
	struct nfs4_client *conf, *unconf;
	nfs4_verifier confirm = setclientid_confirm->sc_confirm; 
	clientid_t * clid = &setclientid_confirm->sc_clientid;
	__be32 status;

	if (STALE_CLIENTID(clid))
		return nfserr_stale_clientid;
	/* 
	 * XXX The Duplicate Request Cache (DRC) has been checked (??)
	 * We get here on a DRC miss.
	 */

	nfs4_lock_state();

	conf = find_confirmed_client(clid);
	unconf = find_unconfirmed_client(clid);

	status = nfserr_clid_inuse;
	if (conf && !rpc_cmp_addr((struct sockaddr *) &conf->cl_addr, sa))
		goto out;
	if (unconf && !rpc_cmp_addr((struct sockaddr *) &unconf->cl_addr, sa))
		goto out;

	/*
	 * section 14.2.34 of RFC 3530 has a description of
	 * SETCLIENTID_CONFIRM request processing consisting
	 * of 4 bullet points, labeled as CASE1 - CASE4 below.
	 */
	if (conf && unconf && same_verf(&confirm, &unconf->cl_confirm)) {
		/*
		 * RFC 3530 14.2.34 CASE 1:
		 * callback update
		 */
		if (!same_creds(&conf->cl_cred, &unconf->cl_cred))
			status = nfserr_clid_inuse;
		else {
			atomic_set(&conf->cl_cb_set, 0);
			nfsd4_change_callback(conf, &unconf->cl_cb_conn);
			nfsd4_probe_callback(conf);
			expire_client(unconf);
			status = nfs_ok;

		}
	} else if (conf && !unconf) {
		/*
		 * RFC 3530 14.2.34 CASE 2:
		 * probable retransmitted request; play it safe and
		 * do nothing.
		 */
		if (!same_creds(&conf->cl_cred, &rqstp->rq_cred))
			status = nfserr_clid_inuse;
		else
			status = nfs_ok;
	} else if (!conf && unconf
			&& same_verf(&unconf->cl_confirm, &confirm)) {
		/*
		 * RFC 3530 14.2.34 CASE 3:
		 * Normal case; new or rebooted client:
		 */
		if (!same_creds(&unconf->cl_cred, &rqstp->rq_cred)) {
			status = nfserr_clid_inuse;
		} else {
			unsigned int hash =
				clientstr_hashval(unconf->cl_recdir);
			conf = find_confirmed_client_by_str(unconf->cl_recdir,
							    hash, false);
			if (conf) {
				nfsd4_remove_clid_dir(conf);
				expire_client(conf);
			}
			move_to_confirmed(unconf);
			conf = unconf;
			nfsd4_probe_callback(conf);
			status = nfs_ok;
		}
	} else if ((!conf || (conf && !same_verf(&conf->cl_confirm, &confirm)))
	    && (!unconf || (unconf && !same_verf(&unconf->cl_confirm,
				    				&confirm)))) {
		/*
		 * RFC 3530 14.2.34 CASE 4:
		 * Client probably hasn't noticed that we rebooted yet.
		 */
		status = nfserr_stale_clientid;
	} else {
		/* check that we have hit one of the cases...*/
		status = nfserr_clid_inuse;
	}
out:
	nfs4_unlock_state();
	return status;
}