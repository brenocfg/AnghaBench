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
struct cmd_list_element {scalar_t__ class; struct cmd_list_element* next; } ;

/* Variables and functions */
 scalar_t__ class_user ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 struct cmd_list_element* lookup_cmd (char**,struct cmd_list_element*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  show_user_1 (struct cmd_list_element*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
show_user (char *args, int from_tty)
{
  struct cmd_list_element *c;
  extern struct cmd_list_element *cmdlist;

  if (args)
    {
      c = lookup_cmd (&args, cmdlist, "", 0, 1);
      if (c->class != class_user)
	error ("Not a user command.");
      show_user_1 (c, gdb_stdout);
    }
  else
    {
      for (c = cmdlist; c; c = c->next)
	{
	  if (c->class == class_user)
	    show_user_1 (c, gdb_stdout);
	}
    }
}