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
struct ui_out {int dummy; } ;
struct command_line {scalar_t__ control_type; char* line; int body_count; struct command_line* next; struct command_line** body_list; } ;

/* Variables and functions */
 scalar_t__ break_control ; 
 scalar_t__ continue_control ; 
 scalar_t__ if_control ; 
 scalar_t__ simple_control ; 
 int /*<<< orphan*/  ui_out_field_fmt (struct ui_out*,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  ui_out_field_string (struct ui_out*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ui_out_spaces (struct ui_out*,int) ; 
 int /*<<< orphan*/  ui_out_text (struct ui_out*,char*) ; 
 scalar_t__ while_control ; 

void
print_command_lines (struct ui_out *uiout, struct command_line *cmd,
		     unsigned int depth)
{
  struct command_line *list;

  list = cmd;
  while (list)
    {

      if (depth)
	ui_out_spaces (uiout, 2 * depth);

      /* A simple command, print it and continue.  */
      if (list->control_type == simple_control)
	{
	  ui_out_field_string (uiout, NULL, list->line);
	  ui_out_text (uiout, "\n");
	  list = list->next;
	  continue;
	}

      /* loop_continue to jump to the start of a while loop, print it
         and continue. */
      if (list->control_type == continue_control)
	{
	  ui_out_field_string (uiout, NULL, "loop_continue");
	  ui_out_text (uiout, "\n");
	  list = list->next;
	  continue;
	}

      /* loop_break to break out of a while loop, print it and continue.  */
      if (list->control_type == break_control)
	{
	  ui_out_field_string (uiout, NULL, "loop_break");
	  ui_out_text (uiout, "\n");
	  list = list->next;
	  continue;
	}

      /* A while command.  Recursively print its subcommands and continue.  */
      if (list->control_type == while_control)
	{
	  ui_out_field_fmt (uiout, NULL, "while %s", list->line);
	  ui_out_text (uiout, "\n");
	  print_command_lines (uiout, *list->body_list, depth + 1);
	  if (depth)
	    ui_out_spaces (uiout, 2 * depth);
	  ui_out_field_string (uiout, NULL, "end");
	  ui_out_text (uiout, "\n");
	  list = list->next;
	  continue;
	}

      /* An if command.  Recursively print both arms before continueing.  */
      if (list->control_type == if_control)
	{
	  ui_out_field_fmt (uiout, NULL, "if %s", list->line);
	  ui_out_text (uiout, "\n");
	  /* The true arm. */
	  print_command_lines (uiout, list->body_list[0], depth + 1);

	  /* Show the false arm if it exists.  */
	  if (list->body_count == 2)
	    {
	      if (depth)
		ui_out_spaces (uiout, 2 * depth);
	      ui_out_field_string (uiout, NULL, "else");
	      ui_out_text (uiout, "\n");
	      print_command_lines (uiout, list->body_list[1], depth + 1);
	    }

	  if (depth)
	    ui_out_spaces (uiout, 2 * depth);
	  ui_out_field_string (uiout, NULL, "end");
	  ui_out_text (uiout, "\n");
	  list = list->next;
	  continue;
	}

      /* ignore illegal command type and try next */
      list = list->next;
    }				/* while (list) */
}