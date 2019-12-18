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
struct cmd_list_element {char* prefixname; int /*<<< orphan*/  class; int /*<<< orphan*/ * func; struct cmd_list_element** prefixlist; scalar_t__ abbrev_flag; struct cmd_list_element* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  all_commands ; 
 int /*<<< orphan*/  help_cmd_list (struct cmd_list_element*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct ui_file*) ; 

__attribute__((used)) static void
help_all (struct ui_file *stream)
{
  struct cmd_list_element *c;
  extern struct cmd_list_element *cmdlist;

  for (c = cmdlist; c; c = c->next)
    {
      if (c->abbrev_flag)
        continue;
      /* If this is a prefix command, print it's subcommands */
      if (c->prefixlist)
        help_cmd_list (*c->prefixlist, all_commands, c->prefixname, 0, stream);
    
      /* If this is a class name, print all of the commands in the class */
      else if (c->func == NULL)
        help_cmd_list (cmdlist, c->class, "", 0, stream);
    }
}