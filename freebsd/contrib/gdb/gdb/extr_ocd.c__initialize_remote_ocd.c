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
 int /*<<< orphan*/  add_prefix_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct cmd_list_element**,char*,int /*<<< orphan*/ ,struct cmd_list_element**) ; 
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bdm_command ; 
 int /*<<< orphan*/  bdm_reset_command ; 
 int /*<<< orphan*/  bdm_restart_command ; 
 int /*<<< orphan*/  bdm_update_flash_command ; 
 int /*<<< orphan*/  class_obscure ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  remote_timeout ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  var_integer ; 

void
_initialize_remote_ocd (void)
{
  extern struct cmd_list_element *cmdlist;
  static struct cmd_list_element *ocd_cmd_list = NULL;

  add_show_from_set (add_set_cmd ("remotetimeout", no_class,
				  var_integer, (char *) &remote_timeout,
			  "Set timeout value for remote read.\n", &setlist),
		     &showlist);

  add_prefix_cmd ("ocd", class_obscure, bdm_command, "", &ocd_cmd_list, "ocd ",
		  0, &cmdlist);

  add_cmd ("reset", class_obscure, bdm_reset_command, "", &ocd_cmd_list);
  add_cmd ("restart", class_obscure, bdm_restart_command, "", &ocd_cmd_list);
  add_cmd ("update-flash", class_obscure, bdm_update_flash_command, "", &ocd_cmd_list);
}