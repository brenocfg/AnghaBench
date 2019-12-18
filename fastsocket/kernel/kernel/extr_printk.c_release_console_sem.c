#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  call_console_drivers (unsigned int,unsigned int) ; 
 unsigned int con_start ; 
 scalar_t__ console_locked ; 
 scalar_t__ console_may_schedule ; 
 int /*<<< orphan*/  console_sem ; 
 scalar_t__ console_suspended ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 unsigned int log_end ; 
 unsigned int log_start ; 
 int /*<<< orphan*/  logbuf_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_critical_timings () ; 
 int /*<<< orphan*/  stop_critical_timings () ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_klogd () ; 

void release_console_sem(void)
{
	unsigned long flags;
	unsigned _con_start, _log_end;
	unsigned wake_klogd = 0;

	if (console_suspended) {
		up(&console_sem);
		return;
	}

	console_may_schedule = 0;

	for ( ; ; ) {
		spin_lock_irqsave(&logbuf_lock, flags);
		wake_klogd |= log_start - log_end;
		if (con_start == log_end)
			break;			/* Nothing to print */
		_con_start = con_start;
		_log_end = log_end;
		con_start = log_end;		/* Flush */
		spin_unlock(&logbuf_lock);
		stop_critical_timings();	/* don't trace print latency */
		call_console_drivers(_con_start, _log_end);
		start_critical_timings();
		local_irq_restore(flags);
	}
	console_locked = 0;
	up(&console_sem);
	spin_unlock_irqrestore(&logbuf_lock, flags);
	if (wake_klogd)
		wake_up_klogd();
}