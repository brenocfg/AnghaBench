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
typedef  scalar_t__ clock_usec_t ;
typedef  scalar_t__ clock_sec_t ;
struct TYPE_4__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_3__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  clock_get_boottime_microtime (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  clock_get_calendar_microtime (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  clock_lock ; 
 TYPE_2__ gIOLastSleepTime ; 
 TYPE_1__ gIOLastWakeTime ; 
 scalar_t__ is_clock_configured ; 
 scalar_t__ kdp_clock_is_locked () ; 
 int /*<<< orphan*/  paniclog_append_noflush (char*,...) ; 
 scalar_t__ simple_lock_try (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 

void
panic_display_times()
{
	if (kdp_clock_is_locked()) {
		paniclog_append_noflush("Warning: clock is locked.  Can't get time\n");
		return;
	}

	if ((is_clock_configured) && (simple_lock_try(&clock_lock))) {
		clock_sec_t	secs, boot_secs;
		clock_usec_t	usecs, boot_usecs;

		simple_unlock(&clock_lock);

		clock_get_calendar_microtime(&secs, &usecs);
		clock_get_boottime_microtime(&boot_secs, &boot_usecs);

		paniclog_append_noflush("Epoch Time:        sec       usec\n");
		paniclog_append_noflush("  Boot    : 0x%08x 0x%08x\n", (unsigned int)boot_secs, (unsigned int)boot_usecs);
		paniclog_append_noflush("  Sleep   : 0x%08x 0x%08x\n", (unsigned int)gIOLastSleepTime.tv_sec, (unsigned int)gIOLastSleepTime.tv_usec);
		paniclog_append_noflush("  Wake    : 0x%08x 0x%08x\n", (unsigned int)gIOLastWakeTime.tv_sec, (unsigned int)gIOLastWakeTime.tv_usec);
		paniclog_append_noflush("  Calendar: 0x%08x 0x%08x\n\n", (unsigned int)secs, (unsigned int)usecs);
	}
}