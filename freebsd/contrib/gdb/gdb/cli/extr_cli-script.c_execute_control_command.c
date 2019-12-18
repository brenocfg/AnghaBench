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
struct value {int dummy; } ;
typedef  char expression ;
struct command_line {int control_type; int body_count; struct command_line* next; struct command_line** body_list; int /*<<< orphan*/  line; } ;
struct cleanup {int dummy; } ;
typedef  enum command_control_type { ____Placeholder_command_control_type } command_control_type ;

/* Variables and functions */
 int /*<<< orphan*/  QUIT ; 
#define  break_control 132 
#define  continue_control 131 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct value* evaluate_expression (char*) ; 
 int /*<<< orphan*/  execute_command (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_current_contents ; 
#define  if_control 130 
 char* insert_args (int /*<<< orphan*/ ) ; 
 int invalid_control ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  null_cleanup ; 
 char* parse_expression (char*) ; 
#define  simple_control 129 
 int /*<<< orphan*/  value_free_to_mark (struct value*) ; 
 struct value* value_mark () ; 
 int value_true (struct value*) ; 
 int /*<<< orphan*/  warning (char*) ; 
#define  while_control 128 

enum command_control_type
execute_control_command (struct command_line *cmd)
{
  struct expression *expr;
  struct command_line *current;
  struct cleanup *old_chain = make_cleanup (null_cleanup, 0);
  struct value *val;
  struct value *val_mark;
  int loop;
  enum command_control_type ret;
  char *new_line;

  /* Start by assuming failure, if a problem is detected, the code
     below will simply "break" out of the switch.  */
  ret = invalid_control;

  switch (cmd->control_type)
    {
    case simple_control:
      /* A simple command, execute it and return.  */
      new_line = insert_args (cmd->line);
      if (!new_line)
	break;
      make_cleanup (free_current_contents, &new_line);
      execute_command (new_line, 0);
      ret = cmd->control_type;
      break;

    case continue_control:
    case break_control:
      /* Return for "continue", and "break" so we can either
         continue the loop at the top, or break out.  */
      ret = cmd->control_type;
      break;

    case while_control:
      {
	/* Parse the loop control expression for the while statement.  */
	new_line = insert_args (cmd->line);
	if (!new_line)
	  break;
	make_cleanup (free_current_contents, &new_line);
	expr = parse_expression (new_line);
	make_cleanup (free_current_contents, &expr);

	ret = simple_control;
	loop = 1;

	/* Keep iterating so long as the expression is true.  */
	while (loop == 1)
	  {
	    int cond_result;

	    QUIT;

	    /* Evaluate the expression.  */
	    val_mark = value_mark ();
	    val = evaluate_expression (expr);
	    cond_result = value_true (val);
	    value_free_to_mark (val_mark);

	    /* If the value is false, then break out of the loop.  */
	    if (!cond_result)
	      break;

	    /* Execute the body of the while statement.  */
	    current = *cmd->body_list;
	    while (current)
	      {
		ret = execute_control_command (current);

		/* If we got an error, or a "break" command, then stop
		   looping.  */
		if (ret == invalid_control || ret == break_control)
		  {
		    loop = 0;
		    break;
		  }

		/* If we got a "continue" command, then restart the loop
		   at this point.  */
		if (ret == continue_control)
		  break;

		/* Get the next statement.  */
		current = current->next;
	      }
	  }

	/* Reset RET so that we don't recurse the break all the way down.  */
	if (ret == break_control)
	  ret = simple_control;

	break;
      }

    case if_control:
      {
	new_line = insert_args (cmd->line);
	if (!new_line)
	  break;
	make_cleanup (free_current_contents, &new_line);
	/* Parse the conditional for the if statement.  */
	expr = parse_expression (new_line);
	make_cleanup (free_current_contents, &expr);

	current = NULL;
	ret = simple_control;

	/* Evaluate the conditional.  */
	val_mark = value_mark ();
	val = evaluate_expression (expr);

	/* Choose which arm to take commands from based on the value of the
	   conditional expression.  */
	if (value_true (val))
	  current = *cmd->body_list;
	else if (cmd->body_count == 2)
	  current = *(cmd->body_list + 1);
	value_free_to_mark (val_mark);

	/* Execute commands in the given arm.  */
	while (current)
	  {
	    ret = execute_control_command (current);

	    /* If we got an error, get out.  */
	    if (ret != simple_control)
	      break;

	    /* Get the next statement in the body.  */
	    current = current->next;
	  }

	break;
      }

    default:
      warning ("Invalid control type in command structure.");
      break;
    }

  do_cleanups (old_chain);

  return ret;
}