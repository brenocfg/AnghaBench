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
struct svc_rqst {int dummy; } ;
struct nfsd4_open_downgrade {scalar_t__ od_stateowner; int /*<<< orphan*/  od_stateid; int /*<<< orphan*/  od_share_deny; int /*<<< orphan*/  od_share_access; int /*<<< orphan*/  od_seqid; } ;
struct TYPE_6__ {TYPE_2__* fh_dentry; } ;
struct nfsd4_compound_state {scalar_t__ replay_owner; int /*<<< orphan*/  minorversion; TYPE_3__ current_fh; } ;
struct nfs4_stateid {int st_access_bmap; int st_deny_bmap; int /*<<< orphan*/  st_stateid; } ;
typedef  int /*<<< orphan*/  stateid_t ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  name; scalar_t__ len; } ;
struct TYPE_5__ {TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPEN_STATE ; 
 int /*<<< orphan*/  access_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deny_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfs4_file_downgrade (struct nfs4_stateid*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_get_stateowner (scalar_t__) ; 
 int /*<<< orphan*/  nfs4_lock_state () ; 
 int /*<<< orphan*/  nfs4_preprocess_seqid_op (struct nfsd4_compound_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,struct nfs4_stateid**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_unlock_state () ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_inval ; 
 int /*<<< orphan*/  reset_union_bmap_deny (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  update_stateid (int /*<<< orphan*/ *) ; 

__be32
nfsd4_open_downgrade(struct svc_rqst *rqstp,
		     struct nfsd4_compound_state *cstate,
		     struct nfsd4_open_downgrade *od)
{
	__be32 status;
	struct nfs4_stateid *stp;

	dprintk("NFSD: nfsd4_open_downgrade on file %.*s\n", 
			(int)cstate->current_fh.fh_dentry->d_name.len,
			cstate->current_fh.fh_dentry->d_name.name);

	if (!access_valid(od->od_share_access, cstate->minorversion)
			|| !deny_valid(od->od_share_deny))
		return nfserr_inval;

	nfs4_lock_state();
	if ((status = nfs4_preprocess_seqid_op(cstate,
					od->od_seqid,
					&od->od_stateid, 
					OPEN_STATE,
					&od->od_stateowner, &stp, NULL)))
		goto out; 

	status = nfserr_inval;
	if (!test_bit(od->od_share_access, &stp->st_access_bmap)) {
		dprintk("NFSD:access not a subset current bitmap: 0x%lx, input access=%08x\n",
			stp->st_access_bmap, od->od_share_access);
		goto out;
	}
	if (!test_bit(od->od_share_deny, &stp->st_deny_bmap)) {
		dprintk("NFSD:deny not a subset current bitmap: 0x%lx, input deny=%08x\n",
			stp->st_deny_bmap, od->od_share_deny);
		goto out;
	}
	nfs4_file_downgrade(stp, od->od_share_access);

	reset_union_bmap_deny(od->od_share_deny, &stp->st_deny_bmap);

	update_stateid(&stp->st_stateid);
	memcpy(&od->od_stateid, &stp->st_stateid, sizeof(stateid_t));
	status = nfs_ok;
out:
	if (od->od_stateowner) {
		nfs4_get_stateowner(od->od_stateowner);
		cstate->replay_owner = od->od_stateowner;
	}
	nfs4_unlock_state();
	return status;
}