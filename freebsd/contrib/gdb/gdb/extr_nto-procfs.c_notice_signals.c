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
struct TYPE_2__ {int /*<<< orphan*/  trace; } ;

/* Variables and functions */
 int NSIG ; 
 TYPE_1__ run ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int) ; 
 int signal_pass_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_print_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_stop_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_signal_from_host (int) ; 

__attribute__((used)) static void
notice_signals (void)
{
  int signo;

  for (signo = 1; signo < NSIG; signo++)
    {
      if (signal_stop_state (target_signal_from_host (signo)) == 0
	  && signal_print_state (target_signal_from_host (signo)) == 0
	  && signal_pass_state (target_signal_from_host (signo)) == 1)
	sigdelset (&run.trace, signo);
      else
	sigaddset (&run.trace, signo);
    }
}