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
 int /*<<< orphan*/  add_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct cmd_list_element**) ; 
 int /*<<< orphan*/  add_prefix_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct cmd_list_element**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_setshow_boolean_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cmd_list_element**,struct cmd_list_element**) ; 
 int /*<<< orphan*/  add_setshow_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cmd_list_element**,struct cmd_list_element**) ; 
 int /*<<< orphan*/  class_support ; 
 int /*<<< orphan*/  logging_filename ; 
 int /*<<< orphan*/  logging_overwrite ; 
 int /*<<< orphan*/  logging_redirect ; 
 int /*<<< orphan*/  set_logging_command ; 
 int /*<<< orphan*/  set_logging_off ; 
 int /*<<< orphan*/  set_logging_on ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  show_logging_command ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  var_filename ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

void
_initialize_cli_logging (void)
{
  static struct cmd_list_element *set_logging_cmdlist, *show_logging_cmdlist;

  
  add_prefix_cmd ("logging", class_support, set_logging_command,
		  "Set logging options", &set_logging_cmdlist,
		  "set logging ", 0, &setlist);
  add_prefix_cmd ("logging", class_support, show_logging_command,
		  "Show logging options", &show_logging_cmdlist,
		  "show logging ", 0, &showlist);
  add_setshow_boolean_cmd ("overwrite", class_support, &logging_overwrite,
			   "Set whether logging overwrites or appends "
			   "to the log file.\n",
			   "Show whether logging overwrites or appends "
			   "to the log file.\n",
			   NULL, NULL, &set_logging_cmdlist, &show_logging_cmdlist);
  add_setshow_boolean_cmd ("redirect", class_support, &logging_redirect,
			   "Set the logging output mode.\n"
			   "If redirect is off, output will go to both the "
			   "screen and the log file.\n"
			   "If redirect is on, output will go only to the log "
			   "file.",
			   "Show the logging output mode.\n"
			   "If redirect is off, output will go to both the "
			   "screen and the log file.\n"
			   "If redirect is on, output will go only to the log "
			   "file.",
			   NULL, NULL, &set_logging_cmdlist, &show_logging_cmdlist);
  add_setshow_cmd ("file", class_support, var_filename, &logging_filename,
		   "Set the current logfile.", "Show the current logfile.",
		   NULL, NULL, &set_logging_cmdlist, &show_logging_cmdlist);
  add_cmd ("on", class_support, set_logging_on,
	   "Enable logging.", &set_logging_cmdlist);
  add_cmd ("off", class_support, set_logging_off,
	   "Disable logging.", &set_logging_cmdlist);

  logging_filename = xstrdup ("gdb.txt");
}