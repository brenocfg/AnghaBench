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
 int /*<<< orphan*/  execute_cmd_pre_hook (struct cmd_list_element*) ; 

__attribute__((used)) static int
hook_stop_stub (void *cmd)
{
  execute_cmd_pre_hook ((struct cmd_list_element *) cmd);
  return (0);
}