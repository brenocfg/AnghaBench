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
struct target_ops {int dummy; } ;
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_target (struct target_ops*) ; 
 int /*<<< orphan*/  blocked_mask ; 
 int /*<<< orphan*/  debug_lin_lwp ; 
 int /*<<< orphan*/  init_lin_lwp_ops () ; 
 struct target_ops lin_lwp_ops ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  normal_mask ; 
 int /*<<< orphan*/  setdebuglist ; 
 int /*<<< orphan*/  showdebuglist ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigchld_handler ; 
 int /*<<< orphan*/  sigdelset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  suspend_mask ; 
 int /*<<< orphan*/  var_zinteger ; 

void
_initialize_lin_lwp (void)
{
  struct sigaction action;

  extern void thread_db_init (struct target_ops *);

  init_lin_lwp_ops ();
  add_target (&lin_lwp_ops);
  thread_db_init (&lin_lwp_ops);

  /* Save the original signal mask.  */
  sigprocmask (SIG_SETMASK, NULL, &normal_mask);

  action.sa_handler = sigchld_handler;
  sigemptyset (&action.sa_mask);
  action.sa_flags = 0;
  sigaction (SIGCHLD, &action, NULL);

  /* Make sure we don't block SIGCHLD during a sigsuspend.  */
  sigprocmask (SIG_SETMASK, NULL, &suspend_mask);
  sigdelset (&suspend_mask, SIGCHLD);

  sigemptyset (&blocked_mask);

  add_show_from_set (add_set_cmd ("lin-lwp", no_class, var_zinteger,
				  (char *) &debug_lin_lwp,
				  "Set debugging of GNU/Linux lwp module.\n\
Enables printf debugging output.\n", &setdebuglist), &showdebuglist);
}