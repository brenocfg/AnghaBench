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
struct TYPE_8__ {int page_len; TYPE_3__* head; int /*<<< orphan*/  len; TYPE_2__* tail; int /*<<< orphan*/  buflen; int /*<<< orphan*/ * pages; int /*<<< orphan*/  page_base; } ;
struct svc_rqst {TYPE_4__ rq_arg; int /*<<< orphan*/  rq_xprt; int /*<<< orphan*/  rq_prot; scalar_t__ rq_resused; int /*<<< orphan*/ * rq_respages; int /*<<< orphan*/ * rq_pages; } ;
struct TYPE_5__ {int page_len; int /*<<< orphan*/  buflen; int /*<<< orphan*/  len; TYPE_2__* tail; TYPE_3__* head; int /*<<< orphan*/  page_base; } ;
struct svc_rdma_op_ctxt {int count; size_t hdr_count; TYPE_1__ arg; int /*<<< orphan*/ * pages; } ;
struct TYPE_7__ {int iov_len; int /*<<< orphan*/  iov_base; } ;
struct TYPE_6__ {int iov_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IPPROTO_MAX ; 
 int /*<<< orphan*/  dprintk (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_rdma_put_context (struct svc_rdma_op_ctxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_xprt_copy_addrs (struct svc_rqst*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rdma_read_complete(struct svc_rqst *rqstp,
			      struct svc_rdma_op_ctxt *head)
{
	int page_no;
	int ret;

	BUG_ON(!head);

	/* Copy RPC pages */
	for (page_no = 0; page_no < head->count; page_no++) {
		put_page(rqstp->rq_pages[page_no]);
		rqstp->rq_pages[page_no] = head->pages[page_no];
	}
	/* Point rq_arg.pages past header */
	rqstp->rq_arg.pages = &rqstp->rq_pages[head->hdr_count];
	rqstp->rq_arg.page_len = head->arg.page_len;
	rqstp->rq_arg.page_base = head->arg.page_base;

	/* rq_respages starts after the last arg page */
	rqstp->rq_respages = &rqstp->rq_arg.pages[page_no];
	rqstp->rq_resused = 0;

	/* Rebuild rq_arg head and tail. */
	rqstp->rq_arg.head[0] = head->arg.head[0];
	rqstp->rq_arg.tail[0] = head->arg.tail[0];
	rqstp->rq_arg.len = head->arg.len;
	rqstp->rq_arg.buflen = head->arg.buflen;

	/* Free the context */
	svc_rdma_put_context(head, 0);

	/* XXX: What should this be? */
	rqstp->rq_prot = IPPROTO_MAX;
	svc_xprt_copy_addrs(rqstp, rqstp->rq_xprt);

	ret = rqstp->rq_arg.head[0].iov_len
		+ rqstp->rq_arg.page_len
		+ rqstp->rq_arg.tail[0].iov_len;
	dprintk("svcrdma: deferred read ret=%d, rq_arg.len =%d, "
		"rq_arg.head[0].iov_base=%p, rq_arg.head[0].iov_len = %zd\n",
		ret, rqstp->rq_arg.len,	rqstp->rq_arg.head[0].iov_base,
		rqstp->rq_arg.head[0].iov_len);

	return ret;
}