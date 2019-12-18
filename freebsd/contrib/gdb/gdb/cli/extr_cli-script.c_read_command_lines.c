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
struct command_line {scalar_t__ control_type; struct command_line* next; } ;
struct cleanup {int dummy; } ;
typedef  enum misc_command_type { ____Placeholder_misc_command_type } misc_command_type ;
typedef  enum command_control_type { ____Placeholder_command_control_type } command_control_type ;

/* Variables and functions */
 int /*<<< orphan*/  END_MESSAGE ; 
 scalar_t__ control_level ; 
 int /*<<< orphan*/  discard_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  dont_repeat () ; 
 int end_command ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ if_control ; 
 scalar_t__ input_from_terminal_p () ; 
 int invalid_control ; 
 struct cleanup* make_cleanup_free_command_lines (struct command_line**) ; 
 int nop_command ; 
 int ok_command ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*,int /*<<< orphan*/ ) ; 
 int read_next_line (struct command_line**) ; 
 int /*<<< orphan*/  readline_begin_hook (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readline_end_hook () ; 
 int recurse_read_control_structure (struct command_line*) ; 
 int simple_control ; 
 int /*<<< orphan*/  stub1 (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 () ; 
 scalar_t__ while_control ; 

struct command_line *
read_command_lines (char *prompt_arg, int from_tty)
{
  struct command_line *head, *tail, *next;
  struct cleanup *old_chain;
  enum command_control_type ret;
  enum misc_command_type val;

  control_level = 0;
  if (readline_begin_hook)
    {
      /* Note - intentional to merge messages with no newline */
      (*readline_begin_hook) ("%s  %s\n", prompt_arg, END_MESSAGE);
    }
  else if (from_tty && input_from_terminal_p ())
    {
      printf_unfiltered ("%s\n%s\n", prompt_arg, END_MESSAGE);
      gdb_flush (gdb_stdout);
    }

  head = tail = NULL;
  old_chain = NULL;

  while (1)
    {
      val = read_next_line (&next);

      /* Ignore blank lines or comments.  */
      if (val == nop_command)
	continue;

      if (val == end_command)
	{
	  ret = simple_control;
	  break;
	}

      if (val != ok_command)
	{
	  ret = invalid_control;
	  break;
	}

      if (next->control_type == while_control
	  || next->control_type == if_control)
	{
	  control_level++;
	  ret = recurse_read_control_structure (next);
	  control_level--;

	  if (ret == invalid_control)
	    break;
	}

      if (tail)
	{
	  tail->next = next;
	}
      else
	{
	  head = next;
	  old_chain = make_cleanup_free_command_lines (&head);
	}
      tail = next;
    }

  dont_repeat ();

  if (head)
    {
      if (ret != invalid_control)
	{
	  discard_cleanups (old_chain);
	}
      else
	do_cleanups (old_chain);
    }

  if (readline_end_hook)
    {
      (*readline_end_hook) ();
    }
  return (head);
}