#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int page_len; TYPE_3__* tail; TYPE_1__* head; } ;
struct svc_rqst {TYPE_4__ rq_res; } ;
struct TYPE_6__ {scalar_t__ err; } ;
struct nfsd3_readdirres {scalar_t__ status; int count; TYPE_2__ common; int /*<<< orphan*/  verf; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_7__ {int iov_len; int /*<<< orphan*/ * iov_base; } ;
struct TYPE_5__ {scalar_t__ iov_len; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/ * encode_post_op_attr (struct svc_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ htonl (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nfserr_eof ; 
 int xdr_ressize_check (struct svc_rqst*,int /*<<< orphan*/ *) ; 

int
nfs3svc_encode_readdirres(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_readdirres *resp)
{
	p = encode_post_op_attr(rqstp, p, &resp->fh);

	if (resp->status == 0) {
		/* stupid readdir cookie */
		memcpy(p, resp->verf, 8); p += 2;
		xdr_ressize_check(rqstp, p);
		if (rqstp->rq_res.head[0].iov_len + (2<<2) > PAGE_SIZE)
			return 1; /*No room for trailer */
		rqstp->rq_res.page_len = (resp->count) << 2;

		/* add the 'tail' to the end of the 'head' page - page 0. */
		rqstp->rq_res.tail[0].iov_base = p;
		*p++ = 0;		/* no more entries */
		*p++ = htonl(resp->common.err == nfserr_eof);
		rqstp->rq_res.tail[0].iov_len = 2<<2;
		return 1;
	} else
		return xdr_ressize_check(rqstp, p);
}