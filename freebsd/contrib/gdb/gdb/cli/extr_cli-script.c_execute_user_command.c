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
struct command_line {struct command_line* next; } ;
struct cmd_list_element {struct command_line* user_commands; } ;
struct cleanup {int dummy; } ;
typedef  enum command_control_type { ____Placeholder_command_control_type } command_control_type ;
typedef  int FILE ;

/* Variables and functions */
 int break_control ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  do_restore_instream_cleanup ; 
 int /*<<< orphan*/  do_restore_user_call_depth ; 
 int /*<<< orphan*/  error (char*) ; 
 int execute_control_command (struct command_line*) ; 
 int* instream ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,int*) ; 
 struct cleanup* setup_user_args (char*) ; 
 int simple_control ; 
 int /*<<< orphan*/  warning (char*) ; 

void
execute_user_command (struct cmd_list_element *c, char *args)
{
  struct command_line *cmdlines;
  struct cleanup *old_chain;
  enum command_control_type ret;
  static int user_call_depth = 0;
  extern int max_user_call_depth;

  old_chain = setup_user_args (args);

  cmdlines = c->user_commands;
  if (cmdlines == 0)
    /* Null command */
    return;

  if (++user_call_depth > max_user_call_depth)
    error ("Max user call depth exceeded -- command aborted\n");

  old_chain = make_cleanup (do_restore_user_call_depth, &user_call_depth);

  /* Set the instream to 0, indicating execution of a
     user-defined function.  */
  old_chain = make_cleanup (do_restore_instream_cleanup, instream);
  instream = (FILE *) 0;
  while (cmdlines)
    {
      ret = execute_control_command (cmdlines);
      if (ret != simple_control && ret != break_control)
	{
	  warning ("Error in control structure.\n");
	  break;
	}
      cmdlines = cmdlines->next;
    }
  do_cleanups (old_chain);

  user_call_depth--;
}