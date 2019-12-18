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
struct svc_fh {int /*<<< orphan*/  fh_dentry; int /*<<< orphan*/  fh_export; } ;
struct kvec {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int NFSD_MAY_OWNER_OVERRIDE ; 
 int NFSD_MAY_READ ; 
 scalar_t__ nfsd_permission (struct svc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nfsd_read (struct svc_rqst*,struct svc_fh*,int /*<<< orphan*/ ,struct kvec*,int,unsigned long*) ; 
 scalar_t__ nfsd_vfs_read (struct svc_rqst*,struct svc_fh*,struct file*,int /*<<< orphan*/ ,struct kvec*,int,unsigned long*) ; 

__be32
nfsd_read_file(struct svc_rqst *rqstp, struct svc_fh *fhp, struct file *file,
		loff_t offset, struct kvec *vec, int vlen,
		unsigned long *count)
{
	__be32		err;

	if (file) {
		err = nfsd_permission(rqstp, fhp->fh_export, fhp->fh_dentry,
				NFSD_MAY_READ|NFSD_MAY_OWNER_OVERRIDE);
		if (err)
			goto out;
		err = nfsd_vfs_read(rqstp, fhp, file, offset, vec, vlen, count);
	} else /* Note file may still be NULL in NFSv4 special stateid case: */
		err = nfsd_read(rqstp, fhp, offset, vec, vlen, count);
out:
	return err;
}