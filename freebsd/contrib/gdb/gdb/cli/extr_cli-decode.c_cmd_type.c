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
struct cmd_list_element {int type; } ;
typedef  enum cmd_types { ____Placeholder_cmd_types } cmd_types ;

/* Variables and functions */

enum cmd_types
cmd_type (struct cmd_list_element *cmd)
{
  return cmd->type;
}