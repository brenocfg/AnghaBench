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
struct svc_rqst {int /*<<< orphan*/  rq_vec; } ;
struct nfsd_writeargs {unsigned long len; int /*<<< orphan*/  vlen; int /*<<< orphan*/  offset; int /*<<< orphan*/  fh; } ;
struct nfsd_attrstat {int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_return_attrs (int /*<<< orphan*/ ,struct nfsd_attrstat*) ; 
 int /*<<< orphan*/  nfsd_write (struct svc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*,int*) ; 

__attribute__((used)) static __be32
nfsd_proc_write(struct svc_rqst *rqstp, struct nfsd_writeargs *argp,
					struct nfsd_attrstat  *resp)
{
	__be32	nfserr;
	int	stable = 1;
	unsigned long cnt = argp->len;

	dprintk("nfsd: WRITE    %s %d bytes at %d\n",
		SVCFH_fmt(&argp->fh),
		argp->len, argp->offset);

	nfserr = nfsd_write(rqstp, fh_copy(&resp->fh, &argp->fh), NULL,
				   argp->offset,
				   rqstp->rq_vec, argp->vlen,
			           &cnt,
				   &stable);
	return nfsd_return_attrs(nfserr, resp);
}