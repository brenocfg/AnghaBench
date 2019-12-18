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
struct svc_rqst {int rq_vers; } ;
struct svc_fh {struct dentry* fh_dentry; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int EXDEV ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int /*<<< orphan*/  NFSD_MAY_CREATE ; 
 int /*<<< orphan*/  NFSD_MAY_NOP ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int commit_metadata (struct svc_fh*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  fh_drop_write (struct svc_fh*) ; 
 int /*<<< orphan*/  fh_lock_nested (struct svc_fh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_unlock (struct svc_fh*) ; 
 scalar_t__ fh_verify (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fh_want_write (struct svc_fh*) ; 
 scalar_t__ isdotent (char*,int) ; 
 struct dentry* lookup_one_len (char*,struct dentry*,int) ; 
 int nfsd_break_lease (struct inode*) ; 
 scalar_t__ nfserr_acces ; 
 scalar_t__ nfserr_exist ; 
 scalar_t__ nfserr_noent ; 
 scalar_t__ nfserr_perm ; 
 scalar_t__ nfserrno (int) ; 
 int vfs_link (struct dentry*,struct inode*,struct dentry*) ; 

__be32
nfsd_link(struct svc_rqst *rqstp, struct svc_fh *ffhp,
				char *name, int len, struct svc_fh *tfhp)
{
	struct dentry	*ddir, *dnew, *dold;
	struct inode	*dirp;
	__be32		err;
	int		host_err;

	err = fh_verify(rqstp, ffhp, S_IFDIR, NFSD_MAY_CREATE);
	if (err)
		goto out;
	err = fh_verify(rqstp, tfhp, -S_IFDIR, NFSD_MAY_NOP);
	if (err)
		goto out;

	err = nfserr_perm;
	if (!len)
		goto out;
	err = nfserr_exist;
	if (isdotent(name, len))
		goto out;

	host_err = fh_want_write(tfhp);
	if (host_err) {
		err = nfserrno(host_err);
		goto out;
	}

	fh_lock_nested(ffhp, I_MUTEX_PARENT);
	ddir = ffhp->fh_dentry;
	dirp = ddir->d_inode;

	dnew = lookup_one_len(name, ddir, len);
	host_err = PTR_ERR(dnew);
	if (IS_ERR(dnew))
		goto out_nfserr;

	dold = tfhp->fh_dentry;

	err = nfserr_noent;
	if (!dold->d_inode)
		goto out_dput;
	host_err = nfsd_break_lease(dold->d_inode);
	if (host_err) {
		err = nfserrno(host_err);
		goto out_dput;
	}
	host_err = vfs_link(dold, dirp, dnew);
	if (!host_err) {
		err = nfserrno(commit_metadata(ffhp));
		if (!err)
			err = nfserrno(commit_metadata(tfhp));
	} else {
		if (host_err == -EXDEV && rqstp->rq_vers == 2)
			err = nfserr_acces;
		else
			err = nfserrno(host_err);
	}
out_dput:
	dput(dnew);
out_unlock:
	fh_unlock(ffhp);
	fh_drop_write(tfhp);
out:
	return err;

out_nfserr:
	err = nfserrno(host_err);
	goto out_unlock;
}