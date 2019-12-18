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
struct gdbarch {int /*<<< orphan*/  (* deprecated_get_saved_register ) (char*,int*,int /*<<< orphan*/ *,struct frame_info*,int,int*) ;} ;
struct frame_info {int dummy; } ;
typedef  enum lval_type { ____Placeholder_lval_type } lval_type ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int /*<<< orphan*/  stub1 (char*,int*,int /*<<< orphan*/ *,struct frame_info*,int,int*) ; 

void
gdbarch_deprecated_get_saved_register (struct gdbarch *gdbarch, char *raw_buffer, int *optimized, CORE_ADDR *addrp, struct frame_info *frame, int regnum, enum lval_type *lval)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->deprecated_get_saved_register != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_deprecated_get_saved_register called\n");
  gdbarch->deprecated_get_saved_register (raw_buffer, optimized, addrp, frame, regnum, lval);
}