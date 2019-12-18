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
struct task_entry {int /*<<< orphan*/  lwp; int /*<<< orphan*/  thread; int /*<<< orphan*/  known_tasks_index; } ;

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  current_lwp ; 
 int current_task ; 
 int current_task_id ; 
 int /*<<< orphan*/  current_task_index ; 
 int /*<<< orphan*/  current_thread ; 
 int /*<<< orphan*/  deprecated_selected_frame ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  fill_fpregset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fill_gregset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fpregset_saved ; 
 int /*<<< orphan*/  frame_relative_level (int /*<<< orphan*/ ) ; 
 int get_current_task () ; 
 struct task_entry* get_entry_vptr (int) ; 
 int /*<<< orphan*/  gregset_saved ; 
 int /*<<< orphan*/  print_stack_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf_filtered (char*,int) ; 
 scalar_t__ task_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
task_command (char *tidstr, int from_tty)
{
  int num;
  struct task_entry *e;

  if (!tidstr)
    error ("Please specify a task ID.  Use the \"info tasks\" command to\n"
	   "see the IDs of currently known tasks.");

  num = atoi (tidstr);
  e = get_entry_vptr (num);

  if (e == NULL)
    error ("Task ID %d not known.  Use the \"info tasks\" command to\n"
	   "see the IDs of currently known tasks.", num);

  if (current_task_id == -1)
    {
#if (defined(__alpha__) && defined(__osf__) && !defined(VXWORKS_TARGET))
      fill_gregset (&gregset_saved, -1);
      fill_fpregset (&fpregset_saved, -1);
#endif
      current_task_id = get_current_task ();
    }

  current_task = num;
  current_task_index = e->known_tasks_index;
  current_thread = e->thread;
  current_lwp = e->lwp;
  if (task_switch (e->thread, e->lwp) == 0)
    {
      /* FIXME: find_printable_frame should be defined in frame.h, and
         implemented in ada-lang.c */
      /*      find_printable_frame (deprecated_selected_frame, frame_relative_level (deprecated_selected_frame)); */
      printf_filtered ("[Switching to task %d]\n", num);
      print_stack_frame (deprecated_selected_frame,
			 frame_relative_level (deprecated_selected_frame), 1);
    }
  else
    printf_filtered ("Unable to switch to task %d\n", num);
}