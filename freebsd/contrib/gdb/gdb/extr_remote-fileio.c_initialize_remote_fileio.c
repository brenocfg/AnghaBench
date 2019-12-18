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
 int /*<<< orphan*/  add_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct cmd_list_element**) ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  set_system_call_allowed ; 
 int /*<<< orphan*/  show_system_call_allowed ; 

void
initialize_remote_fileio (struct cmd_list_element *remote_set_cmdlist,
			  struct cmd_list_element *remote_show_cmdlist)
{
  add_cmd ("system-call-allowed", no_class,
	   set_system_call_allowed,
	   "Set if the host system(3) call is allowed for the target.\n",
	   &remote_set_cmdlist);
  add_cmd ("system-call-allowed", no_class,
	   show_system_call_allowed,
	   "Show if the host system(3) call is allowed for the target.\n",
	   &remote_show_cmdlist);
}