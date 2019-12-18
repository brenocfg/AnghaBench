#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  spl_t ;
struct TYPE_6__ {scalar_t__ count; } ;
struct TYPE_7__ {scalar_t__ deadline; TYPE_1__ queue; int /*<<< orphan*/  has_expired; } ;
typedef  TYPE_2__ rtclock_timer_t ;
struct TYPE_8__ {scalar_t__ quantum_timer_deadline; TYPE_2__ rtclock_timer; int /*<<< orphan*/  cpu_running; } ;
typedef  TYPE_3__ cpu_data_t ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int DECR_SET_DEADLINE ; 
 scalar_t__ EndOfAllTime ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,scalar_t__,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* current_cpu_datap () ; 
 scalar_t__ pmCPUGetDeadline (TYPE_3__*) ; 
 scalar_t__ setPop (scalar_t__) ; 
 int /*<<< orphan*/  splclock () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 

void
timer_resync_deadlines(void)
{
	uint64_t		deadline = EndOfAllTime;
	uint64_t		pmdeadline;
	uint64_t		quantum_deadline;
	rtclock_timer_t		*mytimer;
	spl_t			s = splclock();
	cpu_data_t		*pp;
	uint32_t		decr;

	pp = current_cpu_datap();
	if (!pp->cpu_running)
		/* There's really nothing to do if this processor is down */
		return;

	/*
	 * If we have a clock timer set, pick that.
	 */
	mytimer = &pp->rtclock_timer;
	if (!mytimer->has_expired &&
	    0 < mytimer->deadline && mytimer->deadline < EndOfAllTime)
		deadline = mytimer->deadline;

	/*
	 * If we have a power management deadline, see if that's earlier.
	 */
	pmdeadline = pmCPUGetDeadline(pp);
	if (0 < pmdeadline && pmdeadline < deadline)
		deadline = pmdeadline;

	/* If we have the quantum timer setup, check that */
	quantum_deadline = pp->quantum_timer_deadline;
	if ((quantum_deadline > 0) && 
	    (quantum_deadline < deadline))
		deadline = quantum_deadline;


	/*
	 * Go and set the "pop" event.
	 */
	decr = (uint32_t) setPop(deadline);

	/* Record non-PM deadline for latency tool */
	if (decr != 0 && deadline != pmdeadline) {
		uint64_t queue_count = 0;
		if (deadline != quantum_deadline) {
			/* 
			 * For non-quantum timer put the queue count
			 * in the tracepoint.
			 */
			queue_count = mytimer->queue.count;
		}
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
		    DECR_SET_DEADLINE | DBG_FUNC_NONE,
		    decr, 2,
		    deadline,
		    queue_count, 0);
	}
	splx(s);
}