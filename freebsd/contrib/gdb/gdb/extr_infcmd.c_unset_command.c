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
 int /*<<< orphan*/  printf_filtered (char*) ; 
 int /*<<< orphan*/  unsetlist ; 

__attribute__((used)) static void
unset_command (char *args, int from_tty)
{
  printf_filtered ("\"unset\" must be followed by the name of ");
  printf_filtered ("an unset subcommand.\n");
  help_list (unsetlist, "unset ", -1, gdb_stdout);
}