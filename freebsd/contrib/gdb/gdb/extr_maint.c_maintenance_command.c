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
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  help_list (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maintenancelist ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 

__attribute__((used)) static void
maintenance_command (char *args, int from_tty)
{
  printf_unfiltered ("\"maintenance\" must be followed by the name of a maintenance command.\n");
  help_list (maintenancelist, "maintenance ", -1, gdb_stdout);
}