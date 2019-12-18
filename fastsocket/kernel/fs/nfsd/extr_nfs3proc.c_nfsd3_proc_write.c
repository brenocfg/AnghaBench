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
struct nfsd3_writeres {unsigned long count; scalar_t__ committed; int /*<<< orphan*/  fh; } ;
struct nfsd3_writeargs {unsigned long len; int /*<<< orphan*/  vlen; scalar_t__ offset; scalar_t__ stable; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,unsigned long,unsigned long,char*) ; 
 int /*<<< orphan*/  fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_write (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*,scalar_t__*) ; 

__attribute__((used)) static __be32
nfsd3_proc_write(struct svc_rqst *rqstp, struct nfsd3_writeargs *argp,
					 struct nfsd3_writeres  *resp)
{
	__be32	nfserr;
	unsigned long cnt = argp->len;

	dprintk("nfsd: WRITE(3)    %s %d bytes at %ld%s\n",
				SVCFH_fmt(&argp->fh),
				argp->len,
				(unsigned long) argp->offset,
				argp->stable? " stable" : "");

	fh_copy(&resp->fh, &argp->fh);
	resp->committed = argp->stable;
	nfserr = nfsd_write(rqstp, &resp->fh, NULL,
				   argp->offset,
				   rqstp->rq_vec, argp->vlen,
				   &cnt,
				   &resp->committed);
	resp->count = cnt;
	RETURN_STATUS(nfserr);
}