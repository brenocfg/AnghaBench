#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xdr_netobj {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct svc_rqst {int /*<<< orphan*/  rq_cred; } ;
struct sockaddr {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  cl_id; int /*<<< orphan*/  cl_boot; } ;
struct nfsd4_setclientid {TYPE_3__ se_confirm; TYPE_1__ se_clientid; int /*<<< orphan*/  se_verf; int /*<<< orphan*/  se_name; int /*<<< orphan*/  se_namelen; } ;
struct nfsd4_compound_state {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  cl_id; int /*<<< orphan*/  cl_boot; } ;
struct nfs4_client {TYPE_4__ cl_confirm; TYPE_2__ cl_clientid; scalar_t__ cl_minorversion; int /*<<< orphan*/  cl_verifier; int /*<<< orphan*/  cl_addr; int /*<<< orphan*/  cl_cred; } ;
typedef  int /*<<< orphan*/  nfs4_verifier ;
typedef  int /*<<< orphan*/  addr_str ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int HEXDIR_LEN ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  add_to_unconfirmed (struct nfs4_client*,unsigned int) ; 
 int /*<<< orphan*/  check_name (struct xdr_netobj) ; 
 unsigned int clientstr_hashval (char*) ; 
 int /*<<< orphan*/  copy_clid (struct nfs4_client*,struct nfs4_client*) ; 
 struct nfs4_client* create_client (struct xdr_netobj,char*,struct svc_rqst*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,char*) ; 
 int /*<<< orphan*/  expire_client (struct nfs4_client*) ; 
 struct nfs4_client* find_confirmed_client_by_str (char*,unsigned int,int) ; 
 struct nfs4_client* find_unconfirmed_client_by_str (char*,unsigned int,int) ; 
 int /*<<< orphan*/  gen_callback (struct nfs4_client*,struct nfsd4_setclientid*,struct svc_rqst*) ; 
 int /*<<< orphan*/  gen_clid (struct nfs4_client*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs4_lock_state () ; 
 scalar_t__ nfs4_make_rec_clidname (char*,struct xdr_netobj*) ; 
 int /*<<< orphan*/  nfs4_unlock_state () ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfserr_clid_inuse ; 
 scalar_t__ nfserr_inval ; 
 scalar_t__ nfserr_resource ; 
 int /*<<< orphan*/  rpc_ntop (struct sockaddr*,char*,int) ; 
 int /*<<< orphan*/  same_creds (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ same_verf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__be32
nfsd4_setclientid(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
		  struct nfsd4_setclientid *setclid)
{
	struct xdr_netobj 	clname = { 
		.len = setclid->se_namelen,
		.data = setclid->se_name,
	};
	nfs4_verifier		clverifier = setclid->se_verf;
	unsigned int 		strhashval;
	struct nfs4_client	*conf, *unconf, *new;
	__be32 			status;
	char                    dname[HEXDIR_LEN];
	
	if (!check_name(clname))
		return nfserr_inval;

	status = nfs4_make_rec_clidname(dname, &clname);
	if (status)
		return status;

	/* 
	 * XXX The Duplicate Request Cache (DRC) has been checked (??)
	 * We get here on a DRC miss.
	 */

	strhashval = clientstr_hashval(dname);

	nfs4_lock_state();
	conf = find_confirmed_client_by_str(dname, strhashval, false);
	if (conf) {
		/* RFC 3530 14.2.33 CASE 0: */
		status = nfserr_clid_inuse;
		if (!same_creds(&conf->cl_cred, &rqstp->rq_cred)) {
			char addr_str[INET6_ADDRSTRLEN];
			rpc_ntop((struct sockaddr *) &conf->cl_addr, addr_str,
				 sizeof(addr_str));
			dprintk("NFSD: setclientid: string in use by client "
				"at %s\n", addr_str);
			goto out;
		}
	}
	/*
	 * section 14.2.33 of RFC 3530 (under the heading "IMPLEMENTATION")
	 * has a description of SETCLIENTID request processing consisting
	 * of 5 bullet points, labeled as CASE0 - CASE4 below.
	 */
	unconf = find_unconfirmed_client_by_str(dname, strhashval, false);
	status = nfserr_resource;
	if (!conf) {
		/*
		 * RFC 3530 14.2.33 CASE 4:
		 * placed first, because it is the normal case
		 */
		if (unconf)
			expire_client(unconf);
		new = create_client(clname, dname, rqstp, &clverifier);
		if (new == NULL)
			goto out;
		gen_clid(new);
	} else if (same_verf(&conf->cl_verifier, &clverifier)) {
		/*
		 * RFC 3530 14.2.33 CASE 1:
		 * probable callback update
		 */
		if (unconf) {
			/* Note this is removing unconfirmed {*x***},
			 * which is stronger than RFC recommended {vxc**}.
			 * This has the advantage that there is at most
			 * one {*x***} in either list at any time.
			 */
			expire_client(unconf);
		}
		new = create_client(clname, dname, rqstp, &clverifier);
		if (new == NULL)
			goto out;
		copy_clid(new, conf);
	} else if (!unconf) {
		/*
		 * RFC 3530 14.2.33 CASE 2:
		 * probable client reboot; state will be removed if
		 * confirmed.
		 */
		new = create_client(clname, dname, rqstp, &clverifier);
		if (new == NULL)
			goto out;
		gen_clid(new);
	} else {
		/*
		 * RFC 3530 14.2.33 CASE 3:
		 * probable client reboot; state will be removed if
		 * confirmed.
		 */
		expire_client(unconf);
		new = create_client(clname, dname, rqstp, &clverifier);
		if (new == NULL)
			goto out;
		gen_clid(new);
	}
	/*
	 * XXX: we should probably set this at creation time, and check
	 * for consistent minorversion use throughout:
	 */
	new->cl_minorversion = 0;
	gen_callback(new, setclid, rqstp);
	add_to_unconfirmed(new, strhashval);
	setclid->se_clientid.cl_boot = new->cl_clientid.cl_boot;
	setclid->se_clientid.cl_id = new->cl_clientid.cl_id;
	memcpy(setclid->se_confirm.data, new->cl_confirm.data, sizeof(setclid->se_confirm.data));
	status = nfs_ok;
out:
	nfs4_unlock_state();
	return status;
}