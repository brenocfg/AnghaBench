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
struct command_line {int dummy; } ;
struct cmd_list_element {char* name; struct command_line* user_commands; } ;

/* Variables and functions */
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  print_command_lines (int /*<<< orphan*/ ,struct command_line*,int) ; 
 int /*<<< orphan*/  uiout ; 

void
show_user_1 (struct cmd_list_element *c, struct ui_file *stream)
{
  struct command_line *cmdlines;

  cmdlines = c->user_commands;
  if (!cmdlines)
    return;
  fputs_filtered ("User command ", stream);
  fputs_filtered (c->name, stream);
  fputs_filtered (":\n", stream);

  print_command_lines (uiout, cmdlines, 1);
  fputs_filtered ("\n", stream);
}