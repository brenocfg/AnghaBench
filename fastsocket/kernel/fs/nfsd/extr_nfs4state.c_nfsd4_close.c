#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct svc_rqst {int dummy; } ;
struct TYPE_9__ {TYPE_2__* fh_dentry; } ;
struct nfsd4_compound_state {TYPE_4__* replay_owner; TYPE_3__ current_fh; } ;
struct nfsd4_close {TYPE_4__* cl_stateowner; int /*<<< orphan*/  cl_stateid; int /*<<< orphan*/  cl_seqid; } ;
struct nfs4_stateid {int /*<<< orphan*/  st_stateid; } ;
typedef  int /*<<< orphan*/  stateid_t ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_10__ {int /*<<< orphan*/  so_stateids; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; scalar_t__ len; } ;
struct TYPE_8__ {TYPE_1__ d_name; } ;

/* Variables and functions */
 int CLOSE_STATE ; 
 int OPEN_STATE ; 
 int /*<<< orphan*/  dprintk (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  move_to_close_lru (TYPE_4__*) ; 
 int /*<<< orphan*/  nfs4_get_stateowner (TYPE_4__*) ; 
 int /*<<< orphan*/  nfs4_lock_state () ; 
 int /*<<< orphan*/  nfs4_preprocess_seqid_op (struct nfsd4_compound_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_4__**,struct nfs4_stateid**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_unlock_state () ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  release_open_stateid (struct nfs4_stateid*) ; 
 int /*<<< orphan*/  update_stateid (int /*<<< orphan*/ *) ; 

__be32
nfsd4_close(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	    struct nfsd4_close *close)
{
	__be32 status;
	struct nfs4_stateid *stp;

	dprintk("NFSD: nfsd4_close on file %.*s\n", 
			(int)cstate->current_fh.fh_dentry->d_name.len,
			cstate->current_fh.fh_dentry->d_name.name);

	nfs4_lock_state();
	/* check close_lru for replay */
	if ((status = nfs4_preprocess_seqid_op(cstate,
					close->cl_seqid,
					&close->cl_stateid, 
					OPEN_STATE | CLOSE_STATE,
					&close->cl_stateowner, &stp, NULL)))
		goto out; 
	status = nfs_ok;
	update_stateid(&stp->st_stateid);
	memcpy(&close->cl_stateid, &stp->st_stateid, sizeof(stateid_t));

	/* release_stateid() calls nfsd_close() if needed */
	release_open_stateid(stp);

	/* place unused nfs4_stateowners on so_close_lru list to be
	 * released by the laundromat service after the lease period
	 * to enable us to handle CLOSE replay
	 */
	if (list_empty(&close->cl_stateowner->so_stateids))
		move_to_close_lru(close->cl_stateowner);
out:
	if (close->cl_stateowner) {
		nfs4_get_stateowner(close->cl_stateowner);
		cstate->replay_owner = close->cl_stateowner;
	}
	nfs4_unlock_state();
	return status;
}