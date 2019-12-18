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
 int /*<<< orphan*/  class_maintenance ; 
 int /*<<< orphan*/  maintenance_print_dummy_frames ; 
 int /*<<< orphan*/  maintenanceprintlist ; 

void
_initialize_dummy_frame (void)
{
  add_cmd ("dummy-frames", class_maintenance, maintenance_print_dummy_frames,
	   "Print the contents of the internal dummy-frame stack.",
	   &maintenanceprintlist);

}