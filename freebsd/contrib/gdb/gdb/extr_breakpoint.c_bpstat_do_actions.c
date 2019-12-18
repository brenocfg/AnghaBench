#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct command_line {struct command_line* next; } ;
struct cleanup {int dummy; } ;
typedef  TYPE_1__* bpstat ;
struct TYPE_3__ {struct command_line* commands; struct TYPE_3__* next; } ;

/* Variables and functions */
 scalar_t__ breakpoint_proceeded ; 
 int /*<<< orphan*/  cleanup_executing_breakpoints ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  execute_control_command (struct command_line*) ; 
 int executing_breakpoint_commands ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cleanup* make_cleanup_free_command_lines (struct command_line**) ; 

void
bpstat_do_actions (bpstat *bsp)
{
  bpstat bs;
  struct cleanup *old_chain;

  /* Avoid endless recursion if a `source' command is contained
     in bs->commands.  */
  if (executing_breakpoint_commands)
    return;

  executing_breakpoint_commands = 1;
  old_chain = make_cleanup (cleanup_executing_breakpoints, 0);

top:
  /* Note that (as of this writing), our callers all appear to
     be passing us the address of global stop_bpstat.  And, if
     our calls to execute_control_command cause the inferior to
     proceed, that global (and hence, *bsp) will change.

     We must be careful to not touch *bsp unless the inferior
     has not proceeded. */

  /* This pointer will iterate over the list of bpstat's. */
  bs = *bsp;

  breakpoint_proceeded = 0;
  for (; bs != NULL; bs = bs->next)
    {
      struct command_line *cmd;
      struct cleanup *this_cmd_tree_chain;

      /* Take ownership of the BSP's command tree, if it has one.

         The command tree could legitimately contain commands like
         'step' and 'next', which call clear_proceed_status, which
         frees stop_bpstat's command tree.  To make sure this doesn't
         free the tree we're executing out from under us, we need to
         take ownership of the tree ourselves.  Since a given bpstat's
         commands are only executed once, we don't need to copy it; we
         can clear the pointer in the bpstat, and make sure we free
         the tree when we're done.  */
      cmd = bs->commands;
      bs->commands = 0;
      this_cmd_tree_chain = make_cleanup_free_command_lines (&cmd);

      while (cmd != NULL)
	{
	  execute_control_command (cmd);

	  if (breakpoint_proceeded)
	    break;
	  else
	    cmd = cmd->next;
	}

      /* We can free this command tree now.  */
      do_cleanups (this_cmd_tree_chain);

      if (breakpoint_proceeded)
	/* The inferior is proceeded by the command; bomb out now.
	   The bpstat chain has been blown away by wait_for_inferior.
	   But since execution has stopped again, there is a new bpstat
	   to look at, so start over.  */
	goto top;
    }
  do_cleanups (old_chain);
}