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
 int /*<<< orphan*/ * deprecated_selected_frame ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fputs_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_relative_level (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  init_thread_list () ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  print_stack_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  query (char*) ; 
 scalar_t__ target_has_stack ; 
 int /*<<< orphan*/  target_kill () ; 
 int /*<<< orphan*/  target_longname ; 

__attribute__((used)) static void
kill_command (char *arg, int from_tty)
{
  /* FIXME:  This should not really be inferior_ptid (or target_has_execution).
     It should be a distinct flag that indicates that a target is active, cuz
     some targets don't have processes! */

  if (ptid_equal (inferior_ptid, null_ptid))
    error ("The program is not being run.");
  if (!query ("Kill the program being debugged? "))
    error ("Not confirmed.");
  target_kill ();

  init_thread_list ();		/* Destroy thread info */

  /* Killing off the inferior can leave us with a core file.  If so,
     print the state we are left in.  */
  if (target_has_stack)
    {
      printf_filtered ("In %s,\n", target_longname);
      if (deprecated_selected_frame == NULL)
	fputs_filtered ("No selected stack frame.\n", gdb_stdout);
      else
	print_stack_frame (deprecated_selected_frame,
			   frame_relative_level (deprecated_selected_frame), 1);
    }
}