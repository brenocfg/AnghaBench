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
struct cmd_list_element {int flags; char* replacement; } ;

/* Variables and functions */
 int CMD_DEPRECATED ; 
 int DEPRECATED_WARN_USER ; 

struct cmd_list_element *
deprecate_cmd (struct cmd_list_element *cmd, char *replacement)
{
  cmd->flags |= (CMD_DEPRECATED | DEPRECATED_WARN_USER);

  if (replacement != NULL)
    cmd->replacement = replacement;
  else
    cmd->replacement = NULL;

  return cmd;
}