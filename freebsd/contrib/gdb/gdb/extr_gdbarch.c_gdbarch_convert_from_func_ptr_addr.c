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
struct target_ops {int dummy; } ;
struct gdbarch {int /*<<< orphan*/  (* convert_from_func_ptr_addr ) (struct gdbarch*,int /*<<< orphan*/ ,struct target_ops*) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int /*<<< orphan*/  stub1 (struct gdbarch*,int /*<<< orphan*/ ,struct target_ops*) ; 

CORE_ADDR
gdbarch_convert_from_func_ptr_addr (struct gdbarch *gdbarch, CORE_ADDR addr, struct target_ops *targ)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->convert_from_func_ptr_addr != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_convert_from_func_ptr_addr called\n");
  return gdbarch->convert_from_func_ptr_addr (gdbarch, addr, targ);
}