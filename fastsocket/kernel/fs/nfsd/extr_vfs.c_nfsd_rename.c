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
struct svc_rqst {int rq_vers; } ;
struct svc_fh {int fh_locked; TYPE_2__* fh_export; struct dentry* fh_dentry; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; int /*<<< orphan*/  d_count; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_3__ {scalar_t__ mnt; } ;
struct TYPE_4__ {TYPE_1__ ex_path; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOTEMPTY ; 
 int EPERM ; 
 int EXDEV ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  NFSD_MAY_CREATE ; 
 int /*<<< orphan*/  NFSD_MAY_REMOVE ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int commit_metadata (struct svc_fh*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  fh_drop_write (struct svc_fh*) ; 
 scalar_t__ fh_verify (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fh_want_write (struct svc_fh*) ; 
 int /*<<< orphan*/  fill_post_wcc (struct svc_fh*) ; 
 int /*<<< orphan*/  fill_pre_wcc (struct svc_fh*) ; 
 scalar_t__ isdotent (char*,int) ; 
 struct dentry* lock_rename (struct dentry*,struct dentry*) ; 
 struct dentry* lookup_one_len (char*,struct dentry*,int) ; 
 int nfsd_break_lease (struct inode*) ; 
 scalar_t__ nfserr_acces ; 
 scalar_t__ nfserr_perm ; 
 scalar_t__ nfserr_xdev ; 
 scalar_t__ nfserrno (int) ; 
 scalar_t__ svc_msnfs (struct svc_fh*) ; 
 int /*<<< orphan*/  unlock_rename (struct dentry*,struct dentry*) ; 
 int vfs_rename (struct inode*,struct dentry*,struct inode*,struct dentry*) ; 

__be32
nfsd_rename(struct svc_rqst *rqstp, struct svc_fh *ffhp, char *fname, int flen,
			    struct svc_fh *tfhp, char *tname, int tlen)
{
	struct dentry	*fdentry, *tdentry, *odentry, *ndentry, *trap;
	struct inode	*fdir, *tdir;
	__be32		err;
	int		host_err;

	err = fh_verify(rqstp, ffhp, S_IFDIR, NFSD_MAY_REMOVE);
	if (err)
		goto out;
	err = fh_verify(rqstp, tfhp, S_IFDIR, NFSD_MAY_CREATE);
	if (err)
		goto out;

	fdentry = ffhp->fh_dentry;
	fdir = fdentry->d_inode;

	tdentry = tfhp->fh_dentry;
	tdir = tdentry->d_inode;

	err = (rqstp->rq_vers == 2) ? nfserr_acces : nfserr_xdev;
	if (ffhp->fh_export != tfhp->fh_export)
		goto out;

	err = nfserr_perm;
	if (!flen || isdotent(fname, flen) || !tlen || isdotent(tname, tlen))
		goto out;

	host_err = fh_want_write(ffhp);
	if (host_err) {
		err = nfserrno(host_err);
		goto out;
	}

	/* cannot use fh_lock as we need deadlock protective ordering
	 * so do it by hand */
	trap = lock_rename(tdentry, fdentry);
	ffhp->fh_locked = tfhp->fh_locked = 1;
	fill_pre_wcc(ffhp);
	fill_pre_wcc(tfhp);

	odentry = lookup_one_len(fname, fdentry, flen);
	host_err = PTR_ERR(odentry);
	if (IS_ERR(odentry))
		goto out_nfserr;

	host_err = -ENOENT;
	if (!odentry->d_inode)
		goto out_dput_old;
	host_err = -EINVAL;
	if (odentry == trap)
		goto out_dput_old;

	ndentry = lookup_one_len(tname, tdentry, tlen);
	host_err = PTR_ERR(ndentry);
	if (IS_ERR(ndentry))
		goto out_dput_old;
	host_err = -ENOTEMPTY;
	if (ndentry == trap)
		goto out_dput_new;

	if (svc_msnfs(ffhp) &&
		((atomic_read(&odentry->d_count) > 1)
		 || (atomic_read(&ndentry->d_count) > 1))) {
			host_err = -EPERM;
			goto out_dput_new;
	}

	host_err = -EXDEV;
	if (ffhp->fh_export->ex_path.mnt != tfhp->fh_export->ex_path.mnt)
		goto out_dput_new;

	host_err = nfsd_break_lease(odentry->d_inode);
	if (host_err)
		goto out_dput_new;
	if (ndentry->d_inode) {
		host_err = nfsd_break_lease(ndentry->d_inode);
		if (host_err)
			goto out_dput_new;
	}
	host_err = vfs_rename(fdir, odentry, tdir, ndentry);
	if (!host_err) {
		host_err = commit_metadata(tfhp);
		if (!host_err)
			host_err = commit_metadata(ffhp);
	}
 out_dput_new:
	dput(ndentry);
 out_dput_old:
	dput(odentry);
 out_nfserr:
	err = nfserrno(host_err);

	/* we cannot reply on fh_unlock on the two filehandles,
	 * as that would do the wrong thing if the two directories
	 * were the same, so again we do it by hand
	 */
	fill_post_wcc(ffhp);
	fill_post_wcc(tfhp);
	unlock_rename(tdentry, fdentry);
	ffhp->fh_locked = tfhp->fh_locked = 0;
	fh_drop_write(ffhp);

out:
	return err;
}