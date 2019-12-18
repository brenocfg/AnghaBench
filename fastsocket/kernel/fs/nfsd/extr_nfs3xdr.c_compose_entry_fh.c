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
struct svc_fh {int dummy; } ;
struct svc_export {int dummy; } ;
struct TYPE_2__ {struct svc_export* fh_export; struct dentry* fh_dentry; } ;
struct nfsd3_readdirres {TYPE_1__ fh; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 scalar_t__ d_mountpoint (struct dentry*) ; 
 struct dentry* dget (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int fh_compose (struct svc_fh*,struct svc_export*,struct dentry*,TYPE_1__*) ; 
 scalar_t__ isdotent (char const*,int) ; 
 struct dentry* lookup_one_len (char const*,struct dentry*,int) ; 

__attribute__((used)) static int
compose_entry_fh(struct nfsd3_readdirres *cd, struct svc_fh *fhp,
		const char *name, int namlen)
{
	struct svc_export	*exp;
	struct dentry		*dparent, *dchild;
	int rv = 0;

	dparent = cd->fh.fh_dentry;
	exp  = cd->fh.fh_export;

	if (isdotent(name, namlen)) {
		if (namlen == 2) {
			dchild = dget_parent(dparent);
			if (dchild == dparent) {
				/* filesystem root - cannot return filehandle for ".." */
				dput(dchild);
				return -ENOENT;
			}
		} else
			dchild = dget(dparent);
	} else
		dchild = lookup_one_len(name, dparent, namlen);
	if (IS_ERR(dchild))
		return -ENOENT;
	rv = -ENOENT;
	if (d_mountpoint(dchild))
		goto out;
	rv = fh_compose(fhp, exp, dchild, &cd->fh);
	if (rv)
		goto out;
	if (!dchild->d_inode)
		goto out;
	rv = 0;
out:
	dput(dchild);
	return rv;
}