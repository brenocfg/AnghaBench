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
typedef  scalar_t__ u_int32_t ;
struct TYPE_2__ {scalar_t__ intimer_nodelay; scalar_t__ intimer_fast; scalar_t__ intimer_lazy; } ;
struct inpcbinfo {TYPE_1__ ipi_gc_req; } ;

/* Variables and functions */
 scalar_t__ INPCB_GCREQ_THRESHOLD ; 
#define  INPCB_TIMER_FAST 129 
#define  INPCB_TIMER_NODELAY 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  atomic_add_32 (scalar_t__*,int) ; 
 int /*<<< orphan*/  inpcb_garbage_collecting ; 
 int /*<<< orphan*/  inpcb_sched_lazy_timeout () ; 
 int /*<<< orphan*/  inpcb_sched_timeout () ; 
 int /*<<< orphan*/  inpcb_timeout_lock ; 
 int /*<<< orphan*/  lck_mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

void
inpcb_gc_sched(struct inpcbinfo *ipi, u_int32_t type)
{
	u_int32_t gccnt;

	lck_mtx_lock_spin(&inpcb_timeout_lock);
	inpcb_garbage_collecting = TRUE;
	gccnt = ipi->ipi_gc_req.intimer_nodelay +
		ipi->ipi_gc_req.intimer_fast;

	if (gccnt > INPCB_GCREQ_THRESHOLD) {
		type = INPCB_TIMER_FAST;
	}

	switch (type) {
	case INPCB_TIMER_NODELAY:
		atomic_add_32(&ipi->ipi_gc_req.intimer_nodelay, 1);
		inpcb_sched_timeout();
		break;
	case INPCB_TIMER_FAST:
		atomic_add_32(&ipi->ipi_gc_req.intimer_fast, 1);
		inpcb_sched_timeout();
		break;
	default:
		atomic_add_32(&ipi->ipi_gc_req.intimer_lazy, 1);
		inpcb_sched_lazy_timeout();
		break;
	}
	lck_mtx_unlock(&inpcb_timeout_lock);
}