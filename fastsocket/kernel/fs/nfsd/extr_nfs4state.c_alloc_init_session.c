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
struct svc_rqst {int /*<<< orphan*/  rq_xprt; } ;
struct sockaddr {int dummy; } ;
struct nfsd4_session {int se_cb_seq_nr; int se_flags; int /*<<< orphan*/  se_ref; int /*<<< orphan*/  se_perclnt; int /*<<< orphan*/  se_hash; int /*<<< orphan*/  se_sessionid; int /*<<< orphan*/  se_cb_prog; int /*<<< orphan*/  se_conns; struct nfs4_client* se_client; int /*<<< orphan*/  se_fchannel; } ;
struct nfsd4_channel_attrs {int /*<<< orphan*/  maxreqs; int /*<<< orphan*/  maxresp_cached; } ;
struct nfsd4_create_session {int flags; int /*<<< orphan*/  callback_prog; struct nfsd4_channel_attrs fore_channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  cb_addrlen; int /*<<< orphan*/  cb_addr; int /*<<< orphan*/  cb_xprt; } ;
struct nfs4_client {TYPE_1__ cl_cb_conn; struct nfsd4_session* cl_cb_session; int /*<<< orphan*/  cl_sessions; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int SESSION4_BACK_CHAN ; 
 struct nfsd4_session* alloc_session (int,int) ; 
 int /*<<< orphan*/  client_lock ; 
 int /*<<< orphan*/  free_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_sessionid (struct nfsd4_session*) ; 
 int hash_sessionid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_forechannel_attrs (int /*<<< orphan*/ *,struct nfsd4_channel_attrs*,int,int) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nfsd4_get_drc_mem (int,int /*<<< orphan*/ ) ; 
 int nfsd4_new_conn (struct svc_rqst*,struct nfsd4_session*) ; 
 int /*<<< orphan*/  nfsd4_probe_callback (struct nfs4_client*) ; 
 int /*<<< orphan*/  nfsd4_put_drc_mem (int,int /*<<< orphan*/ ) ; 
 int nfsd4_sanitize_slot_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_copy_addr (struct sockaddr*,struct sockaddr*) ; 
 int /*<<< orphan*/ * sessionid_hashtbl ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct sockaddr* svc_addr (struct svc_rqst*) ; 
 int /*<<< orphan*/  svc_addr_len (struct sockaddr*) ; 
 int /*<<< orphan*/  svc_xprt_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfsd4_session *alloc_init_session(struct svc_rqst *rqstp, struct nfs4_client *clp, struct nfsd4_create_session *cses)
{
	struct nfsd4_session *new;
	struct nfsd4_channel_attrs *fchan = &cses->fore_channel;
	int numslots, slotsize;
	int status;
	int idx;

	/*
	 * Note decreasing slot size below client's request may
	 * make it difficult for client to function correctly, whereas
	 * decreasing the number of slots will (just?) affect
	 * performance.  When short on memory we therefore prefer to
	 * decrease number of slots instead of their size.
	 */
	slotsize = nfsd4_sanitize_slot_size(fchan->maxresp_cached);
	numslots = nfsd4_get_drc_mem(slotsize, fchan->maxreqs);

	new = alloc_session(slotsize, numslots);
	if (!new) {
		nfsd4_put_drc_mem(slotsize, fchan->maxreqs);
		return NULL;
	}
	init_forechannel_attrs(&new->se_fchannel, fchan, numslots, slotsize);

	new->se_client = clp;
	gen_sessionid(new);

	INIT_LIST_HEAD(&new->se_conns);

	new->se_cb_seq_nr = 1;
	new->se_flags = cses->flags;
	new->se_cb_prog = cses->callback_prog;
	kref_init(&new->se_ref);
	idx = hash_sessionid(&new->se_sessionid);
	spin_lock(&client_lock);
	list_add(&new->se_hash, &sessionid_hashtbl[idx]);
	list_add(&new->se_perclnt, &clp->cl_sessions);
	spin_unlock(&client_lock);

	status = nfsd4_new_conn(rqstp, new);
	/* whoops: benny points out, status is ignored! (err, or bogus) */
	if (status) {
		free_session(&new->se_ref);
		return NULL;
	}
	if (!clp->cl_cb_session && (cses->flags & SESSION4_BACK_CHAN)) {
		struct sockaddr *sa = svc_addr(rqstp);

		clp->cl_cb_session = new;
		clp->cl_cb_conn.cb_xprt = rqstp->rq_xprt;
		svc_xprt_get(rqstp->rq_xprt);
		rpc_copy_addr((struct sockaddr *)&clp->cl_cb_conn.cb_addr, sa);
		clp->cl_cb_conn.cb_addrlen = svc_addr_len(sa);
		nfsd4_probe_callback(clp);
	}
	return new;
}