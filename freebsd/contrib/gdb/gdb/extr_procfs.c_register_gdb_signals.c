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
typedef  int /*<<< orphan*/  procinfo ;
typedef  int /*<<< orphan*/  gdb_sigset_t ;

/* Variables and functions */
 int NSIG ; 
 int /*<<< orphan*/  praddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  prdelset (int /*<<< orphan*/ *,int) ; 
 int proc_set_traced_signals (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int signal_pass_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_print_state (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_stop_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_signal_from_host (int) ; 

__attribute__((used)) static int
register_gdb_signals (procinfo *pi, gdb_sigset_t *signals)
{
  int signo;

  for (signo = 0; signo < NSIG; signo ++)
    if (signal_stop_state  (target_signal_from_host (signo)) == 0 &&
	signal_print_state (target_signal_from_host (signo)) == 0 &&
	signal_pass_state  (target_signal_from_host (signo)) == 1)
      prdelset (signals, signo);
    else
      praddset (signals, signo);

  return proc_set_traced_signals (pi, signals);
}