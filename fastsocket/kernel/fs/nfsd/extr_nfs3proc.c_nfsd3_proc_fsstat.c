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
struct nfsd_fhandle {int /*<<< orphan*/  fh; } ;
struct nfsd3_fsstatres {int /*<<< orphan*/  stats; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_statfs (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
nfsd3_proc_fsstat(struct svc_rqst * rqstp, struct nfsd_fhandle    *argp,
					   struct nfsd3_fsstatres *resp)
{
	__be32	nfserr;

	dprintk("nfsd: FSSTAT(3)   %s\n",
				SVCFH_fmt(&argp->fh));

	nfserr = nfsd_statfs(rqstp, &argp->fh, &resp->stats, 0);
	fh_put(&argp->fh);
	RETURN_STATUS(nfserr);
}