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
 int SIGIO ; 
 int /*<<< orphan*/  SIGIO_MASK ; 
 int /*<<< orphan*/  block_signals () ; 
 int /*<<< orphan*/  set_signals (int) ; 
 int /*<<< orphan*/  sig_handler_common (int,struct sigcontext*) ; 
 int signals_enabled ; 
 int /*<<< orphan*/  signals_pending ; 

void sig_handler(int sig, struct sigcontext *sc)
{
	int enabled;

	enabled = signals_enabled;
	if (!enabled && (sig == SIGIO)) {
		signals_pending |= SIGIO_MASK;
		return;
	}

	block_signals();

	sig_handler_common(sig, sc);

	set_signals(enabled);
}