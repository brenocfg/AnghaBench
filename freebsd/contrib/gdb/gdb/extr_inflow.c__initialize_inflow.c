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
 int /*<<< orphan*/  _SC_JOB_CONTROL ; 
 int /*<<< orphan*/  add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  class_run ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int job_control ; 
 int /*<<< orphan*/  kill_command ; 
 int /*<<< orphan*/  null_ptid ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  term_info ; 
 int terminal_is_ours ; 

void
_initialize_inflow (void)
{
  add_info ("terminal", term_info,
	    "Print inferior's saved terminal status.");

  add_com ("kill", class_run, kill_command,
	   "Kill execution of program being debugged.");

  inferior_ptid = null_ptid;

  terminal_is_ours = 1;

  /* OK, figure out whether we have job control.  If neither termios nor
     sgtty (i.e. termio or go32), leave job_control 0.  */

#if defined (HAVE_TERMIOS)
  /* Do all systems with termios have the POSIX way of identifying job
     control?  I hope so.  */
#ifdef _POSIX_JOB_CONTROL
  job_control = 1;
#else
#ifdef _SC_JOB_CONTROL
  job_control = sysconf (_SC_JOB_CONTROL);
#else
  job_control = 0;		/* have to assume the worst */
#endif /* _SC_JOB_CONTROL */
#endif /* _POSIX_JOB_CONTROL */
#endif /* HAVE_TERMIOS */

#ifdef HAVE_SGTTY
#ifdef TIOCGPGRP
  job_control = 1;
#else
  job_control = 0;
#endif /* TIOCGPGRP */
#endif /* sgtty */
}