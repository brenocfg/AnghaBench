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

/* Variables and functions */
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOLIB_CREATE_INFERIOR_HOOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOLIB_RESTART () ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  exec_file_attach (char*,int /*<<< orphan*/ ) ; 
 struct target_ops* find_run_target () ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  insert_breakpoints () ; 
 int /*<<< orphan*/  may_follow_exec ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*) ; 
 int /*<<< orphan*/  push_target (struct target_ops*) ; 
 scalar_t__ step_range_end ; 
 scalar_t__ step_range_start ; 
 int /*<<< orphan*/ * step_resume_breakpoint ; 
 int /*<<< orphan*/  symbol_file_add_main (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_mourn_inferior () ; 
 int /*<<< orphan*/ * through_sigtramp_breakpoint ; 
 int /*<<< orphan*/  update_breakpoints_after_exec () ; 

__attribute__((used)) static void
follow_exec (int pid, char *execd_pathname)
{
  int saved_pid = pid;
  struct target_ops *tgt;

  if (!may_follow_exec)
    return;

  /* This is an exec event that we actually wish to pay attention to.
     Refresh our symbol table to the newly exec'd program, remove any
     momentary bp's, etc.

     If there are breakpoints, they aren't really inserted now,
     since the exec() transformed our inferior into a fresh set
     of instructions.

     We want to preserve symbolic breakpoints on the list, since
     we have hopes that they can be reset after the new a.out's
     symbol table is read.

     However, any "raw" breakpoints must be removed from the list
     (e.g., the solib bp's), since their address is probably invalid
     now.

     And, we DON'T want to call delete_breakpoints() here, since
     that may write the bp's "shadow contents" (the instruction
     value that was overwritten witha TRAP instruction).  Since
     we now have a new a.out, those shadow contents aren't valid. */
  update_breakpoints_after_exec ();

  /* If there was one, it's gone now.  We cannot truly step-to-next
     statement through an exec(). */
  step_resume_breakpoint = NULL;
  step_range_start = 0;
  step_range_end = 0;

  /* If there was one, it's gone now. */
  through_sigtramp_breakpoint = NULL;

  /* What is this a.out's name? */
  printf_unfiltered ("Executing new program: %s\n", execd_pathname);

  /* We've followed the inferior through an exec.  Therefore, the
     inferior has essentially been killed & reborn. */

  /* First collect the run target in effect.  */
  tgt = find_run_target ();
  /* If we can't find one, things are in a very strange state...  */
  if (tgt == NULL)
    error ("Could find run target to save before following exec");

  gdb_flush (gdb_stdout);
  target_mourn_inferior ();
  inferior_ptid = pid_to_ptid (saved_pid);
  /* Because mourn_inferior resets inferior_ptid. */
  push_target (tgt);

  /* That a.out is now the one to use. */
  exec_file_attach (execd_pathname, 0);

  /* And also is where symbols can be found. */
  symbol_file_add_main (execd_pathname, 0);

  /* Reset the shared library package.  This ensures that we get
     a shlib event when the child reaches "_start", at which point
     the dld will have had a chance to initialize the child. */
#if defined(SOLIB_RESTART)
  SOLIB_RESTART ();
#endif
#ifdef SOLIB_CREATE_INFERIOR_HOOK
  SOLIB_CREATE_INFERIOR_HOOK (PIDGET (inferior_ptid));
#endif

  /* Reinsert all breakpoints.  (Those which were symbolic have
     been reset to the proper address in the new a.out, thanks
     to symbol_file_command...) */
  insert_breakpoints ();

  /* The next resume of this inferior should bring it to the shlib
     startup breakpoints.  (If the user had also set bp's on
     "main" from the old (parent) process, then they'll auto-
     matically get reset there in the new process.) */
}