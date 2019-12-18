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
struct svc_rqst {int dummy; } ;
struct nfsd3_commitres {scalar_t__ status; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/ * encode_wcc_data (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 TYPE_1__ nfssvc_boot ; 
 int xdr_ressize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 

int
nfs3svc_encode_commitres(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_commitres *resp)
{
	p = encode_wcc_data(rqstp, p, &resp->fh);
	/* Write verifier */
	if (resp->status == 0) {
		*p++ = htonl(nfssvc_boot.tv_sec);
		*p++ = htonl(nfssvc_boot.tv_usec);
	}
	return xdr_ressize_check(rqstp, p);
}