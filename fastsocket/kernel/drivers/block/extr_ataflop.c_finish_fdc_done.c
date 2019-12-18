#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  expires; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 scalar_t__ NeedSeek ; 
 TYPE_1__ fd_timer ; 
 scalar_t__ fdc_busy ; 
 int /*<<< orphan*/  fdc_wait ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  start_check_change_timer () ; 
 int /*<<< orphan*/  start_motor_off_timer () ; 
 int /*<<< orphan*/  stdma_release () ; 
 int /*<<< orphan*/  stop_timeout () ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ timer_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void finish_fdc_done( int dummy )
{
	unsigned long flags;

	DPRINT(("finish_fdc_done entered\n"));
	stop_timeout();
	NeedSeek = 0;

	if (timer_pending(&fd_timer) && time_before(fd_timer.expires, jiffies + 5))
		/* If the check for a disk change is done too early after this
		 * last seek command, the WP bit still reads wrong :-((
		 */
		mod_timer(&fd_timer, jiffies + 5);
	else
		start_check_change_timer();
	start_motor_off_timer();

	local_irq_save(flags);
	stdma_release();
	fdc_busy = 0;
	wake_up( &fdc_wait );
	local_irq_restore(flags);

	DPRINT(("finish_fdc() finished\n"));
}