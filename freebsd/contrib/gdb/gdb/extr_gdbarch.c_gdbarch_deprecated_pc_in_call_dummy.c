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
struct gdbarch {int (* deprecated_pc_in_call_dummy ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
gdbarch_deprecated_pc_in_call_dummy (struct gdbarch *gdbarch, CORE_ADDR pc, CORE_ADDR sp, CORE_ADDR frame_address)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->deprecated_pc_in_call_dummy != NULL);
  /* Do not check predicate: gdbarch->deprecated_pc_in_call_dummy != generic_pc_in_call_dummy, allow call.  */
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_deprecated_pc_in_call_dummy called\n");
  return gdbarch->deprecated_pc_in_call_dummy (pc, sp, frame_address);
}