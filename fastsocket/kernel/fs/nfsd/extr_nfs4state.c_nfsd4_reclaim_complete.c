#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct svc_rqst {int dummy; } ;
struct nfsd4_reclaim_complete {scalar_t__ rca_one_fs; } ;
struct TYPE_3__ {int /*<<< orphan*/  fh_dentry; } ;
struct nfsd4_compound_state {TYPE_2__* session; TYPE_1__ current_fh; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  se_client; } ;

/* Variables and functions */
 scalar_t__ is_client_expired (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_lock_state () ; 
 int /*<<< orphan*/  nfs4_unlock_state () ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfsd4_create_clid_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfserr_nofilehandle ; 
 int /*<<< orphan*/  nfserr_stale_clientid ; 

__be32
nfsd4_reclaim_complete(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate, struct nfsd4_reclaim_complete *rc)
{
	if (rc->rca_one_fs) {
		if (!cstate->current_fh.fh_dentry)
			return nfserr_nofilehandle;
		/*
		 * We don't take advantage of the rca_one_fs case.
		 * That's OK, it's optional, we can safely ignore it.
		 */
		 return nfs_ok;
	}
	nfs4_lock_state();
	if (is_client_expired(cstate->session->se_client)) {
		nfs4_unlock_state();
		/*
		 * The following error isn't really legal.
		 * But we only get here if the client just explicitly
		 * destroyed the client.  Surely it no longer cares what
		 * error it gets back on an operation for the dead
		 * client.
		 */
		return nfserr_stale_clientid;
	}
	nfsd4_create_clid_dir(cstate->session->se_client);
	nfs4_unlock_state();
	return nfs_ok;
}