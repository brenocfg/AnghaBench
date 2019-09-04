#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
struct nfsmount {int dummy; } ;
struct nfs_open_owner {int dummy; } ;
struct TYPE_12__ {int seqid; int* other; } ;
struct nfs_open_file {int nof_flags; TYPE_3__ nof_stateid; scalar_t__ nof_access; } ;
struct nfs_lock_owner {TYPE_3__ nlo_stateid; int /*<<< orphan*/  nlo_locks; } ;
typedef  scalar_t__ proc_t ;
typedef  TYPE_2__* nfsnode_t ;
typedef  TYPE_3__ nfs_stateid ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_10__ {int nva_flags; } ;
struct TYPE_11__ {int n_openflags; TYPE_1__ n_vattr; TYPE_3__ n_dstateid; } ;

/* Variables and functions */
 struct nfsmount* NFSTONMP (TYPE_2__*) ; 
 int NFS_FFLAG_IS_ATTR ; 
 int NFS_OPEN_FILE_LOST ; 
 int NFS_OPEN_FILE_REOPEN ; 
 int /*<<< orphan*/  NP (TYPE_2__*,char*) ; 
 int N_DELEG_MASK ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ current_proc () ; 
 scalar_t__ get_bsdthreadtask_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_reopen (struct nfs_open_file*,int /*<<< orphan*/ ) ; 
 struct nfs_lock_owner* nfs_lock_owner_find (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_lock_owner_rele (struct nfs_lock_owner*) ; 
 scalar_t__ nfs_open_file_find (TYPE_2__*,struct nfs_open_owner*,struct nfs_open_file**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfs_open_owner* nfs_open_owner_find (struct nfsmount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_open_owner_rele (struct nfs_open_owner*) ; 

void
nfs_get_stateid(nfsnode_t np, thread_t thd, kauth_cred_t cred, nfs_stateid *sid)
{
	struct nfsmount *nmp = NFSTONMP(np);
	proc_t p = thd ? get_bsdthreadtask_info(thd) : current_proc();  // XXX async I/O requests don't have a thread
	struct nfs_open_owner *noop = NULL;
	struct nfs_open_file *nofp = NULL;
	struct nfs_lock_owner *nlop = NULL;
	nfs_stateid *s = NULL;

	if (np->n_openflags & N_DELEG_MASK) {
		s = &np->n_dstateid;
	} else {
		if (p)
			nlop = nfs_lock_owner_find(np, p, 0);
		if (nlop && !TAILQ_EMPTY(&nlop->nlo_locks)) {
			/* we hold locks, use lock stateid */
			s = &nlop->nlo_stateid;
		} else if (((noop = nfs_open_owner_find(nmp, cred, 0))) &&
			 (nfs_open_file_find(np, noop, &nofp, 0, 0, 0) == 0) &&
			 !(nofp->nof_flags & NFS_OPEN_FILE_LOST) &&
			 nofp->nof_access) {
			/* we (should) have the file open, use open stateid */
			if (nofp->nof_flags & NFS_OPEN_FILE_REOPEN)
				nfs4_reopen(nofp, thd);
			if (!(nofp->nof_flags & NFS_OPEN_FILE_LOST))
				s = &nofp->nof_stateid;
		}
	}

	if (s) {
		sid->seqid = s->seqid;
		sid->other[0] = s->other[0];
		sid->other[1] = s->other[1];
		sid->other[2] = s->other[2];
	} else {
		/* named attributes may not have a stateid for reads, so don't complain for them */
		if (!(np->n_vattr.nva_flags & NFS_FFLAG_IS_ATTR))
			NP(np, "nfs_get_stateid: no stateid");
		sid->seqid = sid->other[0] = sid->other[1] = sid->other[2] = 0xffffffff;
	}
	if (nlop)
		nfs_lock_owner_rele(nlop);
	if (noop)
		nfs_open_owner_rele(noop);
}