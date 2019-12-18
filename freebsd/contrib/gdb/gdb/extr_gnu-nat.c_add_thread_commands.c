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
 int /*<<< orphan*/  add_alias_cmd (char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_prefix_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_run ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  set_thread_cmd ; 
 int /*<<< orphan*/  set_thread_cmd_list ; 
 int /*<<< orphan*/  set_thread_default_cmd ; 
 int /*<<< orphan*/  set_thread_default_cmd_list ; 
 int /*<<< orphan*/  set_thread_detach_sc_cmd ; 
 int /*<<< orphan*/  set_thread_exc_port_cmd ; 
 int /*<<< orphan*/  set_thread_pause_cmd ; 
 int /*<<< orphan*/  set_thread_run_cmd ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  show_thread_cmd ; 
 int /*<<< orphan*/  show_thread_cmd_list ; 
 int /*<<< orphan*/  show_thread_default_cmd ; 
 int /*<<< orphan*/  show_thread_default_cmd_list ; 
 int /*<<< orphan*/  show_thread_detach_sc_cmd ; 
 int /*<<< orphan*/  show_thread_pause_cmd ; 
 int /*<<< orphan*/  show_thread_run_cmd ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  thread_cmd_list ; 
 int /*<<< orphan*/  thread_takeover_sc_cmd ; 

__attribute__((used)) static void
add_thread_commands (void)
{
  add_prefix_cmd ("thread", no_class, set_thread_cmd,
		  "Command prefix for setting thread properties.",
		  &set_thread_cmd_list, "set thread ", 0, &setlist);
  add_prefix_cmd ("default", no_class, show_thread_cmd,
		  "Command prefix for setting default thread properties.",
		  &set_thread_default_cmd_list, "set thread default ", 0,
		  &set_thread_cmd_list);
  add_prefix_cmd ("thread", no_class, set_thread_default_cmd,
		  "Command prefix for showing thread properties.",
		  &show_thread_cmd_list, "show thread ", 0, &showlist);
  add_prefix_cmd ("default", no_class, show_thread_default_cmd,
		  "Command prefix for showing default thread properties.",
		  &show_thread_default_cmd_list, "show thread default ", 0,
		  &show_thread_cmd_list);

  add_cmd ("pause", class_run, set_thread_pause_cmd,
	   "Set whether the current thread is suspended \
while gdb has control.\n\
A value of \"on\" takes effect immediately, otherwise nothing happens\n\
until the next time the program is continued.  This property normally\n\
has no effect because the whole task is suspended, however, that may\n\
be disabled with \"set task pause off\".\n\
The default value is \"off\".",
	   &set_thread_cmd_list);
  add_cmd ("pause", no_class, show_thread_pause_cmd,
	   "Show whether the current thread is suspended \
while gdb has control.",
	   &show_thread_cmd_list);

  add_cmd ("run", class_run, set_thread_run_cmd,
	   "Set whether the current thread is allowed to run.",
	   &set_thread_cmd_list);
  add_cmd ("run", no_class, show_thread_run_cmd,
	   "Show whether the current thread is allowed to run.",
	   &show_thread_cmd_list);

  add_cmd ("detach-suspend-count", class_run, set_thread_detach_sc_cmd,
	   "Set the suspend count will leave on the thread when detaching.\n\
Note that this is relative to suspend count when gdb noticed the thread;\n\
use the `thread takeover-suspend-count' to force it to an absolute value.",
	   &set_thread_cmd_list);
  add_cmd ("detach-suspend-count", no_class, show_thread_detach_sc_cmd,
	   "Show the suspend count will leave on the thread when detaching.\n\
Note that this is relative to suspend count when gdb noticed the thread;\n\
use the `thread takeover-suspend-count' to force it to an absolute value.",
	   &show_thread_cmd_list);

  add_cmd ("exception-port", no_class, set_thread_exc_port_cmd,
	   "Set the thread exception port to which we forward exceptions.\n\
This overrides the task exception port.\n\
The argument should be the value of the send right in the task.",
	   &set_thread_cmd_list);
  add_alias_cmd ("excp", "exception-port", no_class, 1, &set_thread_cmd_list);
  add_alias_cmd ("exc-port", "exception-port", no_class, 1,
		 &set_thread_cmd_list);

  add_cmd ("takeover-suspend-count", no_class, thread_takeover_sc_cmd,
	   "Force the threads absolute suspend-count to be gdb's.\n\
Prior to giving this command, gdb's thread suspend-counts are relative\n\
to the thread's initial suspend-count when gdb notices the threads.",
	   &thread_cmd_list);
}