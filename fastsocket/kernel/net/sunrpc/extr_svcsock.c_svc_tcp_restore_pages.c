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
struct svc_sock {int sk_tcplen; int /*<<< orphan*/ ** sk_pages; } ;
struct TYPE_4__ {TYPE_1__* head; } ;
struct svc_rqst {int /*<<< orphan*/ ** rq_pages; TYPE_2__ rq_arg; } ;
typedef  int /*<<< orphan*/  rpc_fraghdr ;
struct TYPE_3__ {int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 unsigned int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int svc_tcp_restore_pages(struct svc_sock *svsk, struct svc_rqst *rqstp)
{
	unsigned int i, len, npages;

	if (svsk->sk_tcplen <= sizeof(rpc_fraghdr))
		return 0;
	len = svsk->sk_tcplen - sizeof(rpc_fraghdr);
	npages = (len + PAGE_SIZE - 1) >> PAGE_SHIFT;
	for (i = 0; i < npages; i++) {
		if (rqstp->rq_pages[i] != NULL)
			put_page(rqstp->rq_pages[i]);
		BUG_ON(svsk->sk_pages[i] == NULL);
		rqstp->rq_pages[i] = svsk->sk_pages[i];
		svsk->sk_pages[i] = NULL;
	}
	rqstp->rq_arg.head[0].iov_base = page_address(rqstp->rq_pages[0]);
	return len;
}