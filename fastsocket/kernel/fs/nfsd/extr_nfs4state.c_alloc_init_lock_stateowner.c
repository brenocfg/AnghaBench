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
struct nfsd4_lock {scalar_t__ lk_new_lock_seqid; int /*<<< orphan*/  lk_new_owner; } ;
struct nfs4_replay {int /*<<< orphan*/  rp_ibuf; int /*<<< orphan*/  rp_buf; scalar_t__ rp_buflen; int /*<<< orphan*/  rp_status; } ;
struct nfs4_stateowner {int so_confirmed; struct nfs4_replay so_replay; scalar_t__ so_seqid; struct nfs4_client* so_client; scalar_t__ so_id; scalar_t__ so_is_open_owner; int /*<<< orphan*/  so_perstateid; int /*<<< orphan*/  so_strhash; int /*<<< orphan*/  so_idhash; scalar_t__ so_time; int /*<<< orphan*/  so_close_lru; int /*<<< orphan*/  so_stateids; int /*<<< orphan*/  so_perclient; } ;
struct nfs4_stateid {int /*<<< orphan*/  st_lockowners; } ;
struct nfs4_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nfs4_stateowner* alloc_stateowner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_ownerid ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lock_ownerid_hashtbl ; 
 int /*<<< orphan*/ * lock_ownerstr_hashtbl ; 
 unsigned int lockownerid_hashval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfserr_serverfault ; 

__attribute__((used)) static struct nfs4_stateowner *
alloc_init_lock_stateowner(unsigned int strhashval, struct nfs4_client *clp, struct nfs4_stateid *open_stp, struct nfsd4_lock *lock) {
	struct nfs4_stateowner *sop;
	struct nfs4_replay *rp;
	unsigned int idhashval;

	if (!(sop = alloc_stateowner(&lock->lk_new_owner)))
		return NULL;
	idhashval = lockownerid_hashval(current_ownerid);
	INIT_LIST_HEAD(&sop->so_idhash);
	INIT_LIST_HEAD(&sop->so_strhash);
	INIT_LIST_HEAD(&sop->so_perclient);
	INIT_LIST_HEAD(&sop->so_stateids);
	INIT_LIST_HEAD(&sop->so_perstateid);
	INIT_LIST_HEAD(&sop->so_close_lru); /* not used */
	sop->so_time = 0;
	list_add(&sop->so_idhash, &lock_ownerid_hashtbl[idhashval]);
	list_add(&sop->so_strhash, &lock_ownerstr_hashtbl[strhashval]);
	list_add(&sop->so_perstateid, &open_stp->st_lockowners);
	sop->so_is_open_owner = 0;
	sop->so_id = current_ownerid++;
	sop->so_client = clp;
	/* It is the openowner seqid that will be incremented in encode in the
	 * case of new lockowners; so increment the lock seqid manually: */
	sop->so_seqid = lock->lk_new_lock_seqid + 1;
	sop->so_confirmed = 1;
	rp = &sop->so_replay;
	rp->rp_status = nfserr_serverfault;
	rp->rp_buflen = 0;
	rp->rp_buf = rp->rp_ibuf;
	return sop;
}