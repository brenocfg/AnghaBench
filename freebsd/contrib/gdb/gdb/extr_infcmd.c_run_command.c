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
 int /*<<< orphan*/  SOLIB_RESTART () ; 
 int /*<<< orphan*/  async_disable_stdin () ; 
 int /*<<< orphan*/  clear_breakpoint_hit_counts () ; 
 int /*<<< orphan*/  do_run_cleanups (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  environ_vector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ event_loop_p ; 
 scalar_t__ get_exec_file (int /*<<< orphan*/ ) ; 
 char* get_inferior_args () ; 
 int /*<<< orphan*/  inferior_environ ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  init_wait_for_inferior () ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  objfile_purge_solibs () ; 
 int /*<<< orphan*/  ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query (char*) ; 
 int /*<<< orphan*/  reopen_exec_file () ; 
 int /*<<< orphan*/  reread_symbols () ; 
 char* set_inferior_args (int /*<<< orphan*/ ) ; 
 int strip_bg_char (char**) ; 
 scalar_t__ target_can_async_p () ; 
 int /*<<< orphan*/  target_create_inferior (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ target_has_execution ; 
 int /*<<< orphan*/  target_kill () ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ui_out_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_spaces (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ui_out_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  xfree (char*) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static void
run_command (char *args, int from_tty)
{
  char *exec_file;

  dont_repeat ();

  if (! ptid_equal (inferior_ptid, null_ptid) && target_has_execution)
    {
      if (from_tty
	  && !query ("The program being debugged has been started already.\n\
Start it from the beginning? "))
	error ("Program not restarted.");
      target_kill ();
#if defined(SOLIB_RESTART)
      SOLIB_RESTART ();
#endif
      init_wait_for_inferior ();
    }

  clear_breakpoint_hit_counts ();

  /* Purge old solib objfiles. */
  objfile_purge_solibs ();

  do_run_cleanups (NULL);

  /* The comment here used to read, "The exec file is re-read every
     time we do a generic_mourn_inferior, so we just have to worry
     about the symbol file."  The `generic_mourn_inferior' function
     gets called whenever the program exits.  However, suppose the
     program exits, and *then* the executable file changes?  We need
     to check again here.  Since reopen_exec_file doesn't do anything
     if the timestamp hasn't changed, I don't see the harm.  */
  reopen_exec_file ();
  reread_symbols ();

  exec_file = (char *) get_exec_file (0);

  /* We keep symbols from add-symbol-file, on the grounds that the
     user might want to add some symbols before running the program
     (right?).  But sometimes (dynamic loading where the user manually
     introduces the new symbols with add-symbol-file), the code which
     the symbols describe does not persist between runs.  Currently
     the user has to manually nuke all symbols between runs if they
     want them to go away (PR 2207).  This is probably reasonable.  */

  if (!args)
    {
      if (event_loop_p && target_can_async_p ())
	async_disable_stdin ();
    }
  else
    {
      int async_exec = strip_bg_char (&args);

      /* If we get a request for running in the bg but the target
         doesn't support it, error out. */
      if (event_loop_p && async_exec && !target_can_async_p ())
	error ("Asynchronous execution not supported on this target.");

      /* If we don't get a request of running in the bg, then we need
         to simulate synchronous (fg) execution. */
      if (event_loop_p && !async_exec && target_can_async_p ())
	{
	  /* Simulate synchronous execution */
	  async_disable_stdin ();
	}

      /* If there were other args, beside '&', process them. */
      if (args)
	{
          char *old_args = set_inferior_args (xstrdup (args));
          xfree (old_args);
	}
    }

  if (from_tty)
    {
      ui_out_field_string (uiout, NULL, "Starting program");
      ui_out_text (uiout, ": ");
      if (exec_file)
	ui_out_field_string (uiout, "execfile", exec_file);
      ui_out_spaces (uiout, 1);
      /* We call get_inferior_args() because we might need to compute
	 the value now.  */
      ui_out_field_string (uiout, "infargs", get_inferior_args ());
      ui_out_text (uiout, "\n");
      ui_out_flush (uiout);
    }

  /* We call get_inferior_args() because we might need to compute
     the value now.  */
  target_create_inferior (exec_file, get_inferior_args (),
			  environ_vector (inferior_environ));
}