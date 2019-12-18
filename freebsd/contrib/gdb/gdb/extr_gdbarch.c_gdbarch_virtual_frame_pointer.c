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
struct gdbarch {int /*<<< orphan*/  (* virtual_frame_pointer ) (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  LONGEST ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 

void
gdbarch_virtual_frame_pointer (struct gdbarch *gdbarch, CORE_ADDR pc, int *frame_regnum, LONGEST *frame_offset)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->virtual_frame_pointer != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_virtual_frame_pointer called\n");
  gdbarch->virtual_frame_pointer (pc, frame_regnum, frame_offset);
}