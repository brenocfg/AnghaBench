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
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  SIGWINCH ; 
 int /*<<< orphan*/  SIGWINCH_HANDLER ; 
 int /*<<< orphan*/  SIG_DFL ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  async_disconnect ; 
 int /*<<< orphan*/  async_do_nothing ; 
 int /*<<< orphan*/  async_float_handler ; 
 int /*<<< orphan*/  async_request_quit ; 
 int /*<<< orphan*/  async_stop_sig ; 
 void* create_async_signal_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_sigfpe ; 
 int /*<<< orphan*/  handle_sighup ; 
 int /*<<< orphan*/  handle_sigint ; 
 int /*<<< orphan*/  handle_sigquit ; 
 int /*<<< orphan*/  handle_sigwinch ; 
 void* sigfpe_token ; 
 void* sighup_token ; 
 void* sigint_token ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* sigquit_token ; 
 void* sigtstp_token ; 
 void* sigwinch_token ; 

void
async_init_signals (void)
{
  signal (SIGINT, handle_sigint);
  sigint_token =
    create_async_signal_handler (async_request_quit, NULL);

  /* If SIGTRAP was set to SIG_IGN, then the SIG_IGN will get passed
     to the inferior and breakpoints will be ignored.  */
#ifdef SIGTRAP
  signal (SIGTRAP, SIG_DFL);
#endif

  /* If we initialize SIGQUIT to SIG_IGN, then the SIG_IGN will get
     passed to the inferior, which we don't want.  It would be
     possible to do a "signal (SIGQUIT, SIG_DFL)" after we fork, but
     on BSD4.3 systems using vfork, that can affect the
     GDB process as well as the inferior (the signal handling tables
     might be in memory, shared between the two).  Since we establish
     a handler for SIGQUIT, when we call exec it will set the signal
     to SIG_DFL for us.  */
  signal (SIGQUIT, handle_sigquit);
  sigquit_token =
    create_async_signal_handler (async_do_nothing, NULL);
#ifdef SIGHUP
  if (signal (SIGHUP, handle_sighup) != SIG_IGN)
    sighup_token =
      create_async_signal_handler (async_disconnect, NULL);
  else
    sighup_token =
      create_async_signal_handler (async_do_nothing, NULL);
#endif
  signal (SIGFPE, handle_sigfpe);
  sigfpe_token =
    create_async_signal_handler (async_float_handler, NULL);

#if defined(SIGWINCH) && defined(SIGWINCH_HANDLER)
  signal (SIGWINCH, handle_sigwinch);
  sigwinch_token =
    create_async_signal_handler (SIGWINCH_HANDLER, NULL);
#endif
#ifdef STOP_SIGNAL
  sigtstp_token =
    create_async_signal_handler (async_stop_sig, NULL);
#endif

}