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
 int cmd_cfunc_eq (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_command ; 

int
is_complete_command (struct cmd_list_element *c)
{
  return cmd_cfunc_eq (c, complete_command);
}