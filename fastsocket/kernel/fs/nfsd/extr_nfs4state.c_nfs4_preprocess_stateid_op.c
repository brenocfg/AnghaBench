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
struct svc_fh {TYPE_1__* fh_dentry; } ;
struct nfsd4_compound_state {struct svc_fh current_fh; } ;
struct nfs4_stateid {int /*<<< orphan*/  st_file; TYPE_2__* st_stateowner; int /*<<< orphan*/  st_stateid; } ;
struct nfs4_delegation {int /*<<< orphan*/  dl_file; int /*<<< orphan*/  dl_client; int /*<<< orphan*/  dl_stateid; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  stateid_t ;
typedef  scalar_t__ __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  so_client; int /*<<< orphan*/  so_confirmed; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int HAS_SESSION ; 
 scalar_t__ ONE_STATEID (int /*<<< orphan*/ *) ; 
 int RD_STATE ; 
 scalar_t__ STALE_STATEID (int /*<<< orphan*/ *) ; 
 scalar_t__ ZERO_STATEID (int /*<<< orphan*/ *) ; 
 scalar_t__ check_special_stateids (struct svc_fh*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ check_stateid_generation (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct nfs4_delegation* find_delegation_stateid (struct inode*,int /*<<< orphan*/ *) ; 
 struct file* find_readable_file (int /*<<< orphan*/ ) ; 
 struct nfs4_stateid* find_stateid (int /*<<< orphan*/ *,int) ; 
 struct file* find_writeable_file (int /*<<< orphan*/ ) ; 
 scalar_t__ grace_disallows_io (struct inode*) ; 
 scalar_t__ is_delegation_stateid (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs4_check_delegmode (struct nfs4_delegation*,int) ; 
 scalar_t__ nfs4_check_fh (struct svc_fh*,struct nfs4_stateid*) ; 
 scalar_t__ nfs4_check_openmode (struct nfs4_stateid*,int) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfsd4_has_session (struct nfsd4_compound_state*) ; 
 scalar_t__ nfserr_bad_stateid ; 
 scalar_t__ nfserr_expired ; 
 scalar_t__ nfserr_grace ; 
 scalar_t__ nfserr_stale_stateid ; 
 int /*<<< orphan*/  renew_client (int /*<<< orphan*/ ) ; 

__be32
nfs4_preprocess_stateid_op(struct nfsd4_compound_state *cstate,
			   stateid_t *stateid, int flags, struct file **filpp)
{
	struct nfs4_stateid *stp = NULL;
	struct nfs4_delegation *dp = NULL;
	struct svc_fh *current_fh = &cstate->current_fh;
	struct inode *ino = current_fh->fh_dentry->d_inode;
	__be32 status;

	if (filpp)
		*filpp = NULL;

	if (grace_disallows_io(ino))
		return nfserr_grace;

	if (nfsd4_has_session(cstate))
		flags |= HAS_SESSION;

	if (ZERO_STATEID(stateid) || ONE_STATEID(stateid))
		return check_special_stateids(current_fh, stateid, flags);

	status = nfserr_stale_stateid;
	if (STALE_STATEID(stateid)) 
		goto out;

	/*
	 * We assume that any stateid that has the current boot time,
	 * but that we can't find, is expired:
	 */
	status = nfserr_expired;
	if (is_delegation_stateid(stateid)) {
		dp = find_delegation_stateid(ino, stateid);
		if (!dp)
			goto out;
		status = check_stateid_generation(stateid, &dp->dl_stateid,
						  flags);
		if (status)
			goto out;
		status = nfs4_check_delegmode(dp, flags);
		if (status)
			goto out;
		renew_client(dp->dl_client);
		if (filpp)
			*filpp = find_readable_file(dp->dl_file);
		BUG_ON(!*filpp);
	} else { /* open or lock stateid */
		stp = find_stateid(stateid, flags);
		if (!stp)
			goto out;
		status = nfserr_bad_stateid;
		if (nfs4_check_fh(current_fh, stp))
			goto out;
		if (!stp->st_stateowner->so_confirmed)
			goto out;
		status = check_stateid_generation(stateid, &stp->st_stateid,
						  flags);
		if (status)
			goto out;
		status = nfs4_check_openmode(stp, flags);
		if (status)
			goto out;
		renew_client(stp->st_stateowner->so_client);
		if (filpp) {
			if (flags & RD_STATE)
				*filpp = find_readable_file(stp->st_file);
			else
				*filpp = find_writeable_file(stp->st_file);
		}
	}
	status = nfs_ok;
out:
	return status;
}