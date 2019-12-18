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
struct gdbarch {int /*<<< orphan*/  initialized_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  architecture_changed_event () ; 
 int /*<<< orphan*/ * current_gdbarch ; 
 int /*<<< orphan*/  current_gdbarch_swap_in_hack (struct gdbarch*) ; 
 int /*<<< orphan*/  current_gdbarch_swap_out_hack () ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 

void
deprecated_current_gdbarch_select_hack (struct gdbarch *new_gdbarch)
{
  gdb_assert (new_gdbarch != NULL);
  gdb_assert (current_gdbarch != NULL);
  gdb_assert (new_gdbarch->initialized_p);
  current_gdbarch_swap_out_hack ();
  current_gdbarch_swap_in_hack (new_gdbarch);
  architecture_changed_event ();
}