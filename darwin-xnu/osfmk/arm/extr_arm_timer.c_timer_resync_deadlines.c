#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spl_t ;
struct TYPE_4__ {scalar_t__ deadline; int /*<<< orphan*/  has_expired; } ;
typedef  TYPE_1__ rtclock_timer_t ;
struct TYPE_5__ {scalar_t__ idle_timer_deadline; scalar_t__ quantum_timer_deadline; scalar_t__ rtcPop; TYPE_1__ rtclock_timer; } ;
typedef  TYPE_2__ cpu_data_t ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  DBG_MACH_EXCP_DECI ; 
 scalar_t__ EndOfAllTime ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* getCpuDatap () ; 
 int setPop (scalar_t__) ; 
 int /*<<< orphan*/  splclock () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 

void
timer_resync_deadlines(void)
{
	uint64_t        deadline;
	rtclock_timer_t *mytimer;
	spl_t           s = splclock();	/* No interruptions please */
	cpu_data_t     *cpu_data_ptr;

	cpu_data_ptr = getCpuDatap();

	deadline = 0;

	/* if we have a clock timer set sooner, pop on that */
	mytimer = &cpu_data_ptr->rtclock_timer;	/* Point to the timer itself */
	if ((!mytimer->has_expired) && (mytimer->deadline > 0))
		deadline = mytimer->deadline;

	/* if we have a idle timer event coming up, how about that? */
	if ((cpu_data_ptr->idle_timer_deadline > 0)
	     && (cpu_data_ptr->idle_timer_deadline < deadline))
		deadline = cpu_data_ptr->idle_timer_deadline;

	/* If we have the quantum timer setup, check that */
	if ((cpu_data_ptr->quantum_timer_deadline > 0)
	    && (cpu_data_ptr->quantum_timer_deadline < deadline))
		deadline = cpu_data_ptr->quantum_timer_deadline;

	if ((deadline == EndOfAllTime)
	    || ((deadline > 0) && (cpu_data_ptr->rtcPop != deadline))) {
		int             decr;

		decr = setPop(deadline);

		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, 
		    MACHDBG_CODE(DBG_MACH_EXCP_DECI, 1) | DBG_FUNC_NONE, 
		    decr, 2, 0, 0, 0);
	}
	splx(s);
}