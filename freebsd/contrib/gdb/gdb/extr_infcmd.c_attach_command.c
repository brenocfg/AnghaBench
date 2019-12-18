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
 int /*<<< orphan*/  NO_STOP_QUIETLY ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOLIB_ADD (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STOP_QUIETLY_NO_SIGSTOP ; 
 int /*<<< orphan*/  attach_hook () ; 
 int /*<<< orphan*/  auto_solib_add ; 
 int /*<<< orphan*/  clear_proceed_status () ; 
 int /*<<< orphan*/  current_target ; 
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  exec_file_attach (char*,int) ; 
 scalar_t__ get_exec_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  init_wait_for_inferior () ; 
 int /*<<< orphan*/  normal_stop () ; 
 scalar_t__ query (char*) ; 
 int /*<<< orphan*/  re_enable_breakpoints_in_shlibs () ; 
 char* savestring (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  source_full_path_of (char*,char**) ; 
 int /*<<< orphan*/  stop_soon ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  symbol_file_add_main (char*,int) ; 
 int /*<<< orphan*/  target_attach (char*,int) ; 
 scalar_t__ target_has_execution ; 
 int /*<<< orphan*/  target_kill () ; 
 char* target_pid_to_exec_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_post_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_terminal_inferior () ; 
 int /*<<< orphan*/  target_terminal_init () ; 
 int /*<<< orphan*/  wait_for_inferior () ; 

void
attach_command (char *args, int from_tty)
{
  char *exec_file;
  char *full_exec_path = NULL;

  dont_repeat ();		/* Not for the faint of heart */

  if (target_has_execution)
    {
      if (query ("A program is being debugged already.  Kill it? "))
	target_kill ();
      else
	error ("Not killed.");
    }

  target_attach (args, from_tty);

  /* Set up the "saved terminal modes" of the inferior
     based on what modes we are starting it with.  */
  target_terminal_init ();

  /* Install inferior's terminal modes.  */
  target_terminal_inferior ();

  /* Set up execution context to know that we should return from
     wait_for_inferior as soon as the target reports a stop.  */
  init_wait_for_inferior ();
  clear_proceed_status ();

  /* No traps are generated when attaching to inferior under Mach 3
     or GNU hurd.  */
#ifndef ATTACH_NO_WAIT
  /* Careful here. See comments in inferior.h.  Basically some OSes
     don't ignore SIGSTOPs on continue requests anymore.  We need a
     way for handle_inferior_event to reset the stop_signal variable
     after an attach, and this is what STOP_QUIETLY_NO_SIGSTOP is for.  */
  stop_soon = STOP_QUIETLY_NO_SIGSTOP;
  wait_for_inferior ();
  stop_soon = NO_STOP_QUIETLY;
#endif

  /*
   * If no exec file is yet known, try to determine it from the
   * process itself.
   */
  exec_file = (char *) get_exec_file (0);
  if (!exec_file)
    {
      exec_file = target_pid_to_exec_file (PIDGET (inferior_ptid));
      if (exec_file)
	{
	  /* It's possible we don't have a full path, but rather just a
	     filename.  Some targets, such as HP-UX, don't provide the
	     full path, sigh.

	     Attempt to qualify the filename against the source path.
	     (If that fails, we'll just fall back on the original
	     filename.  Not much more we can do...)
	   */
	  if (!source_full_path_of (exec_file, &full_exec_path))
	    full_exec_path = savestring (exec_file, strlen (exec_file));

	  exec_file_attach (full_exec_path, from_tty);
	  symbol_file_add_main (full_exec_path, from_tty);
	}
    }

#ifdef SOLIB_ADD
  /* Add shared library symbols from the newly attached process, if any.  */
  SOLIB_ADD ((char *) 0, from_tty, &current_target, auto_solib_add);
  re_enable_breakpoints_in_shlibs ();
#endif

  /* Take any necessary post-attaching actions for this platform.
   */
  target_post_attach (PIDGET (inferior_ptid));

  normal_stop ();

  if (attach_hook)
    attach_hook ();
}