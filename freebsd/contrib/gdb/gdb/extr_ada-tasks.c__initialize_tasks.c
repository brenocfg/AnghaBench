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
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_prefix_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct cmd_list_element**,char*,int,struct cmd_list_element**) ; 
 int /*<<< orphan*/  class_run ; 
 int /*<<< orphan*/  info_tasks_command ; 
 int /*<<< orphan*/  task_command ; 

void
_initialize_tasks (void)
{
  static struct cmd_list_element *task_cmd_list = NULL;
  extern struct cmd_list_element *cmdlist;

  add_info ("tasks", info_tasks_command,
	    "Without argument: list all known Ada tasks, with status information.\n"
	    "info tasks n: print detailed information of task n.\n");

  add_prefix_cmd ("task", class_run, task_command,
		  "Use this command to switch between tasks.\n\
 The new task ID must be currently known.", &task_cmd_list, "task ", 1, &cmdlist);
}