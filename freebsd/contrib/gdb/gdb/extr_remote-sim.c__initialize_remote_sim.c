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
 int /*<<< orphan*/  add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_obscure ; 
 int /*<<< orphan*/  gdbsim_ops ; 
 int /*<<< orphan*/  init_gdbsim_ops () ; 
 int /*<<< orphan*/  simulator_command ; 

void
_initialize_remote_sim (void)
{
  init_gdbsim_ops ();
  add_target (&gdbsim_ops);

  add_com ("sim <command>", class_obscure, simulator_command,
	   "Send a command to the simulator.");
}