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
struct svc_fh {int /*<<< orphan*/  fh_dentry; TYPE_2__* fh_export; } ;
struct kstat {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  mnt; } ;
struct TYPE_4__ {TYPE_1__ ex_path; } ;

/* Variables and functions */
 int /*<<< orphan*/ * encode_fattr (struct svc_rqst*,int /*<<< orphan*/ *,struct svc_fh*,struct kstat*) ; 
 int /*<<< orphan*/  vfs_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct kstat*) ; 

__be32 *nfs2svc_encode_fattr(struct svc_rqst *rqstp, __be32 *p, struct svc_fh *fhp)
{
	struct kstat stat;
	vfs_getattr(fhp->fh_export->ex_path.mnt, fhp->fh_dentry, &stat);
	return encode_fattr(rqstp, p, fhp, &stat);
}