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
struct nfsd3_readlinkres {int /*<<< orphan*/  len; int /*<<< orphan*/  fh; } ;
struct nfsd3_readlinkargs {int /*<<< orphan*/  buffer; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS3_MAXPATHLEN ; 
 int /*<<< orphan*/  RETURN_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_readlink (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __be32
nfsd3_proc_readlink(struct svc_rqst *rqstp, struct nfsd3_readlinkargs *argp,
					   struct nfsd3_readlinkres *resp)
{
	__be32 nfserr;

	dprintk("nfsd: READLINK(3) %s\n", SVCFH_fmt(&argp->fh));

	/* Read the symlink. */
	fh_copy(&resp->fh, &argp->fh);
	resp->len = NFS3_MAXPATHLEN;
	nfserr = nfsd_readlink(rqstp, &resp->fh, argp->buffer, &resp->len);
	RETURN_STATUS(nfserr);
}