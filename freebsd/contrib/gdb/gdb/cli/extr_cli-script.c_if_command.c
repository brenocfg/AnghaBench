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
struct command_line {int dummy; } ;

/* Variables and functions */
 int control_level ; 
 int /*<<< orphan*/  execute_control_command (struct command_line*) ; 
 int /*<<< orphan*/  free_command_lines (struct command_line**) ; 
 struct command_line* get_command_line (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  if_control ; 

void
if_command (char *arg, int from_tty)
{
  struct command_line *command = NULL;

  control_level = 1;
  command = get_command_line (if_control, arg);

  if (command == NULL)
    return;

  execute_control_command (command);
  free_command_lines (&command);
}