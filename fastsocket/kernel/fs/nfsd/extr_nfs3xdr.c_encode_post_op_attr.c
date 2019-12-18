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
struct kstat {int /*<<< orphan*/  mtime; } ;
struct dentry {scalar_t__ d_inode; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  mnt; } ;
struct TYPE_4__ {TYPE_1__ ex_path; } ;

/* Variables and functions */
 int /*<<< orphan*/ * encode_fattr3 (struct svc_rqst*,int /*<<< orphan*/ *,struct svc_fh*,struct kstat*) ; 
 int /*<<< orphan*/  lease_get_mtime (scalar_t__,int /*<<< orphan*/ *) ; 
 int vfs_getattr (int /*<<< orphan*/ ,struct dentry*,struct kstat*) ; 
 int /*<<< orphan*/  xdr_one ; 
 int /*<<< orphan*/  xdr_zero ; 

__attribute__((used)) static __be32 *
encode_post_op_attr(struct svc_rqst *rqstp, __be32 *p, struct svc_fh *fhp)
{
	struct dentry *dentry = fhp->fh_dentry;
	if (dentry && dentry->d_inode) {
	        int err;
		struct kstat stat;

		err = vfs_getattr(fhp->fh_export->ex_path.mnt, dentry, &stat);
		if (!err) {
			*p++ = xdr_one;		/* attributes follow */
			lease_get_mtime(dentry->d_inode, &stat.mtime);
			return encode_fattr3(rqstp, p, fhp, &stat);
		}
	}
	*p++ = xdr_zero;
	return p;
}