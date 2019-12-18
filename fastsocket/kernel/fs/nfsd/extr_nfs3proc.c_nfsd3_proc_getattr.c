#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct svc_rqst {int dummy; } ;
struct nfsd_fhandle {int /*<<< orphan*/  fh; } ;
struct TYPE_7__ {int /*<<< orphan*/  fh_dentry; TYPE_2__* fh_export; } ;
struct nfsd3_attrstat {int /*<<< orphan*/  stat; TYPE_3__ fh; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_5__ {int /*<<< orphan*/  mnt; } ;
struct TYPE_6__ {TYPE_1__ ex_path; } ;

/* Variables and functions */
 int NFSD_MAY_BYPASS_GSS_ON_ROOT ; 
 int NFSD_MAY_NOP ; 
 int /*<<< orphan*/  RETURN_STATUS (scalar_t__) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_copy (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ fh_verify (struct svc_rqst*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nfserrno (int) ; 
 int vfs_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd3_proc_getattr(struct svc_rqst *rqstp, struct nfsd_fhandle  *argp,
					   struct nfsd3_attrstat *resp)
{
	int	err;
	__be32	nfserr;

	dprintk("nfsd: GETATTR(3)  %s\n",
		SVCFH_fmt(&argp->fh));

	fh_copy(&resp->fh, &argp->fh);
	nfserr = fh_verify(rqstp, &resp->fh, 0,
			NFSD_MAY_NOP | NFSD_MAY_BYPASS_GSS_ON_ROOT);
	if (nfserr)
		RETURN_STATUS(nfserr);

	err = vfs_getattr(resp->fh.fh_export->ex_path.mnt,
			  resp->fh.fh_dentry, &resp->stat);
	nfserr = nfserrno(err);

	RETURN_STATUS(nfserr);
}