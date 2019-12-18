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
struct sigcontext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGVTALRM_MASK ; 
 int /*<<< orphan*/  block_signals () ; 
 int /*<<< orphan*/  real_alarm_handler (struct sigcontext*) ; 
 int /*<<< orphan*/  set_signals (int) ; 
 int signals_enabled ; 
 int /*<<< orphan*/  signals_pending ; 

void alarm_handler(int sig, struct sigcontext *sc)
{
	int enabled;

	enabled = signals_enabled;
	if (!signals_enabled) {
		signals_pending |= SIGVTALRM_MASK;
		return;
	}

	block_signals();

	real_alarm_handler(sc);
	set_signals(enabled);
}