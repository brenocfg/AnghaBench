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
struct gdbarch {int (* deprecated_register_raw_size ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int stub1 (int) ; 

int
gdbarch_deprecated_register_raw_size (struct gdbarch *gdbarch, int reg_nr)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->deprecated_register_raw_size != NULL);
  /* Do not check predicate: gdbarch->deprecated_register_raw_size != generic_register_size, allow call.  */
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_deprecated_register_raw_size called\n");
  return gdbarch->deprecated_register_raw_size (reg_nr);
}