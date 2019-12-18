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
struct svc_rqst {int dummy; } ;
struct svc_fh {int /*<<< orphan*/  fh_export; struct dentry* fh_dentry; } ;
struct iattr {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  NFSD_MAY_CREATE ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int commit_metadata (struct svc_fh*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 scalar_t__ fh_compose (struct svc_fh*,int /*<<< orphan*/ ,struct dentry*,struct svc_fh*) ; 
 int /*<<< orphan*/  fh_drop_write (struct svc_fh*) ; 
 int /*<<< orphan*/  fh_lock (struct svc_fh*) ; 
 int /*<<< orphan*/  fh_unlock (struct svc_fh*) ; 
 scalar_t__ fh_verify (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fh_want_write (struct svc_fh*) ; 
 scalar_t__ isdotent (char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct dentry* lookup_one_len (char*,struct dentry*,int) ; 
 scalar_t__ nfserr_exist ; 
 scalar_t__ nfserr_noent ; 
 scalar_t__ nfserrno (int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 scalar_t__ unlikely (int) ; 
 int vfs_symlink (int /*<<< orphan*/ ,struct dentry*,char*) ; 

__be32
nfsd_symlink(struct svc_rqst *rqstp, struct svc_fh *fhp,
				char *fname, int flen,
				char *path,  int plen,
				struct svc_fh *resfhp,
				struct iattr *iap)
{
	struct dentry	*dentry, *dnew;
	__be32		err, cerr;
	int		host_err;

	err = nfserr_noent;
	if (!flen || !plen)
		goto out;
	err = nfserr_exist;
	if (isdotent(fname, flen))
		goto out;

	err = fh_verify(rqstp, fhp, S_IFDIR, NFSD_MAY_CREATE);
	if (err)
		goto out;

	host_err = fh_want_write(fhp);
	if (host_err)
		goto out_nfserr;

	fh_lock(fhp);
	dentry = fhp->fh_dentry;
	dnew = lookup_one_len(fname, dentry, flen);
	host_err = PTR_ERR(dnew);
	if (IS_ERR(dnew))
		goto out_nfserr;

	if (unlikely(path[plen] != 0)) {
		char *path_alloced = kmalloc(plen+1, GFP_KERNEL);
		if (path_alloced == NULL)
			host_err = -ENOMEM;
		else {
			strncpy(path_alloced, path, plen);
			path_alloced[plen] = 0;
			host_err = vfs_symlink(dentry->d_inode, dnew, path_alloced);
			kfree(path_alloced);
		}
	} else
		host_err = vfs_symlink(dentry->d_inode, dnew, path);
	err = nfserrno(host_err);
	if (!err)
		err = nfserrno(commit_metadata(fhp));
	fh_unlock(fhp);

	fh_drop_write(fhp);

	cerr = fh_compose(resfhp, fhp->fh_export, dnew, fhp);
	dput(dnew);
	if (err==0) err = cerr;
out:
	return err;

out_nfserr:
	err = nfserrno(host_err);
	goto out;
}