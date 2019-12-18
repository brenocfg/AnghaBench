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
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_task_commands () ; 
 int /*<<< orphan*/  add_thread_commands () ; 
 int /*<<< orphan*/  class_maintenance ; 
 int /*<<< orphan*/  getproc () ; 
 int /*<<< orphan*/  gnu_debug_flag ; 
 int /*<<< orphan*/  gnu_ops ; 
 int /*<<< orphan*/  init_gnu_ops () ; 
 int /*<<< orphan*/  maintenancelist ; 
 int /*<<< orphan*/  proc_server ; 
 int /*<<< orphan*/  var_boolean ; 

void
_initialize_gnu_nat (void)
{
  proc_server = getproc ();
  
  init_gnu_ops ();
  add_target (&gnu_ops);

  add_task_commands ();
  add_thread_commands ();
  add_set_cmd ("gnu-debug", class_maintenance,
	       var_boolean, (char *) &gnu_debug_flag,
	       "Set debugging output for the gnu backend.", &maintenancelist);
}