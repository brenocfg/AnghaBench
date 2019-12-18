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
struct nfsd3_commitres {int /*<<< orphan*/  fh; } ;
struct nfsd3_commitargs {scalar_t__ offset; int /*<<< orphan*/  count; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ NFS_OFFSET_MAX ; 
 int /*<<< orphan*/  RETURN_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_commit (struct svc_rqst*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfserr_inval ; 

__attribute__((used)) static __be32
nfsd3_proc_commit(struct svc_rqst * rqstp, struct nfsd3_commitargs *argp,
					   struct nfsd3_commitres  *resp)
{
	__be32	nfserr;

	dprintk("nfsd: COMMIT(3)   %s %u@%Lu\n",
				SVCFH_fmt(&argp->fh),
				argp->count,
				(unsigned long long) argp->offset);

	if (argp->offset > NFS_OFFSET_MAX)
		RETURN_STATUS(nfserr_inval);

	fh_copy(&resp->fh, &argp->fh);
	nfserr = nfsd_commit(rqstp, &resp->fh, argp->offset, argp->count);

	RETURN_STATUS(nfserr);
}