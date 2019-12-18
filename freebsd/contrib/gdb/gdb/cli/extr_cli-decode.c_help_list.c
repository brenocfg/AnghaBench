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
struct ui_file {int dummy; } ;
struct cmd_list_element {int dummy; } ;
typedef  enum command_class { ____Placeholder_command_class } command_class ;

/* Variables and functions */
 int all_classes ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  help_cmd_list (struct cmd_list_element*,int,char*,int,struct ui_file*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

void
help_list (struct cmd_list_element *list, char *cmdtype,
	   enum command_class class, struct ui_file *stream)
{
  int len;
  char *cmdtype1, *cmdtype2;

  /* If CMDTYPE is "foo ", CMDTYPE1 gets " foo" and CMDTYPE2 gets "foo sub"  */
  len = strlen (cmdtype);
  cmdtype1 = (char *) alloca (len + 1);
  cmdtype1[0] = 0;
  cmdtype2 = (char *) alloca (len + 4);
  cmdtype2[0] = 0;
  if (len)
    {
      cmdtype1[0] = ' ';
      strncpy (cmdtype1 + 1, cmdtype, len - 1);
      cmdtype1[len] = 0;
      strncpy (cmdtype2, cmdtype, len - 1);
      strcpy (cmdtype2 + len - 1, " sub");
    }

  if (class == all_classes)
    fprintf_filtered (stream, "List of classes of %scommands:\n\n", cmdtype2);
  else
    fprintf_filtered (stream, "List of %scommands:\n\n", cmdtype2);

  help_cmd_list (list, class, cmdtype, (int) class >= 0, stream);

  if (class == all_classes)
    {
      fprintf_filtered (stream, "\n\
Type \"help%s\" followed by a class name for a list of commands in ",
			cmdtype1);
      wrap_here ("");
      fprintf_filtered (stream, "that class.");
    }

  fprintf_filtered (stream, "\nType \"help%s\" followed by %scommand name ",
		    cmdtype1, cmdtype2);
  wrap_here ("");
  fputs_filtered ("for ", stream);
  wrap_here ("");
  fputs_filtered ("full ", stream);
  wrap_here ("");
  fputs_filtered ("documentation.\n", stream);
  fputs_filtered ("Command name abbreviations are allowed if unambiguous.\n",
		  stream);
}