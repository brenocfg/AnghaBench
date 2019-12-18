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
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 struct cmd_list_element* add_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct cmd_list_element* add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_com_alias (char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  add_info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_info_alias (char*,char*,int) ; 
 int /*<<< orphan*/  add_prefix_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cmd_list_element* add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 struct cmd_list_element* add_show_from_set (struct cmd_list_element*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  advance_command ; 
 int /*<<< orphan*/  all_registers_info ; 
 int /*<<< orphan*/  attach_command ; 
 int /*<<< orphan*/  class_alias ; 
 int /*<<< orphan*/  class_files ; 
 int /*<<< orphan*/  class_info ; 
 int /*<<< orphan*/  class_run ; 
 int /*<<< orphan*/  cmdlist ; 
 int /*<<< orphan*/  continue_command ; 
 int /*<<< orphan*/  detach_command ; 
 int /*<<< orphan*/  disconnect_command ; 
 int /*<<< orphan*/  environment_info ; 
 int /*<<< orphan*/  filename_completer ; 
 int /*<<< orphan*/  finish_command ; 
 int /*<<< orphan*/  float_info ; 
 int /*<<< orphan*/  go_command ; 
 int /*<<< orphan*/  inferior_args ; 
 int /*<<< orphan*/  inferior_environ ; 
 int /*<<< orphan*/  init_environ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interrupt_target_command ; 
 int /*<<< orphan*/  jump_command ; 
 int /*<<< orphan*/  location_completer ; 
 int /*<<< orphan*/  make_environ () ; 
 int /*<<< orphan*/  next_command ; 
 int /*<<< orphan*/  nexti_command ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  nofp_registers_info ; 
 int /*<<< orphan*/  noop_completer ; 
 int /*<<< orphan*/  notice_args_read ; 
 int /*<<< orphan*/  notice_args_set ; 
 int /*<<< orphan*/  path_command ; 
 int /*<<< orphan*/  path_info ; 
 int /*<<< orphan*/  program_info ; 
 int /*<<< orphan*/  run_command ; 
 int /*<<< orphan*/  run_no_args_command ; 
 int /*<<< orphan*/  set_cmd_completer (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cmd_sfunc (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_environment_command ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  signal_command ; 
 int /*<<< orphan*/  step_command ; 
 int /*<<< orphan*/  stepi_command ; 
 int /*<<< orphan*/  tty_command ; 
 int /*<<< orphan*/  unset_command ; 
 int /*<<< orphan*/  unset_environment_command ; 
 int /*<<< orphan*/  unsetlist ; 
 int /*<<< orphan*/  until_command ; 
 int /*<<< orphan*/  var_string_noescape ; 
 int /*<<< orphan*/  vector_info ; 
 scalar_t__ xdb_commands ; 

void
_initialize_infcmd (void)
{
  struct cmd_list_element *c;

  c = add_com ("tty", class_run, tty_command,
	       "Set terminal for future runs of program being debugged.");
  set_cmd_completer (c, filename_completer);

  c = add_set_cmd ("args", class_run, var_string_noescape,
		   (char *) &inferior_args,
		   "Set argument list to give program being debugged when it is started.\n\
Follow this command with any number of args, to be passed to the program.",
		   &setlist);
  set_cmd_completer (c, filename_completer);
  set_cmd_sfunc (c, notice_args_set);
  c = add_show_from_set (c, &showlist);
  set_cmd_sfunc (c, notice_args_read);

  c = add_cmd
    ("environment", no_class, environment_info,
     "The environment to give the program, or one variable's value.\n\
With an argument VAR, prints the value of environment variable VAR to\n\
give the program being debugged.  With no arguments, prints the entire\n\
environment to be given to the program.", &showlist);
  set_cmd_completer (c, noop_completer);

  add_prefix_cmd ("unset", no_class, unset_command,
		  "Complement to certain \"set\" commands.",
		  &unsetlist, "unset ", 0, &cmdlist);

  c = add_cmd ("environment", class_run, unset_environment_command,
	       "Cancel environment variable VAR for the program.\n\
This does not affect the program until the next \"run\" command.",
	       &unsetlist);
  set_cmd_completer (c, noop_completer);

  c = add_cmd ("environment", class_run, set_environment_command,
	       "Set environment variable value to give the program.\n\
Arguments are VAR VALUE where VAR is variable name and VALUE is value.\n\
VALUES of environment variables are uninterpreted strings.\n\
This does not affect the program until the next \"run\" command.",
	       &setlist);
  set_cmd_completer (c, noop_completer);

  c = add_com ("path", class_files, path_command,
	       "Add directory DIR(s) to beginning of search path for object files.\n\
$cwd in the path means the current working directory.\n\
This path is equivalent to the $PATH shell variable.  It is a list of\n\
directories, separated by colons.  These directories are searched to find\n\
fully linked executable files and separately compiled object files as needed.");
  set_cmd_completer (c, filename_completer);

  c = add_cmd ("paths", no_class, path_info,
	       "Current search path for finding object files.\n\
$cwd in the path means the current working directory.\n\
This path is equivalent to the $PATH shell variable.  It is a list of\n\
directories, separated by colons.  These directories are searched to find\n\
fully linked executable files and separately compiled object files as needed.",
	       &showlist);
  set_cmd_completer (c, noop_completer);

  add_com ("attach", class_run, attach_command,
	   "Attach to a process or file outside of GDB.\n\
This command attaches to another target, of the same type as your last\n\
\"target\" command (\"info files\" will show your target stack).\n\
The command may take as argument a process id or a device file.\n\
For a process id, you must have permission to send the process a signal,\n\
and it must have the same effective uid as the debugger.\n\
When using \"attach\" with a process id, the debugger finds the\n\
program running in the process, looking first in the current working\n\
directory, or (if not found there) using the source file search path\n\
(see the \"directory\" command).  You can also use the \"file\" command\n\
to specify the program, and to load its symbol table.");

  add_com ("detach", class_run, detach_command,
	   "Detach a process or file previously attached.\n\
If a process, it is no longer traced, and it continues its execution.  If\n\
you were debugging a file, the file is closed and gdb no longer accesses it.");

  add_com ("disconnect", class_run, disconnect_command,
	   "Disconnect from a target.\n\
The target will wait for another debugger to connect.  Not available for\n\
all targets.");

  add_com ("signal", class_run, signal_command,
	   "Continue program giving it signal specified by the argument.\n\
An argument of \"0\" means continue program without giving it a signal.");

  add_com ("stepi", class_run, stepi_command,
	   "Step one instruction exactly.\n\
Argument N means do this N times (or till program stops for another reason).");
  add_com_alias ("si", "stepi", class_alias, 0);

  add_com ("nexti", class_run, nexti_command,
	   "Step one instruction, but proceed through subroutine calls.\n\
Argument N means do this N times (or till program stops for another reason).");
  add_com_alias ("ni", "nexti", class_alias, 0);

  add_com ("finish", class_run, finish_command,
	   "Execute until selected stack frame returns.\n\
Upon return, the value returned is printed and put in the value history.");

  add_com ("next", class_run, next_command,
	   "Step program, proceeding through subroutine calls.\n\
Like the \"step\" command as long as subroutine calls do not happen;\n\
when they do, the call is treated as one instruction.\n\
Argument N means do this N times (or till program stops for another reason).");
  add_com_alias ("n", "next", class_run, 1);
  if (xdb_commands)
    add_com_alias ("S", "next", class_run, 1);

  add_com ("step", class_run, step_command,
	   "Step program until it reaches a different source line.\n\
Argument N means do this N times (or till program stops for another reason).");
  add_com_alias ("s", "step", class_run, 1);

  c = add_com ("until", class_run, until_command,
	       "Execute until the program reaches a source line greater than the current\n\
or a specified location (same args as break command) within the current frame.");
  set_cmd_completer (c, location_completer);
  add_com_alias ("u", "until", class_run, 1);

  c = add_com ("advance", class_run, advance_command,
	       "Continue the program up to the given location (same form as args for break command).\n\
Execution will also stop upon exit from the current stack frame.");
  set_cmd_completer (c, location_completer);

  c = add_com ("jump", class_run, jump_command,
	       "Continue program being debugged at specified line or address.\n\
Give as argument either LINENUM or *ADDR, where ADDR is an expression\n\
for an address to start at.");
  set_cmd_completer (c, location_completer);

  if (xdb_commands)
    {
      c = add_com ("go", class_run, go_command,
		   "Usage: go <location>\n\
Continue program being debugged, stopping at specified line or \n\
address.\n\
Give as argument either LINENUM or *ADDR, where ADDR is an \n\
expression for an address to start at.\n\
This command is a combination of tbreak and jump.");
      set_cmd_completer (c, location_completer);
    }

  if (xdb_commands)
    add_com_alias ("g", "go", class_run, 1);

  add_com ("continue", class_run, continue_command,
	   "Continue program being debugged, after signal or breakpoint.\n\
If proceeding from breakpoint, a number N may be used as an argument,\n\
which means to set the ignore count of that breakpoint to N - 1 (so that\n\
the breakpoint won't break until the Nth time it is reached).");
  add_com_alias ("c", "cont", class_run, 1);
  add_com_alias ("fg", "cont", class_run, 1);

  c = add_com ("run", class_run, run_command,
	   "Start debugged program.  You may specify arguments to give it.\n\
Args may include \"*\", or \"[...]\"; they are expanded using \"sh\".\n\
Input and output redirection with \">\", \"<\", or \">>\" are also allowed.\n\n\
With no arguments, uses arguments last specified (with \"run\" or \"set args\").\n\
To cancel previous arguments and run with no arguments,\n\
use \"set args\" without arguments.");
  set_cmd_completer (c, filename_completer);
  add_com_alias ("r", "run", class_run, 1);
  if (xdb_commands)
    add_com ("R", class_run, run_no_args_command,
	     "Start debugged program with no arguments.");

  add_com ("interrupt", class_run, interrupt_target_command,
	   "Interrupt the execution of the debugged program.");

  add_info ("registers", nofp_registers_info,
	    "List of integer registers and their contents, for selected stack frame.\n\
Register name as argument means describe only that register.");
  add_info_alias ("r", "registers", 1);

  if (xdb_commands)
    add_com ("lr", class_info, nofp_registers_info,
	     "List of integer registers and their contents, for selected stack frame.\n\
  Register name as argument means describe only that register.");
  add_info ("all-registers", all_registers_info,
	    "List of all registers and their contents, for selected stack frame.\n\
Register name as argument means describe only that register.");

  add_info ("program", program_info,
	    "Execution status of the program.");

  add_info ("float", float_info,
	    "Print the status of the floating point unit\n");

  add_info ("vector", vector_info,
	    "Print the status of the vector unit\n");

  inferior_environ = make_environ ();
  init_environ (inferior_environ);
}