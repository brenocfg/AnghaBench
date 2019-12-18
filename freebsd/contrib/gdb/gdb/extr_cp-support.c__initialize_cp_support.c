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

/* Variables and functions */
 int /*<<< orphan*/  add_alias_cmd (char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_prefix_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_maintenance ; 
 int /*<<< orphan*/  first_component_command ; 
 int /*<<< orphan*/  maint_cplus_cmd_list ; 
 int /*<<< orphan*/  maint_cplus_command ; 
 int /*<<< orphan*/  maintenancelist ; 

void
_initialize_cp_support (void)
{
  add_prefix_cmd ("cplus", class_maintenance, maint_cplus_command,
		  "C++ maintenance commands.", &maint_cplus_cmd_list,
		  "maintenance cplus ", 0, &maintenancelist);
  add_alias_cmd ("cp", "cplus", class_maintenance, 1, &maintenancelist);

  add_cmd ("first_component", class_maintenance, first_component_command,
	   "Print the first class/namespace component of NAME.",
	   &maint_cplus_cmd_list);
		  
}