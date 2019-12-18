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
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_PROFILING ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  do_timer (int) ; 
 int /*<<< orphan*/  get_irq_regs () ; 
 int /*<<< orphan*/  profile_tick (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_process_times (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xtime_lock ; 

void h8300_timer_tick(void)
{
	if (current->pid)
		profile_tick(CPU_PROFILING);
	write_seqlock(&xtime_lock);
	do_timer(1);
	write_sequnlock(&xtime_lock);
	update_process_times(user_mode(get_irq_regs()));
}