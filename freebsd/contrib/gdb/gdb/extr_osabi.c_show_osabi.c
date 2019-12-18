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
 scalar_t__ GDB_OSABI_DEFAULT ; 
 scalar_t__ GDB_OSABI_UNKNOWN ; 
 int /*<<< orphan*/  current_gdbarch ; 
 scalar_t__ gdbarch_osabi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdbarch_osabi_name (scalar_t__) ; 
 scalar_t__ osabi_auto ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ user_osabi_state ; 
 scalar_t__ user_selected_osabi ; 

__attribute__((used)) static void
show_osabi (char *args, int from_tty)
{
  if (user_osabi_state == osabi_auto)
    printf_filtered ("The current OS ABI is \"auto\" (currently \"%s\").\n",
		     gdbarch_osabi_name (gdbarch_osabi (current_gdbarch)));
  else
    printf_filtered ("The current OS ABI is \"%s\".\n",
		     gdbarch_osabi_name (user_selected_osabi));

  if (GDB_OSABI_DEFAULT != GDB_OSABI_UNKNOWN)
    printf_filtered ("The default OS ABI is \"%s\".\n",
		     gdbarch_osabi_name (GDB_OSABI_DEFAULT));
}