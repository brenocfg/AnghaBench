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
 struct cmd_list_element* add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (struct cmd_list_element*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_files ; 
 int /*<<< orphan*/  cmdlist ; 
 int /*<<< orphan*/  core_file_command ; 
 int /*<<< orphan*/  filename_completer ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  gnutarget_string ; 
 int /*<<< orphan*/  set_cmd_completer (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cmd_sfunc (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gnutarget (char*) ; 
 int /*<<< orphan*/  set_gnutarget_command ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  var_string_noescape ; 

void
_initialize_core (void)
{
  struct cmd_list_element *c;
  c = add_cmd ("core-file", class_files, core_file_command,
	       "Use FILE as core dump for examining memory and registers.\n\
No arg means have no core file.  This command has been superseded by the\n\
`target core' and `detach' commands.", &cmdlist);
  set_cmd_completer (c, filename_completer);

  c = add_set_cmd ("gnutarget", class_files, var_string_noescape,
		   (char *) &gnutarget_string,
		   "Set the current BFD target.\n\
Use `set gnutarget auto' to specify automatic detection.",
		   &setlist);
  set_cmd_sfunc (c, set_gnutarget_command);
  add_show_from_set (c, &showlist);

  if (getenv ("GNUTARGET"))
    set_gnutarget (getenv ("GNUTARGET"));
  else
    set_gnutarget ("auto");
}