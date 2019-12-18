#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cl_id; } ;
struct nfsd4_open {int op_seqid; struct nfs4_stateowner* op_stateowner; int /*<<< orphan*/  op_owner; TYPE_2__ op_clientid; } ;
struct nfsd4_compound_state {int dummy; } ;
struct TYPE_5__ {scalar_t__ rp_buflen; } ;
struct nfs4_stateowner {int so_seqid; struct nfs4_client* so_client; int /*<<< orphan*/  so_close_lru; TYPE_1__ so_replay; int /*<<< orphan*/  so_confirmed; } ;
struct nfs4_client {int dummy; } ;
typedef  TYPE_2__ clientid_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ STALE_CLIENTID (TYPE_2__*) ; 
 struct nfs4_stateowner* alloc_init_open_stateowner (unsigned int,struct nfs4_client*,struct nfsd4_open*) ; 
 int /*<<< orphan*/  check_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 struct nfs4_client* find_confirmed_client (TYPE_2__*) ; 
 struct nfs4_stateowner* find_openstateowner_str (unsigned int,struct nfsd4_open*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_ok ; 
 scalar_t__ nfsd4_has_session (struct nfsd4_compound_state*) ; 
 int /*<<< orphan*/  nfserr_bad_seqid ; 
 int /*<<< orphan*/  nfserr_expired ; 
 int /*<<< orphan*/  nfserr_inval ; 
 int /*<<< orphan*/  nfserr_replay_me ; 
 int /*<<< orphan*/  nfserr_resource ; 
 int /*<<< orphan*/  nfserr_stale_clientid ; 
 unsigned int ownerstr_hashval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_openowner (struct nfs4_stateowner*) ; 
 int /*<<< orphan*/  renew_client (struct nfs4_client*) ; 

__be32
nfsd4_process_open1(struct nfsd4_compound_state *cstate,
		    struct nfsd4_open *open)
{
	clientid_t *clientid = &open->op_clientid;
	struct nfs4_client *clp = NULL;
	unsigned int strhashval;
	struct nfs4_stateowner *sop = NULL;

	if (!check_name(open->op_owner))
		return nfserr_inval;

	if (STALE_CLIENTID(&open->op_clientid))
		return nfserr_stale_clientid;

	strhashval = ownerstr_hashval(clientid->cl_id, open->op_owner);
	sop = find_openstateowner_str(strhashval, open);
	open->op_stateowner = sop;
	if (!sop) {
		/* Make sure the client's lease hasn't expired. */
		clp = find_confirmed_client(clientid);
		if (clp == NULL)
			return nfserr_expired;
		goto renew;
	}
	/* When sessions are used, skip open sequenceid processing */
	if (nfsd4_has_session(cstate))
		goto renew;
	if (!sop->so_confirmed) {
		/* Replace unconfirmed owners without checking for replay. */
		clp = sop->so_client;
		release_openowner(sop);
		open->op_stateowner = NULL;
		goto renew;
	}
	if (open->op_seqid == sop->so_seqid - 1) {
		if (sop->so_replay.rp_buflen)
			return nfserr_replay_me;
		/* The original OPEN failed so spectacularly
		 * that we don't even have replay data saved!
		 * Therefore, we have no choice but to continue
		 * processing this OPEN; presumably, we'll
		 * fail again for the same reason.
		 */
		dprintk("nfsd4_process_open1: replay with no replay cache\n");
		goto renew;
	}
	if (open->op_seqid != sop->so_seqid)
		return nfserr_bad_seqid;
renew:
	if (open->op_stateowner == NULL) {
		sop = alloc_init_open_stateowner(strhashval, clp, open);
		if (sop == NULL)
			return nfserr_resource;
		open->op_stateowner = sop;
	}
	list_del_init(&sop->so_close_lru);
	renew_client(sop->so_client);
	return nfs_ok;
}