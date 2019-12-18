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
struct nfsd4_open {int /*<<< orphan*/  op_seqid; int /*<<< orphan*/  op_owner; } ;
struct nfs4_replay {int /*<<< orphan*/  rp_ibuf; int /*<<< orphan*/  rp_buf; scalar_t__ rp_buflen; int /*<<< orphan*/  rp_status; } ;
struct nfs4_stateowner {int so_is_open_owner; struct nfs4_replay so_replay; scalar_t__ so_confirmed; int /*<<< orphan*/  so_seqid; struct nfs4_client* so_client; scalar_t__ so_id; int /*<<< orphan*/  so_perclient; int /*<<< orphan*/  so_strhash; int /*<<< orphan*/  so_idhash; scalar_t__ so_time; int /*<<< orphan*/  so_close_lru; int /*<<< orphan*/  so_perstateid; int /*<<< orphan*/  so_stateids; } ;
struct nfs4_client {int /*<<< orphan*/  cl_openowners; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nfs4_stateowner* alloc_stateowner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_ownerid ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfserr_serverfault ; 
 int /*<<< orphan*/ * ownerid_hashtbl ; 
 unsigned int ownerid_hashval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ownerstr_hashtbl ; 

__attribute__((used)) static struct nfs4_stateowner *
alloc_init_open_stateowner(unsigned int strhashval, struct nfs4_client *clp, struct nfsd4_open *open) {
	struct nfs4_stateowner *sop;
	struct nfs4_replay *rp;
	unsigned int idhashval;

	if (!(sop = alloc_stateowner(&open->op_owner)))
		return NULL;
	idhashval = ownerid_hashval(current_ownerid);
	INIT_LIST_HEAD(&sop->so_idhash);
	INIT_LIST_HEAD(&sop->so_strhash);
	INIT_LIST_HEAD(&sop->so_perclient);
	INIT_LIST_HEAD(&sop->so_stateids);
	INIT_LIST_HEAD(&sop->so_perstateid);  /* not used */
	INIT_LIST_HEAD(&sop->so_close_lru);
	sop->so_time = 0;
	list_add(&sop->so_idhash, &ownerid_hashtbl[idhashval]);
	list_add(&sop->so_strhash, &ownerstr_hashtbl[strhashval]);
	list_add(&sop->so_perclient, &clp->cl_openowners);
	sop->so_is_open_owner = 1;
	sop->so_id = current_ownerid++;
	sop->so_client = clp;
	sop->so_seqid = open->op_seqid;
	sop->so_confirmed = 0;
	rp = &sop->so_replay;
	rp->rp_status = nfserr_serverfault;
	rp->rp_buflen = 0;
	rp->rp_buf = rp->rp_ibuf;
	return sop;
}