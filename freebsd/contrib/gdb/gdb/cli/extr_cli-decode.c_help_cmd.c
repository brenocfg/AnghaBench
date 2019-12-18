#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ui_file {int dummy; } ;
struct cmd_list_element {char* doc; char* prefixname; TYPE_2__* hook_post; TYPE_1__* hook_pre; int /*<<< orphan*/  class; int /*<<< orphan*/ * func; struct cmd_list_element** prefixlist; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  all_classes ; 
 int /*<<< orphan*/  all_commands ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  help_all (struct ui_file*) ; 
 int /*<<< orphan*/  help_list (struct cmd_list_element*,char*,int /*<<< orphan*/ ,struct ui_file*) ; 
 struct cmd_list_element* lookup_cmd (char**,struct cmd_list_element*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

void
help_cmd (char *command, struct ui_file *stream)
{
  struct cmd_list_element *c;
  extern struct cmd_list_element *cmdlist;

  if (!command)
    {
      help_list (cmdlist, "", all_classes, stream);
      return;
    }

  if (strcmp (command, "all") == 0)
    {
      help_all (stream);
      return;
    }

  c = lookup_cmd (&command, cmdlist, "", 0, 0);

  if (c == 0)
    return;

  /* There are three cases here.
     If c->prefixlist is nonzero, we have a prefix command.
     Print its documentation, then list its subcommands.

     If c->func is non NULL, we really have a command.  Print its
     documentation and return.

     If c->func is NULL, we have a class name.  Print its
     documentation (as if it were a command) and then set class to the
     number of this class so that the commands in the class will be
     listed.  */

  fputs_filtered (c->doc, stream);
  fputs_filtered ("\n", stream);

  if (c->prefixlist == 0 && c->func != NULL)
    return;
  fprintf_filtered (stream, "\n");

  /* If this is a prefix command, print it's subcommands */
  if (c->prefixlist)
    help_list (*c->prefixlist, c->prefixname, all_commands, stream);

  /* If this is a class name, print all of the commands in the class */
  if (c->func == NULL)
    help_list (cmdlist, "", c->class, stream);

  if (c->hook_pre || c->hook_post)
    fprintf_filtered (stream,
                      "\nThis command has a hook (or hooks) defined:\n");

  if (c->hook_pre)
    fprintf_filtered (stream, 
                      "\tThis command is run after  : %s (pre hook)\n",
                    c->hook_pre->name);
  if (c->hook_post)
    fprintf_filtered (stream, 
                      "\tThis command is run before : %s (post hook)\n",
                    c->hook_post->name);
}