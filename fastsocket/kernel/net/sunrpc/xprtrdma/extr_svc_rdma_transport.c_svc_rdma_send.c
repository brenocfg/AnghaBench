#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  xpt_flags; } ;
struct svcxprt_rdma {scalar_t__ sc_sq_depth; int /*<<< orphan*/  sc_send_wait; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_sq_count; TYPE_1__ sc_xprt; int /*<<< orphan*/  sc_qp; } ;
struct ib_send_wr {scalar_t__ send_flags; struct ib_send_wr* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOTCONN ; 
 scalar_t__ IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  XPT_CLOSE ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int,scalar_t__,scalar_t__) ; 
 int ib_post_send (int /*<<< orphan*/ ,struct ib_send_wr*,struct ib_send_wr**) ; 
 int /*<<< orphan*/  rdma_stat_sq_starve ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sq_cq_reap (struct svcxprt_rdma*) ; 
 int /*<<< orphan*/  svc_xprt_get (TYPE_1__*) ; 
 int /*<<< orphan*/  svc_xprt_put (TYPE_1__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int svc_rdma_send(struct svcxprt_rdma *xprt, struct ib_send_wr *wr)
{
	struct ib_send_wr *bad_wr, *n_wr;
	int wr_count;
	int i;
	int ret;

	if (test_bit(XPT_CLOSE, &xprt->sc_xprt.xpt_flags))
		return -ENOTCONN;

	BUG_ON(wr->send_flags != IB_SEND_SIGNALED);
	wr_count = 1;
	for (n_wr = wr->next; n_wr; n_wr = n_wr->next)
		wr_count++;

	/* If the SQ is full, wait until an SQ entry is available */
	while (1) {
		spin_lock_bh(&xprt->sc_lock);
		if (xprt->sc_sq_depth < atomic_read(&xprt->sc_sq_count) + wr_count) {
			spin_unlock_bh(&xprt->sc_lock);
			atomic_inc(&rdma_stat_sq_starve);

			/* See if we can opportunistically reap SQ WR to make room */
			sq_cq_reap(xprt);

			/* Wait until SQ WR available if SQ still full */
			wait_event(xprt->sc_send_wait,
				   atomic_read(&xprt->sc_sq_count) <
				   xprt->sc_sq_depth);
			if (test_bit(XPT_CLOSE, &xprt->sc_xprt.xpt_flags))
				return -ENOTCONN;
			continue;
		}
		/* Take a transport ref for each WR posted */
		for (i = 0; i < wr_count; i++)
			svc_xprt_get(&xprt->sc_xprt);

		/* Bump used SQ WR count and post */
		atomic_add(wr_count, &xprt->sc_sq_count);
		ret = ib_post_send(xprt->sc_qp, wr, &bad_wr);
		if (ret) {
			set_bit(XPT_CLOSE, &xprt->sc_xprt.xpt_flags);
			atomic_sub(wr_count, &xprt->sc_sq_count);
			for (i = 0; i < wr_count; i ++)
				svc_xprt_put(&xprt->sc_xprt);
			dprintk("svcrdma: failed to post SQ WR rc=%d, "
			       "sc_sq_count=%d, sc_sq_depth=%d\n",
			       ret, atomic_read(&xprt->sc_sq_count),
			       xprt->sc_sq_depth);
		}
		spin_unlock_bh(&xprt->sc_lock);
		if (ret)
			wake_up(&xprt->sc_send_wait);
		break;
	}
	return ret;
}