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
struct command_line {int control_type; int body_count; int /*<<< orphan*/  line; struct command_line** body_list; int /*<<< orphan*/ * next; } ;
typedef  enum command_control_type { ____Placeholder_command_control_type } command_control_type ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  memset (struct command_line**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  savestring (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static struct command_line *
build_command_line (enum command_control_type type, char *args)
{
  struct command_line *cmd;

  if (args == NULL)
    error ("if/while commands require arguments.\n");

  cmd = (struct command_line *) xmalloc (sizeof (struct command_line));
  cmd->next = NULL;
  cmd->control_type = type;

  cmd->body_count = 1;
  cmd->body_list
    = (struct command_line **) xmalloc (sizeof (struct command_line *)
					* cmd->body_count);
  memset (cmd->body_list, 0, sizeof (struct command_line *) * cmd->body_count);
  cmd->line = savestring (args, strlen (args));
  return cmd;
}