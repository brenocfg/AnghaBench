#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
struct nfsmount {scalar_t__ nm_vers; } ;
struct nfs_open_file {scalar_t__ nof_owner; } ;
struct nfs_lock_owner {int /*<<< orphan*/  nlo_pid; scalar_t__ nlo_open_owner; } ;
struct nfs_file_lock {int nfl_flags; int /*<<< orphan*/  nfl_type; int /*<<< orphan*/  nfl_end; int /*<<< orphan*/  nfl_start; struct nfs_lock_owner* nfl_owner; } ;
typedef  TYPE_2__* nfsnode_t ;
typedef  int /*<<< orphan*/  msgreq ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_10__ {int /*<<< orphan*/  l_pid; int /*<<< orphan*/  l_type; int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_start; int /*<<< orphan*/  l_whence; } ;
struct TYPE_13__ {TYPE_1__ lm_fl; int /*<<< orphan*/  lm_cred; int /*<<< orphan*/  lm_fh_len; int /*<<< orphan*/  lm_fh; int /*<<< orphan*/  lm_flags; int /*<<< orphan*/  lm_version; } ;
struct TYPE_12__ {TYPE_4__ lmr_msg; } ;
struct TYPE_11__ {int /*<<< orphan*/  n_fhp; int /*<<< orphan*/  n_fhsize; } ;
typedef  TYPE_3__ LOCKD_MSG_REQUEST ;
typedef  TYPE_4__ LOCKD_MSG ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  LOCKD_MSG_BLOCK ; 
 int /*<<< orphan*/  LOCKD_MSG_RECLAIM ; 
 int /*<<< orphan*/  LOCKD_MSG_VERSION ; 
 struct nfsmount* NFSTONMP (TYPE_2__*) ; 
 int /*<<< orphan*/  NFSX_V2FH ; 
 int NFS_FILE_LOCK_WAIT ; 
 int /*<<< orphan*/  NFS_FLOCK_LENGTH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NFS_VER2 ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  cru2x (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nfs3_lockd_request (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_lock_owner_clear_busy (struct nfs_lock_owner*) ; 
 int nfs_lock_owner_set_busy (struct nfs_lock_owner*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int /*<<< orphan*/  nfs_open_owner_ref (scalar_t__) ; 

int
nfs3_setlock_rpc(
	nfsnode_t np,
	struct nfs_open_file *nofp,
	struct nfs_file_lock *nflp,
	int reclaim,
	int flags,
	thread_t thd,
	kauth_cred_t cred)
{
	struct nfs_lock_owner *nlop = nflp->nfl_owner;
	struct nfsmount *nmp;
	int error;
	LOCKD_MSG_REQUEST msgreq;
	LOCKD_MSG *msg;

	nmp = NFSTONMP(np);
	if (nfs_mount_gone(nmp))
		return (ENXIO);

	if (!nlop->nlo_open_owner) {
		nfs_open_owner_ref(nofp->nof_owner);
		nlop->nlo_open_owner = nofp->nof_owner;
	}
	if ((error = nfs_lock_owner_set_busy(nlop, thd)))
		return (error);

	/* set up lock message request structure */
	bzero(&msgreq, sizeof(msgreq));
	msg = &msgreq.lmr_msg;
	msg->lm_version = LOCKD_MSG_VERSION;
	if ((nflp->nfl_flags & NFS_FILE_LOCK_WAIT) && !reclaim)
		msg->lm_flags |= LOCKD_MSG_BLOCK;
	if (reclaim)
		msg->lm_flags |= LOCKD_MSG_RECLAIM;
	msg->lm_fh_len = (nmp->nm_vers == NFS_VER2) ? NFSX_V2FH : np->n_fhsize;
	bcopy(np->n_fhp, msg->lm_fh, msg->lm_fh_len);
	cru2x(cred, &msg->lm_cred);

	msg->lm_fl.l_whence = SEEK_SET;
	msg->lm_fl.l_start = nflp->nfl_start;
	msg->lm_fl.l_len = NFS_FLOCK_LENGTH(nflp->nfl_start, nflp->nfl_end);
	msg->lm_fl.l_type = nflp->nfl_type;
	msg->lm_fl.l_pid = nlop->nlo_pid;

	error = nfs3_lockd_request(np, 0, &msgreq, flags, thd);

	nfs_lock_owner_clear_busy(nlop);
	return (error);
}