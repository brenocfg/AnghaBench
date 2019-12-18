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
struct svc_fh {TYPE_2__* fh_export; struct dentry* fh_dentry; } ;
struct inode {int /*<<< orphan*/  i_fop; int /*<<< orphan*/  i_mode; } ;
struct file {int /*<<< orphan*/  f_mode; } ;
struct dentry {struct inode* d_inode; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  mnt; } ;
struct TYPE_4__ {TYPE_1__ ex_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMODE_32BITHASH ; 
 int /*<<< orphan*/  FMODE_64BITHASH ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int NFSD_MAY_64BIT_COOKIE ; 
 int NFSD_MAY_NOT_BREAK_LEASE ; 
 int NFSD_MAY_OWNER_OVERRIDE ; 
 int NFSD_MAY_READ ; 
 int NFSD_MAY_WRITE ; 
 int O_LARGEFILE ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_WRONLY ; 
 int PTR_ERR (struct file*) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int break_lease (struct inode*,int) ; 
 int /*<<< orphan*/  current_cred () ; 
 struct file* dentry_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 scalar_t__ fh_verify (struct svc_rqst*,struct svc_fh*,int,int) ; 
 int ima_file_check (struct file*,int) ; 
 scalar_t__ mandatory_lock (struct inode*) ; 
 int /*<<< orphan*/  mntget (int /*<<< orphan*/ ) ; 
 scalar_t__ nfserr_perm ; 
 scalar_t__ nfserrno (int) ; 
 int /*<<< orphan*/  validate_process_creds () ; 
 int /*<<< orphan*/  vfs_dq_init (struct inode*) ; 

__be32
nfsd_open(struct svc_rqst *rqstp, struct svc_fh *fhp, int type,
			int may_flags, struct file **filp)
{
	struct dentry	*dentry;
	struct inode	*inode;
	int		flags = O_RDONLY|O_LARGEFILE;
	__be32		err;
	int		host_err = 0;

	validate_process_creds();

	/*
	 * If we get here, then the client has already done an "open",
	 * and (hopefully) checked permission - so allow OWNER_OVERRIDE
	 * in case a chmod has now revoked permission.
	 */
	err = fh_verify(rqstp, fhp, type, may_flags | NFSD_MAY_OWNER_OVERRIDE);
	if (err)
		goto out;

	dentry = fhp->fh_dentry;
	inode = dentry->d_inode;

	/* Disallow write access to files with the append-only bit set
	 * or any access when mandatory locking enabled
	 */
	err = nfserr_perm;
	if (IS_APPEND(inode) && (may_flags & NFSD_MAY_WRITE))
		goto out;
	/*
	 * We must ignore files (but only files) which might have mandatory
	 * locks on them because there is no way to know if the accesser has
	 * the lock.
	 */
	if (S_ISREG((inode)->i_mode) && mandatory_lock(inode))
		goto out;

	if (!inode->i_fop)
		goto out;

	/*
	 * Check to see if there are any leases on this file.
	 * This may block while leases are broken.
	 */
	if (!(may_flags & NFSD_MAY_NOT_BREAK_LEASE))
		host_err = break_lease(inode, O_NONBLOCK | ((may_flags & NFSD_MAY_WRITE) ? O_WRONLY : 0));
	if (host_err) /* NOMEM or WOULDBLOCK */
		goto out_nfserr;

	if (may_flags & NFSD_MAY_WRITE) {
		if (may_flags & NFSD_MAY_READ)
			flags = O_RDWR|O_LARGEFILE;
		else
			flags = O_WRONLY|O_LARGEFILE;

		vfs_dq_init(inode);
	}
	*filp = dentry_open(dget(dentry), mntget(fhp->fh_export->ex_path.mnt),
			    flags, current_cred());
	if (IS_ERR(*filp)) {
		host_err = PTR_ERR(*filp);
		*filp = NULL;
	} else {
		host_err = ima_file_check(*filp, may_flags);

		if (may_flags & NFSD_MAY_64BIT_COOKIE)
			(*filp)->f_mode |= FMODE_64BITHASH;
		else
			(*filp)->f_mode |= FMODE_32BITHASH;
	}

out_nfserr:
	err = nfserrno(host_err);
out:
	validate_process_creds();
	return err;
}