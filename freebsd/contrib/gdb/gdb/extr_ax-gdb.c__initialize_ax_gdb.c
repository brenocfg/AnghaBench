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
 int /*<<< orphan*/  add_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  agent_command ; 
 int /*<<< orphan*/  class_maintenance ; 
 int /*<<< orphan*/  maintenancelist ; 

void
_initialize_ax_gdb (void)
{
  add_cmd ("agent", class_maintenance, agent_command,
	   "Translate an expression into remote agent bytecode.",
	   &maintenancelist);
}