#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct svc_rqst {int dummy; } ;
struct nfsd4_lockt {int lt_type; int /*<<< orphan*/  lt_denied; int /*<<< orphan*/  lt_length; int /*<<< orphan*/  lt_offset; int /*<<< orphan*/ * lt_stateowner; int /*<<< orphan*/  lt_owner; int /*<<< orphan*/  lt_clientid; } ;
struct TYPE_6__ {TYPE_1__* fh_dentry; } ;
struct nfsd4_compound_state {TYPE_2__ current_fh; } ;
struct inode {int dummy; } ;
struct file_lock {scalar_t__ fl_type; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_start; int /*<<< orphan*/  fl_flags; int /*<<< orphan*/  fl_pid; scalar_t__ fl_owner; } ;
typedef  scalar_t__ fl_owner_t ;
typedef  scalar_t__ __be32 ;
struct TYPE_7__ {int /*<<< orphan*/  tgid; } ;
struct TYPE_5__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FL_POSIX ; 
 scalar_t__ F_RDLCK ; 
 scalar_t__ F_UNLCK ; 
 scalar_t__ F_WRLCK ; 
#define  NFS4_READW_LT 131 
#define  NFS4_READ_LT 130 
#define  NFS4_WRITEW_LT 129 
#define  NFS4_WRITE_LT 128 
 scalar_t__ STALE_CLIENTID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_IFREG ; 
 scalar_t__ check_lock_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 scalar_t__ fh_verify (struct svc_rqst*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_lockstateowner_str (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  last_byte_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ locks_in_grace () ; 
 int /*<<< orphan*/  locks_init_lock (struct file_lock*) ; 
 int /*<<< orphan*/  nfs4_lock_state () ; 
 int /*<<< orphan*/  nfs4_set_lock_denied (struct file_lock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_transform_lock_offset (struct file_lock*) ; 
 int /*<<< orphan*/  nfs4_unlock_state () ; 
 scalar_t__ nfs_ok ; 
 int /*<<< orphan*/  nfsd4_has_session (struct nfsd4_compound_state*) ; 
 int nfsd_test_lock (struct svc_rqst*,TYPE_2__*,struct file_lock*) ; 
 scalar_t__ nfserr_denied ; 
 scalar_t__ nfserr_grace ; 
 scalar_t__ nfserr_inval ; 
 scalar_t__ nfserr_stale_clientid ; 
 scalar_t__ nfserr_symlink ; 
 scalar_t__ nfserrno (int) ; 

__be32
nfsd4_lockt(struct svc_rqst *rqstp, struct nfsd4_compound_state *cstate,
	    struct nfsd4_lockt *lockt)
{
	struct inode *inode;
	struct file_lock file_lock;
	int error;
	__be32 status;

	if (locks_in_grace())
		return nfserr_grace;

	if (check_lock_length(lockt->lt_offset, lockt->lt_length))
		 return nfserr_inval;

	lockt->lt_stateowner = NULL;
	nfs4_lock_state();

	status = nfserr_stale_clientid;
	if (!nfsd4_has_session(cstate) && STALE_CLIENTID(&lockt->lt_clientid))
		goto out;

	if ((status = fh_verify(rqstp, &cstate->current_fh, S_IFREG, 0))) {
		dprintk("NFSD: nfsd4_lockt: fh_verify() failed!\n");
		if (status == nfserr_symlink)
			status = nfserr_inval;
		goto out;
	}

	inode = cstate->current_fh.fh_dentry->d_inode;
	locks_init_lock(&file_lock);
	switch (lockt->lt_type) {
		case NFS4_READ_LT:
		case NFS4_READW_LT:
			file_lock.fl_type = F_RDLCK;
		break;
		case NFS4_WRITE_LT:
		case NFS4_WRITEW_LT:
			file_lock.fl_type = F_WRLCK;
		break;
		default:
			dprintk("NFSD: nfs4_lockt: bad lock type!\n");
			status = nfserr_inval;
		goto out;
	}

	lockt->lt_stateowner = find_lockstateowner_str(inode,
			&lockt->lt_clientid, &lockt->lt_owner);
	if (lockt->lt_stateowner)
		file_lock.fl_owner = (fl_owner_t)lockt->lt_stateowner;
	file_lock.fl_pid = current->tgid;
	file_lock.fl_flags = FL_POSIX;

	file_lock.fl_start = lockt->lt_offset;
	file_lock.fl_end = last_byte_offset(lockt->lt_offset, lockt->lt_length);

	nfs4_transform_lock_offset(&file_lock);

	status = nfs_ok;
	error = nfsd_test_lock(rqstp, &cstate->current_fh, &file_lock);
	if (error) {
		status = nfserrno(error);
		goto out;
	}
	if (file_lock.fl_type != F_UNLCK) {
		status = nfserr_denied;
		nfs4_set_lock_denied(&file_lock, &lockt->lt_denied);
	}
out:
	nfs4_unlock_state();
	return status;
}