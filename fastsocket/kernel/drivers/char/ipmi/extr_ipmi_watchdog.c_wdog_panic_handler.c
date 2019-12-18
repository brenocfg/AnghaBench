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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_OK ; 
 scalar_t__ WDOG_TIMEOUT_NONE ; 
 scalar_t__ ipmi_watchdog_state ; 
 int /*<<< orphan*/  panic_halt_ipmi_set_timeout () ; 
 scalar_t__ pretimeout ; 
 int timeout ; 
 scalar_t__ watchdog_user ; 

__attribute__((used)) static int wdog_panic_handler(struct notifier_block *this,
			      unsigned long         event,
			      void                  *unused)
{
	static int panic_event_handled;

	/* On a panic, if we have a panic timeout, make sure to extend
	   the watchdog timer to a reasonable value to complete the
	   panic, if the watchdog timer is running.  Plus the
	   pretimeout is meaningless at panic time. */
	if (watchdog_user && !panic_event_handled &&
	    ipmi_watchdog_state != WDOG_TIMEOUT_NONE) {
		/* Make sure we do this only once. */
		panic_event_handled = 1;

		timeout = 255;
		pretimeout = 0;
		panic_halt_ipmi_set_timeout();
	}

	return NOTIFY_OK;
}