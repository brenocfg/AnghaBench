#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int page_len; TYPE_1__* tail; } ;
struct svc_rqst {TYPE_2__ rq_res; } ;
struct nfsd3_readres {scalar_t__ status; int count; int eof; int /*<<< orphan*/  fh; } ;
typedef  scalar_t__ __be32 ;
struct TYPE_3__ {int iov_len; scalar_t__* iov_base; } ;

/* Variables and functions */
 scalar_t__* encode_post_op_attr (struct svc_rqst*,scalar_t__*,int /*<<< orphan*/ *) ; 
 void* htonl (int) ; 
 int xdr_ressize_check (struct svc_rqst*,scalar_t__*) ; 

int
nfs3svc_encode_readres(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_readres *resp)
{
	p = encode_post_op_attr(rqstp, p, &resp->fh);
	if (resp->status == 0) {
		*p++ = htonl(resp->count);
		*p++ = htonl(resp->eof);
		*p++ = htonl(resp->count);	/* xdr opaque count */
		xdr_ressize_check(rqstp, p);
		/* now update rqstp->rq_res to reflect data aswell */
		rqstp->rq_res.page_len = resp->count;
		if (resp->count & 3) {
			/* need to pad the tail */
			rqstp->rq_res.tail[0].iov_base = p;
			*p = 0;
			rqstp->rq_res.tail[0].iov_len = 4 - (resp->count & 3);
		}
		return 1;
	} else
		return xdr_ressize_check(rqstp, p);
}