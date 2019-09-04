#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ deadline; int /*<<< orphan*/  deadline_set; int /*<<< orphan*/  timer; } ;
struct TYPE_6__ {TYPE_1__ threshold; } ;
typedef  TYPE_2__ timer_longterm_t ;
typedef  int /*<<< orphan*/  spl_t ;

/* Variables and functions */
 int TIMER_CALL_LOCAL ; 
 int TIMER_CALL_SYS_CRITICAL ; 
 scalar_t__ TIMER_LONGTERM_NONE ; 
 scalar_t__ cpu_number () ; 
 scalar_t__ master_cpu ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  splclock () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_call_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timer_longterm_queue ; 
 int /*<<< orphan*/  timer_longterm_update_locked (TYPE_2__*) ; 
 int /*<<< orphan*/  timer_queue_lock_spin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_queue_unlock (int /*<<< orphan*/ ) ; 

void
timer_longterm_update(timer_longterm_t *tlp)
{
	spl_t	s = splclock();

	timer_queue_lock_spin(timer_longterm_queue);

	if (cpu_number() != master_cpu)
		panic("timer_longterm_update_master() on non-boot cpu");

	timer_longterm_update_locked(tlp);

	if (tlp->threshold.deadline != TIMER_LONGTERM_NONE)
		timer_call_enter(
			&tlp->threshold.timer,
			tlp->threshold.deadline_set,
			TIMER_CALL_LOCAL | TIMER_CALL_SYS_CRITICAL);
	
	timer_queue_unlock(timer_longterm_queue);
	splx(s);
}