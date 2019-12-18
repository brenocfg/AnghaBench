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
struct svc_fh {int /*<<< orphan*/  fh_dentry; int /*<<< orphan*/  fh_export; } ;
struct nfsd4_getattr {int /*<<< orphan*/  ga_bmval; struct svc_fh* ga_fhp; } ;
struct nfsd4_compoundres {int end; int p; int /*<<< orphan*/  rqstp; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int COMPOUND_ERR_SLACK_SPACE ; 
 int /*<<< orphan*/  nfsd4_encode_fattr (struct svc_fh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __be32
nfsd4_encode_getattr(struct nfsd4_compoundres *resp, __be32 nfserr, struct nfsd4_getattr *getattr)
{
	struct svc_fh *fhp = getattr->ga_fhp;
	int buflen;

	if (nfserr)
		return nfserr;

	buflen = resp->end - resp->p - (COMPOUND_ERR_SLACK_SPACE >> 2);
	nfserr = nfsd4_encode_fattr(fhp, fhp->fh_export, fhp->fh_dentry,
				    resp->p, &buflen, getattr->ga_bmval,
				    resp->rqstp, 0);
	if (!nfserr)
		resp->p += buflen;
	return nfserr;
}