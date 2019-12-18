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
struct cmd_list_element {int /*<<< orphan*/  (* func ) (struct cmd_list_element*,char*,int) ;} ;

/* Variables and functions */
 scalar_t__ cmd_func_p (struct cmd_list_element*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  stub1 (struct cmd_list_element*,char*,int) ; 

void
cmd_func (struct cmd_list_element *cmd, char *args, int from_tty)
{
  if (cmd_func_p (cmd))
    (*cmd->func) (cmd, args, from_tty);
  else
    error ("Invalid command");
}