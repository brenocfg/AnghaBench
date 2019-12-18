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
struct nfsd_diropres {int /*<<< orphan*/  fh; } ;
struct nfsd_diropargs {int /*<<< orphan*/  fh; int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_FHSIZE ; 
 int /*<<< orphan*/  SVCFH_fmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_lookup (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_return_dirop (int /*<<< orphan*/ ,struct nfsd_diropres*) ; 

__attribute__((used)) static __be32
nfsd_proc_lookup(struct svc_rqst *rqstp, struct nfsd_diropargs *argp,
					 struct nfsd_diropres  *resp)
{
	__be32	nfserr;

	dprintk("nfsd: LOOKUP   %s %.*s\n",
		SVCFH_fmt(&argp->fh), argp->len, argp->name);

	fh_init(&resp->fh, NFS_FHSIZE);
	nfserr = nfsd_lookup(rqstp, &argp->fh, argp->name, argp->len,
				 &resp->fh);

	fh_put(&argp->fh);
	return nfsd_return_dirop(nfserr, resp);
}