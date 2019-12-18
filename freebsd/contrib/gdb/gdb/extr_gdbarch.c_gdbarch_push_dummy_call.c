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
struct value {int dummy; } ;
struct regcache {int dummy; } ;
struct gdbarch {int /*<<< orphan*/  (* push_dummy_call ) (struct gdbarch*,int /*<<< orphan*/ ,struct regcache*,int /*<<< orphan*/ ,int,struct value**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int gdbarch_debug ; 
 int /*<<< orphan*/  stub1 (struct gdbarch*,int /*<<< orphan*/ ,struct regcache*,int /*<<< orphan*/ ,int,struct value**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

CORE_ADDR
gdbarch_push_dummy_call (struct gdbarch *gdbarch, CORE_ADDR func_addr, struct regcache *regcache, CORE_ADDR bp_addr, int nargs, struct value **args, CORE_ADDR sp, int struct_return, CORE_ADDR struct_addr)
{
  gdb_assert (gdbarch != NULL);
  gdb_assert (gdbarch->push_dummy_call != NULL);
  if (gdbarch_debug >= 2)
    fprintf_unfiltered (gdb_stdlog, "gdbarch_push_dummy_call called\n");
  return gdbarch->push_dummy_call (gdbarch, func_addr, regcache, bp_addr, nargs, args, sp, struct_return, struct_addr);
}