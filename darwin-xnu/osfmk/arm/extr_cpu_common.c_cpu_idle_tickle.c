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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  (* idle_timer_t ) (int /*<<< orphan*/ ,int*) ;
struct TYPE_3__ {void* idle_timer_notify; int idle_timer_deadline; int /*<<< orphan*/  idle_timer_refcon; } ;
typedef  TYPE_1__ cpu_data_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  clock_absolutetime_interval_to_deadline (int,int*) ; 
 TYPE_1__* getCpuDatap () ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  timer_resync_deadlines () ; 

void
cpu_idle_tickle(void)
{
	boolean_t	intr;
	cpu_data_t	*cpu_data_ptr;
	uint64_t	new_idle_timeout_ticks = 0x0ULL;

	intr = ml_set_interrupts_enabled(FALSE);
	cpu_data_ptr = getCpuDatap();

	if (cpu_data_ptr->idle_timer_notify != (void *)NULL) {
		((idle_timer_t)cpu_data_ptr->idle_timer_notify)(cpu_data_ptr->idle_timer_refcon, &new_idle_timeout_ticks);
		if (new_idle_timeout_ticks != 0x0ULL) {
			/* if a new idle timeout was requested set the new idle timer deadline */
			clock_absolutetime_interval_to_deadline(new_idle_timeout_ticks, &cpu_data_ptr->idle_timer_deadline);
		} else {
			/* turn off the idle timer */
			cpu_data_ptr->idle_timer_deadline = 0x0ULL;
		}
		timer_resync_deadlines();
	}
	(void) ml_set_interrupts_enabled(intr);
}