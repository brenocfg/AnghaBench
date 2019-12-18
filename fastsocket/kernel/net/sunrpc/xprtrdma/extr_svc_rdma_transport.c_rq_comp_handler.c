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
struct TYPE_3__ {int /*<<< orphan*/  refcount; } ;
struct TYPE_4__ {TYPE_1__ xpt_ref; } ;
struct svcxprt_rdma {int /*<<< orphan*/  sc_dto_q; TYPE_2__ sc_xprt; int /*<<< orphan*/  sc_flags; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMAXPRT_RQ_PENDING ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dto_lock ; 
 int /*<<< orphan*/  dto_tasklet ; 
 int /*<<< orphan*/  dto_xprt_q ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  svc_xprt_get (TYPE_2__*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rq_comp_handler(struct ib_cq *cq, void *cq_context)
{
	struct svcxprt_rdma *xprt = cq_context;
	unsigned long flags;

	/* Guard against unconditional flush call for destroyed QP */
	if (atomic_read(&xprt->sc_xprt.xpt_ref.refcount)==0)
		return;

	/*
	 * Set the bit regardless of whether or not it's on the list
	 * because it may be on the list already due to an SQ
	 * completion.
	 */
	set_bit(RDMAXPRT_RQ_PENDING, &xprt->sc_flags);

	/*
	 * If this transport is not already on the DTO transport queue,
	 * add it
	 */
	spin_lock_irqsave(&dto_lock, flags);
	if (list_empty(&xprt->sc_dto_q)) {
		svc_xprt_get(&xprt->sc_xprt);
		list_add_tail(&xprt->sc_dto_q, &dto_xprt_q);
	}
	spin_unlock_irqrestore(&dto_lock, flags);

	/* Tasklet does all the work to avoid irqsave locks. */
	tasklet_schedule(&dto_tasklet);
}