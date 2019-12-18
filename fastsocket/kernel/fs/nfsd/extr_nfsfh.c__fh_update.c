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
struct TYPE_3__ {int fh_size; int /*<<< orphan*/  fh_fileid_type; scalar_t__ fh_auth; } ;
struct svc_fh {int fh_maxsize; TYPE_1__ fh_handle; } ;
struct TYPE_4__ {struct dentry* dentry; } ;
struct svc_export {int ex_flags; TYPE_2__ ex_path; } ;
struct fid {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILEID_ROOT ; 
 int NFSEXP_NOSUBTREECHECK ; 
 int /*<<< orphan*/  exportfs_encode_fh (struct dentry*,struct fid*,int*,int) ; 

__attribute__((used)) static void _fh_update(struct svc_fh *fhp, struct svc_export *exp,
		struct dentry *dentry)
{
	if (dentry != exp->ex_path.dentry) {
		struct fid *fid = (struct fid *)
			(fhp->fh_handle.fh_auth + fhp->fh_handle.fh_size/4 - 1);
		int maxsize = (fhp->fh_maxsize - fhp->fh_handle.fh_size)/4;
		int subtreecheck = !(exp->ex_flags & NFSEXP_NOSUBTREECHECK);

		fhp->fh_handle.fh_fileid_type =
			exportfs_encode_fh(dentry, fid, &maxsize, subtreecheck);
		fhp->fh_handle.fh_size += maxsize * 4;
	} else {
		fhp->fh_handle.fh_fileid_type = FILEID_ROOT;
	}
}