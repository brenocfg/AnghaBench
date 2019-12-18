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
struct svc_rqst {int dummy; } ;
struct nfsd4_locku {scalar_t__ lu_stateowner; int /*<<< orphan*/  lu_stateid; scalar_t__ lu_length; scalar_t__ lu_offset; int /*<<< orphan*/  lu_seqid; } ;
struct nfsd4_compound_state {scalar_t__ replay_owner; } ;
struct nfs4_stateid {int /*<<< orphan*/  st_stateid; int /*<<< orphan*/  st_file; } ;
struct file_lock {int /*<<< orphan*/  fl_end; scalar_t__ fl_start; int /*<<< orphan*/ * fl_lmops; int /*<<< orphan*/  fl_flags; struct file* fl_file; int /*<<< orphan*/  fl_pid; scalar_t__ fl_owner; int /*<<< orphan*/  fl_type; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  stateid_t ;
typedef  scalar_t__ fl_owner_t ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  tgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  FL_POSIX ; 
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  LOCK_STATE ; 
 scalar_t__ check_lock_length (scalar_t__,scalar_t__) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 struct file* find_any_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  last_byte_offset (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  locks_init_lock (struct file_lock*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfs4_get_stateowner (scalar_t__) ; 
 int /*<<< orphan*/  nfs4_lock_state () ; 
 int /*<<< orphan*/  nfs4_preprocess_seqid_op (struct nfsd4_compound_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,struct nfs4_stateid**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_transform_lock_offset (struct file_lock*) ; 
 int /*<<< orphan*/  nfs4_unlock_state () ; 
 int /*<<< orphan*/  nfsd_posix_mng_ops ; 
 int /*<<< orphan*/  nfserr_inval ; 
 int /*<<< orphan*/  nfserr_lock_range ; 
 int /*<<< orphan*/  nfserrno (int) ; 
 int /*<<< orphan*/  update_stateid (int /*<<< orphan*/ *) ; 
 int vfs_lock_file (struct file*,int /*<<< orphan*/ ,struct file_lock*,int /*<<< orphan*/ *) ; 

__be32
nfsd4_locku(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	    struct nfsd4_locku *locku)
{
	struct nfs4_stateid *stp;
	struct file *filp = NULL;
	struct file_lock file_lock;
	__be32 status;
	int err;
						        
	dprintk("NFSD: nfsd4_locku: start=%Ld length=%Ld\n",
		(long long) locku->lu_offset,
		(long long) locku->lu_length);

	if (check_lock_length(locku->lu_offset, locku->lu_length))
		 return nfserr_inval;

	nfs4_lock_state();
									        
	if ((status = nfs4_preprocess_seqid_op(cstate,
					locku->lu_seqid, 
					&locku->lu_stateid, 
					LOCK_STATE,
					&locku->lu_stateowner, &stp, NULL)))
		goto out;

	filp = find_any_file(stp->st_file);
	if (!filp) {
		status = nfserr_lock_range;
		goto out;
	}
	BUG_ON(!filp);
	locks_init_lock(&file_lock);
	file_lock.fl_type = F_UNLCK;
	file_lock.fl_owner = (fl_owner_t) locku->lu_stateowner;
	file_lock.fl_pid = current->tgid;
	file_lock.fl_file = filp;
	file_lock.fl_flags = FL_POSIX; 
	file_lock.fl_lmops = &nfsd_posix_mng_ops;
	file_lock.fl_start = locku->lu_offset;

	file_lock.fl_end = last_byte_offset(locku->lu_offset, locku->lu_length);
	nfs4_transform_lock_offset(&file_lock);

	/*
	*  Try to unlock the file in the VFS.
	*/
	err = vfs_lock_file(filp, F_SETLK, &file_lock, NULL);
	if (err) {
		dprintk("NFSD: nfs4_locku: vfs_lock_file failed!\n");
		goto out_nfserr;
	}
	/*
	* OK, unlock succeeded; the only thing left to do is update the stateid.
	*/
	update_stateid(&stp->st_stateid);
	memcpy(&locku->lu_stateid, &stp->st_stateid, sizeof(stateid_t));

out:
	if (locku->lu_stateowner) {
		nfs4_get_stateowner(locku->lu_stateowner);
		cstate->replay_owner = locku->lu_stateowner;
	}
	nfs4_unlock_state();
	return status;

out_nfserr:
	status = nfserrno(err);
	goto out;
}