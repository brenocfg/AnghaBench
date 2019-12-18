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
typedef  int /*<<< orphan*/  u32 ;
struct svc_rqst {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  err; } ;
struct nfsd3_readdirres {int buflen; scalar_t__ offset; scalar_t__ buffer; scalar_t__ count; int /*<<< orphan*/  verf; TYPE_1__ common; int /*<<< orphan*/  fh; struct svc_rqst* rqstp; } ;
struct nfsd3_readdirargs {int count; scalar_t__ cookie; scalar_t__ buffer; int /*<<< orphan*/  verf; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs3svc_encode_entry ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfsd_readdir (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdr_encode_hyper (scalar_t__,scalar_t__) ; 

__attribute__((used)) static __be32
nfsd3_proc_readdir(struct svc_rqst *rqstp, struct nfsd3_readdirargs *argp,
					   struct nfsd3_readdirres  *resp)
{
	__be32		nfserr;
	int		count;

	dprintk("nfsd: READDIR(3)  %s %d bytes at %d\n",
				SVCFH_fmt(&argp->fh),
				argp->count, (u32) argp->cookie);

	/* Make sure we've room for the NULL ptr & eof flag, and shrink to
	 * client read size */
	count = (argp->count >> 2) - 2;

	/* Read directory and encode entries on the fly */
	fh_copy(&resp->fh, &argp->fh);

	resp->buflen = count;
	resp->common.err = nfs_ok;
	resp->buffer = argp->buffer;
	resp->rqstp = rqstp;
	nfserr = nfsd_readdir(rqstp, &resp->fh, (loff_t*) &argp->cookie, 
					&resp->common, nfs3svc_encode_entry);
	memcpy(resp->verf, argp->verf, 8);
	resp->count = resp->buffer - argp->buffer;
	if (resp->offset)
		xdr_encode_hyper(resp->offset, argp->cookie);

	RETURN_STATUS(nfserr);
}