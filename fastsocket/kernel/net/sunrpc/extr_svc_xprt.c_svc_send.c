#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xdr_buf {TYPE_2__* tail; int /*<<< orphan*/  page_len; TYPE_1__* head; int /*<<< orphan*/  len; } ;
struct svc_xprt {int /*<<< orphan*/  xpt_bc_pending; int /*<<< orphan*/  xpt_mutex; TYPE_3__* xpt_ops; int /*<<< orphan*/  xpt_flags; } ;
struct svc_rqst {struct xdr_buf rq_res; struct svc_xprt* rq_xprt; } ;
struct TYPE_6__ {int (* xpo_sendto ) (struct svc_rqst*) ;int /*<<< orphan*/  (* xpo_release_rqst ) (struct svc_rqst*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  iov_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  iov_len; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ECONNREFUSED ; 
 int EFAULT ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  XPT_CLOSE ; 
 int /*<<< orphan*/  XPT_DEAD ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct svc_rqst*) ; 
 int stub2 (struct svc_rqst*) ; 
 int /*<<< orphan*/  svc_xprt_release (struct svc_rqst*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int svc_send(struct svc_rqst *rqstp)
{
	struct svc_xprt	*xprt;
	int		len;
	struct xdr_buf	*xb;

	xprt = rqstp->rq_xprt;
	if (!xprt)
		return -EFAULT;

	/* release the receive skb before sending the reply */
	rqstp->rq_xprt->xpt_ops->xpo_release_rqst(rqstp);

	/* calculate over-all length */
	xb = &rqstp->rq_res;
	xb->len = xb->head[0].iov_len +
		xb->page_len +
		xb->tail[0].iov_len;

	/* Grab mutex to serialize outgoing data. */
	mutex_lock(&xprt->xpt_mutex);
	if (test_bit(XPT_DEAD, &xprt->xpt_flags)
			|| test_bit(XPT_CLOSE, &xprt->xpt_flags))
		len = -ENOTCONN;
	else
		len = xprt->xpt_ops->xpo_sendto(rqstp);
	mutex_unlock(&xprt->xpt_mutex);
	rpc_wake_up(&xprt->xpt_bc_pending);
	svc_xprt_release(rqstp);

	if (len == -ECONNREFUSED || len == -ENOTCONN || len == -EAGAIN)
		return 0;
	return len;
}