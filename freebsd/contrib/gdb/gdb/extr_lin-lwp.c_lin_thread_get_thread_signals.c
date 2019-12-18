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
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  blocked_mask ; 
 int get_signo (char*) ; 
 int /*<<< orphan*/  sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigchld_handler ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  suspend_mask ; 

void
lin_thread_get_thread_signals (sigset_t *set)
{
  struct sigaction action;
  int restart, cancel;

  sigemptyset (set);

  restart = get_signo ("__pthread_sig_restart");
  if (restart == 0)
    return;

  cancel = get_signo ("__pthread_sig_cancel");
  if (cancel == 0)
    return;

  sigaddset (set, restart);
  sigaddset (set, cancel);

  /* The GNU/Linux Threads library makes terminating threads send a
     special "cancel" signal instead of SIGCHLD.  Make sure we catch
     those (to prevent them from terminating GDB itself, which is
     likely to be their default action) and treat them the same way as
     SIGCHLD.  */

  action.sa_handler = sigchld_handler;
  sigemptyset (&action.sa_mask);
  action.sa_flags = 0;
  sigaction (cancel, &action, NULL);

  /* We block the "cancel" signal throughout this code ...  */
  sigaddset (&blocked_mask, cancel);
  sigprocmask (SIG_BLOCK, &blocked_mask, NULL);

  /* ... except during a sigsuspend.  */
  sigdelset (&suspend_mask, cancel);
}