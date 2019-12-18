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
 int /*<<< orphan*/  add_info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  show_copying_command ; 
 int /*<<< orphan*/  show_warranty_command ; 
 int /*<<< orphan*/  showlist ; 

void
_initialize_copying (void)
{
  add_cmd ("copying", no_class, show_copying_command,
	   "Conditions for redistributing copies of GDB.",
	   &showlist);
  add_cmd ("warranty", no_class, show_warranty_command,
	   "Various kinds of warranty you do not have.",
	   &showlist);

  /* For old-timers, allow "info copying", etc.  */
  add_info ("copying", show_copying_command,
	    "Conditions for redistributing copies of GDB.");
  add_info ("warranty", show_warranty_command,
	    "Various kinds of warranty you do not have.");
}