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
struct command_line {int body_count; struct command_line** body_list; int /*<<< orphan*/  control_type; int /*<<< orphan*/  line; struct command_line* next; } ;

/* Variables and functions */
 scalar_t__ xmalloc (int) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

struct command_line *
copy_command_lines (struct command_line *cmds)
{
  struct command_line *result = NULL;

  if (cmds)
    {
      result = (struct command_line *) xmalloc (sizeof (struct command_line));

      result->next = copy_command_lines (cmds->next);
      result->line = xstrdup (cmds->line);
      result->control_type = cmds->control_type;
      result->body_count = cmds->body_count;
      if (cmds->body_count > 0)
        {
          int i;

          result->body_list = (struct command_line **)
            xmalloc (sizeof (struct command_line *) * cmds->body_count);

          for (i = 0; i < cmds->body_count; i++)
            result->body_list[i] = copy_command_lines (cmds->body_list[i]);
        }
      else
        result->body_list = NULL;
    }

  return result;
}