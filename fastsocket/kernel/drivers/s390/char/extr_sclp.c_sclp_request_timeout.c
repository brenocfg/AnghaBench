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
 int HZ ; 
 int SCLP_BUSY_INTERVAL ; 
 int /*<<< orphan*/  __sclp_queue_read_req () ; 
 int /*<<< orphan*/  __sclp_set_request_timer (int,void (*) (unsigned long),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sclp_lock ; 
 int /*<<< orphan*/  sclp_process_queue () ; 
 scalar_t__ sclp_running_state ; 
 scalar_t__ sclp_running_state_idle ; 
 scalar_t__ sclp_running_state_running ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
sclp_request_timeout(unsigned long data)
{
	unsigned long flags;

	spin_lock_irqsave(&sclp_lock, flags);
	if (data) {
		if (sclp_running_state == sclp_running_state_running) {
			/* Break running state and queue NOP read event request
			 * to get a defined interface state. */
			__sclp_queue_read_req();
			sclp_running_state = sclp_running_state_idle;
		}
	} else {
		__sclp_set_request_timer(SCLP_BUSY_INTERVAL * HZ,
					 sclp_request_timeout, 0);
	}
	spin_unlock_irqrestore(&sclp_lock, flags);
	sclp_process_queue();
}